#include "modeller.h"
#include "../math/vector.h"
#include "../math/quaternion.h"
#include "../math/constants.h"

#include <cstdint>

using namespace LRender;

const float Modeller::TURTLE_STEP = 0.05f;
const float Modeller::TURTLE_ANGLE = 0.3;
const size_t Modeller::TUBE_PRECISION = 7;

Modeller::Modeller(const Agent &agent, std::mt19937 &randomizer) {
	build(agent, randomizer);
}

std::shared_ptr<Model> Modeller::getBranches() {
	return branches;
}

std::shared_ptr<Model> Modeller::getLeaves() {
	return leaves;
}

void Modeller::build(const Agent &agent, std::mt19937 &randomizer) {
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	std::vector<Path> paths;
	Node node(agent.getPosition(), std::uniform_real_distribution<float>(0, Constants::PI * 2)(randomizer));

	trace(
		nullptr,
		paths,
		node,
		agent.getSymbols().begin(),
		agent.getSymbols().end());

	for(auto path : paths)
		makeTube(vertices, indices, TUBE_PRECISION, path);

	branches.reset(new Model(vertices, indices));
}

int Modeller::trace(
	Path *parent,
	std::vector<Path> &paths,
	Node node,
	std::string::const_iterator &at,
	const std::string::const_iterator &last) {
	Path path(node);
	int lastChild = -1;

	while(at != last) {
		switch(*at++) {
		case BRANCH_OPEN:
			lastChild = trace(&path, paths, node, at, last);

			break;
		case BRANCH_CLOSE:
			goto end;
		case PITCH_INCREMENT:
			node.pitch(TURTLE_ANGLE);
			
			break;
		case PITCH_DECREMENT:
			node.pitch(-TURTLE_ANGLE);

			break;
		case ROLL_INCREMENT:
			node.roll(TURTLE_ANGLE);

			break;
		case ROLL_DECREMENT:
			node.roll(-TURTLE_ANGLE);

			break;
		default:
			if(*(at - 1) >= STEP_MIN && *(at - 1) <= STEP_MAX) {
				path.add(node.extrude(TURTLE_STEP));

				if(lastChild != -1) {
					paths[lastChild].setRoot({ *(path.getNodes().end() - 2), *(path.getNodes().end() - 1) });

					lastChild = -1;
				}
			}

			break;
		}
	}

end:
	if(path.size() > 1) {
		path.calculateTopDist();
		paths.push_back(path);

		if(parent)
			parent->calculateTopDist(path.getNodes()[0].topDist);

		if(lastChild != -1)
			paths[lastChild].setRoot({ *(path.getNodes().end() - 1) });

		return paths.size() - 1;
	}

	return -1;
}

Modeller::TraceChild::TraceChild(const int branchAt, const int childIndex) :
	branchAt(branchAt),
	childIndex(childIndex) {

}
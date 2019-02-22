#include "agentModel.h"
#include "tube.h"
#include "../math/vector.h"
#include "../math/quaternion.h"
#include "../math/constants.h"

#include <cstdint>

using namespace LRender;

const float AgentModel::TURTLE_STEP = 0.05f;
const float AgentModel::TURTLE_ANGLE = 0.3;
const size_t AgentModel::TUBE_PRECISION = 7;

AgentModel::AgentModel(const Agent &agent, const RadiusSampler &radiusSampler, std::mt19937 &randomizer) :
	radiusSampler(radiusSampler) {
	build(agent, randomizer);
}

std::shared_ptr<Model> AgentModel::getBranches() {
	return branches;
}

std::shared_ptr<Model> AgentModel::getLeaves() {
	return leaves;
}

void AgentModel::build(const Agent &agent, std::mt19937 &randomizer) {
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
		Tube::modelTube(
			vertices,
			indices,
			Vector(0.53f, 0.39f, 0.78f),
			radiusSampler,
			TUBE_PRECISION,
			path);

	branches.reset(new Model(vertices, indices));
}

int AgentModel::trace(
	Path *parent,
	std::vector<Path> &paths,
	Node node,
	std::string::const_iterator &at,
	const std::string::const_iterator &last) {
	Path path(node);
	int lastChild = -1;

	while(at != last) {
		switch(*at++) {
		case SYM_BRANCH_OPEN:
			lastChild = trace(&path, paths, node, at, last);

			break;
		case SYM_BRANCH_CLOSE:
			goto end;
		case SYM_PITCH_INCREMENT:
			node.pitch(TURTLE_ANGLE);
			
			break;
		case SYM_PITCH_DECREMENT:
			node.pitch(-TURTLE_ANGLE);

			break;
		case SYM_ROLL_INCREMENT:
			node.roll(TURTLE_ANGLE);

			break;
		case SYM_ROLL_DECREMENT:
			node.roll(-TURTLE_ANGLE);

			break;
		default:
			if(*(at - 1) >= SYM_STEP_MIN && *(at - 1) <= SYM_STEP_MAX) {
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

AgentModel::TraceChild::TraceChild(const int branchAt, const int childIndex) :
	branchAt(branchAt),
	childIndex(childIndex) {

}
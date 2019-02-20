#include "modeller.h"
#include "../math/vector.h"
#include "../math/quaternion.h"
#include "../math/constants.h"

#include <cstdint>

using namespace LRender;

const Vector Modeller::UP(0, 1, 0);
const float Modeller::TURTLE_STEP = 0.05f;
const float Modeller::TURTLE_ANGLE = 0.3;
const float Modeller::TURTLE_RADIUS_PER_SEGMENT = 0.001f;
const Vector Modeller::AXIS_PITCH(0, 0, 1);
const Vector Modeller::AXIS_ROLL(0, 1, 0);
const size_t Modeller::TUBE_PRECISION = 5;

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

	trace(
		paths,
		Node(agent.getPosition(), Quaternion().rotate(
			UP,
			std::uniform_real_distribution<float>(0, Constants::PI * 2)(randomizer))),
		agent.getSymbols().begin(),
		agent.getSymbols().end());
	
	for(auto path : paths)
		path.setRadius(TURTLE_RADIUS_PER_SEGMENT * 40);

	for(size_t i = paths.size(); i-- > 0;) {
		paths[i].setRadius(paths[i].size() * TURTLE_RADIUS_PER_SEGMENT);
		paths[i].taper(paths);
	}

	for(auto path : paths)
		makeTube(vertices, indices, TUBE_PRECISION, path.getNodes());

	branches.reset(new Model(vertices, indices));
}

int Modeller::trace(
	std::vector<Path> &paths,
	Node node,
	std::string::const_iterator &at,
	const std::string::const_iterator &last) {
	Path path(node);

	while(at != last) {
		switch(*at++) {
		case BRANCH_OPEN:
			path.attach(trace(paths, node, at, last));

			break;
		case BRANCH_CLOSE:
			if(path.size() > 1)
				return paths.push_back(path), paths.size() - 1;

			return -1;
		case PITCH_INCREMENT:
			node.heading.rotate(AXIS_PITCH, TURTLE_ANGLE);
			
			break;
		case PITCH_DECREMENT:
			node.heading.rotate(AXIS_PITCH, -TURTLE_ANGLE);

			break;
		case ROLL_INCREMENT:
			node.heading.rotate(AXIS_ROLL, TURTLE_ANGLE);

			break;
		case ROLL_DECREMENT:
			node.heading.rotate(AXIS_ROLL, -TURTLE_ANGLE);

			break;
		default:
			if(*(at - 1) >= STEP_MIN && *(at - 1) <= STEP_MAX)
				path.add(node.extrude(TURTLE_STEP));

			break;
		}
	}

	if(path.size() > 1)
		return paths.push_back(path), paths.size() - 1;

	return -1;
}
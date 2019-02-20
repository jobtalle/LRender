#include "modeller.h"
#include "../math/vector.h"
#include "../math/quaternion.h"

#include <cstdint>
#include <iostream>

using namespace LRender;

const Vector Modeller::UP(0, 1, 0);
const float Modeller::TURTLE_STEP = 0.1;
const float Modeller::TURTLE_ANGLE = 0.3;
const Vector Modeller::AXIS_PITCH(0, 0, 1);
const Vector Modeller::AXIS_ROLL(0, 1, 0);
const size_t Modeller::TUBE_PRECISION = 6;

Modeller::Modeller(const Agent &agent) {
	build(agent);
}

std::shared_ptr<Model> Modeller::getBranches() {
	return branches;
}

std::shared_ptr<Model> Modeller::getLeaves() {
	return leaves;
}

void Modeller::build(const Agent &agent) {
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	trace(
		vertices,
		indices,
		Node(agent.getPosition(), Quaternion()),
		agent.getSymbols().begin(),
		agent.getSymbols().end());

	branches.reset(new Model(vertices, indices));
}

void Modeller::trace(
	std::vector<Vertex> &vertices,
	std::vector<uint32_t> &indices,
	Node node,
	std::string::const_iterator &at,
	const std::string::const_iterator &last) {
	std::vector<Node> path({ node });

	while(at != last) {
		switch(*at++) {
		case BRANCH_OPEN:
			trace(vertices, indices, node, at, last);

			break;
		case BRANCH_CLOSE:
			if(path.size() > 1)
				makeTube(vertices, indices, TUBE_PRECISION, path);

			return;

			break;
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
			path.push_back(node.extrude(TURTLE_STEP));

			break;
		}
	}

	if(path.size() > 1)
		makeTube(vertices, indices, TUBE_PRECISION, path);
}
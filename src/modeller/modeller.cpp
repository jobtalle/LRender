#include "modeller.h"
#include "../math/vector.h"
#include "../math/quaternion.h"

#include <cstdint>
#include <iostream>

using namespace LRender;

const float Modeller::TURTLE_STEP = 0.05;
const float Modeller::TURTLE_ANGLE = 0.3;
const Vector Modeller::AXIS_PITCH(0, 0, 1);
const Vector Modeller::AXIS_ROLL(0, 1, 0);
const Vector Modeller::UP(0, TURTLE_STEP, 0);

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

	trace(vertices, indices, Quaternion(), agent.getPosition(), agent.getSymbols().begin(), agent.getSymbols().end());

	branches.reset(new Model(vertices, indices));
}

void Modeller::trace(
	std::vector<Vertex> &vertices,
	std::vector<uint32_t> &indices,
	Quaternion turtleHeading,
	Vector turtlePosition,
	std::string::const_iterator &at,
	const std::string::const_iterator &last) {
	std::vector<Vector> path({ turtlePosition });

	while(at != last) {
		switch(*at++) {
		case BRANCH_OPEN:
			trace(vertices, indices, turtleHeading, turtlePosition, at, last);

			break;
		case BRANCH_CLOSE:
			if(path.size() > 1)
				makeTube(vertices, indices, path);

			return;

			break;
		case PITCH_INCREMENT:
			turtleHeading.rotate(AXIS_PITCH, TURTLE_ANGLE);
			
			break;
		case PITCH_DECREMENT:
			turtleHeading.rotate(AXIS_PITCH, -TURTLE_ANGLE);

			break;
		case ROLL_INCREMENT:
			turtleHeading.rotate(AXIS_ROLL, TURTLE_ANGLE);

			break;
		case ROLL_DECREMENT:
			turtleHeading.rotate(AXIS_ROLL, -TURTLE_ANGLE);

			break;
		default:
			path.push_back(turtlePosition += turtleHeading * UP);

			break;
		}
	}

	if(path.size() > 1)
		makeTube(vertices, indices, path);
}
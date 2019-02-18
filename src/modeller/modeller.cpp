#include "modeller.h"
#include "../math/vector.h"
#include "../math/quaternion.h"

#include <iostream>

using namespace LRender;

const float Modeller::TURTLE_STEP = 0.05;
const Vector Modeller::UP(0, -TURTLE_STEP, 0);

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
	std::vector<std::vector<Vector>> paths;

	makePath(paths, Quaternion(), agent.getPosition(), agent.getSymbols().begin(), agent.getSymbols().end());

	std::cout << "Made " << paths.size() << " paths" << std::endl;
}

void Modeller::makePath(
	std::vector<std::vector<Vector>> &paths,
	Quaternion turtleHeading,
	Vector turtlePosition,
	std::string::const_iterator &at,
	const std::string::const_iterator &last) {
	std::vector<Vector> path({ turtlePosition });

	while(at != last) {
		switch(*at++) {
		case BRANCH_OPEN:
			makePath(paths, turtleHeading, turtlePosition, at, last);

			break;
		case BRANCH_CLOSE:
			if(path.size() > 1)
				paths.push_back(path);

			return;

			break;
		default:
			path.push_back(turtlePosition += turtleHeading * UP);

			break;
		}
	}

	if(path.size() > 1)
		paths.push_back(path);
}
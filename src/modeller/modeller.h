#pragma once

#include "../scene/agent.h"
#include "../model.h"
#include "../math/quaternion.h"

#include <vector>
#include <memory>

namespace LRender {
	class Modeller final {
	public:
		Modeller(const Agent &agent);
		std::shared_ptr<Model> getBranches();
		std::shared_ptr<Model> getLeaves();

	private:
		static const float TURTLE_STEP;
		static const Vector UP;
		static const char BRANCH_OPEN = '[';
		static const char BRANCH_CLOSE = ']';

		std::shared_ptr<Model> branches;
		std::shared_ptr<Model> leaves;

		void build(const Agent &agent);
		void makePath(
			std::vector<std::vector<Vector>> &paths,
			Quaternion turtleHeading,
			Vector turtlePosition,
			std::string::const_iterator &at,
			const std::string::const_iterator &last);
	};
};
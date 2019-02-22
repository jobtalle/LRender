#pragma once

#include "node.h"
#include "branch.h"
#include "leaf.h"
#include "radiusSampler.h"
#include "../scene/agent.h"
#include "../model.h"
#include "../math/quaternion.h"

#include <vector>
#include <memory>
#include <random>

namespace LRender {
	class AgentModel final {
	public:
		AgentModel(
			const Agent &agent,
			const RadiusSampler &radiusSampler,
			std::mt19937 &randomizer);
		std::shared_ptr<Model> getBranches();
		std::shared_ptr<Model> getLeaves();

	private:
		static const float TURTLE_STEP;
		static const float TURTLE_ANGLE;
		static const size_t TUBE_PRECISION;
		static const char SYM_STEP_MIN = 'A';
		static const char SYM_STEP_MAX = 'Z';
		static const char SYM_LEAF = '>';
		static const char SYM_BRANCH_OPEN = '[';
		static const char SYM_BRANCH_CLOSE = ']';
		static const char SYM_PITCH_INCREMENT = '+';
		static const char SYM_PITCH_DECREMENT = '-';
		static const char SYM_ROLL_INCREMENT = '/';
		static const char SYM_ROLL_DECREMENT = '\\';

		std::shared_ptr<Model> modelBranches;
		std::shared_ptr<Model> modelLeaves;
		RadiusSampler radiusSampler;

		void build(
			const Agent &agent, std::mt19937 &randomizer);
		int traceBranch(
			Branch *branch,
			std::vector<Branch> &branches,
			std::vector<Leaf> &leaves,
			Node node,
			std::string::const_iterator &at,
			const std::string::const_iterator &last);
	};
};
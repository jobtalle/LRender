#pragma once

#include "node.h"
#include "path.h"
#include "../scene/agent.h"
#include "../model.h"
#include "../math/quaternion.h"

#include <vector>
#include <memory>
#include <random>

namespace LRender {
	class Modeller final {
	public:
		Modeller(const Agent &agent, std::mt19937 &randomizer);
		std::shared_ptr<Model> getBranches();
		std::shared_ptr<Model> getLeaves();

	private:
		static const float TURTLE_STEP;
		static const float TURTLE_ANGLE;
		static const size_t TUBE_PRECISION;
		static const char STEP_MIN = 'A';
		static const char STEP_MAX = 'Z';
		static const char BRANCH_OPEN = '[';
		static const char BRANCH_CLOSE = ']';
		static const char PITCH_INCREMENT = '+';
		static const char PITCH_DECREMENT = '-';
		static const char ROLL_INCREMENT = '/';
		static const char ROLL_DECREMENT = '\\';

		std::shared_ptr<Model> branches;
		std::shared_ptr<Model> leaves;

		void build(const Agent &agent, std::mt19937 &randomizer);
		void trace(
			Path *parent,
			std::vector<Path> &paths,
			Node node,
			std::string::const_iterator &at,
			const std::string::const_iterator &last);

		static void makeTube(
			std::vector<Vertex> &vertices,
			std::vector<uint32_t> &indices,
			const size_t precision,
			const Path &path);
	};
};
#pragma once

#include "modeller/node.h"
#include "modeller/branch.h"
#include "modeller/leaf.h"
#include "modeller/seed.h"
#include "scene/agent.h"
#include "model/model.h"
#include "lparse.h"

#include <vector>
#include <memory>
#include <list>

namespace LRender {
	class AgentModel final {
	public:
		AgentModel(
			const Agent &agent,
			LParse::Randomizer &randomizer);
		AgentModel(const AgentModel &other) = default;
		const Model &getBranches() const;
		const Model &getLeaves() const;
		const std::vector<Vector> &getSeedPositions() const;
		const std::vector<float> &getLeafAreas() const;
		const Vector &getMinimum() const;
		const Vector &getMaximum() const;
		void makeModels();

	private:
		static const float TURTLE_STEP;
		static const float TURTLE_ANGLE;
		static const size_t TUBE_PRECISION;

		std::shared_ptr<Geometry> geometryBranches;
		std::shared_ptr<Geometry> geometryLeaves;
		std::shared_ptr<Model> modelBranches;
		std::shared_ptr<Model> modelLeaves;
		std::vector<Vector> seedPositions;
		std::vector<float> leafAreas;
		Vector minimum;
		Vector maximum;

		void build(
			const Agent &agent, LParse::Randomizer &randomizer);
		Branch *traceBranch(
			Branch *parent,
			bool leaf,
			std::list<Branch> &branches,
			std::list<Leaf> &leaves,
			std::list<Seed> &seeds,
			Node node,
			std::string::const_iterator &at,
			const std::string::const_iterator &last);
	};
}
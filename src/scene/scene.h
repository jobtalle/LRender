#pragma once

#include "scene/agent.h"
#include "scene/terrain.h"

#include <vector>

namespace LRender {
	class Scene final {
	public:
		Scene(const Terrain &terrain);
		void addAgent(const Agent &agent);
		const Terrain &getTerrain() const;
		const std::vector<Agent> &getAgents() const;

	private:
		const Terrain terrain;
		std::vector<Agent> agents;
	};
}
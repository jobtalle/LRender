#pragma once

#include "agent.h"

#include <vector>

namespace LRender {
	class Scene final {
	public:
		Scene();
		void addAgent(const Agent &agent);

	private:
		std::vector<Agent> agents;
	};
}
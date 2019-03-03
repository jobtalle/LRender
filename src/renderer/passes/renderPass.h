#pragma once

#include "modeller/agentModel.h"
#include "modeller/terrainModel.h"
#include "renderer/shaders.h"
#include "renderer/orbit.h"
#include "math/matrix.h"

#include <vector>

namespace LRender {
	class RenderPass {
	public:
		virtual ~RenderPass() = default;
		virtual void render(
			const Shaders &shaders,
			const Orbit &orbit,
			const Matrix &projection,
			const std::vector<LRender::TerrainModel> &terrains,
			const std::vector<LRender::AgentModel> &agents) = 0;
	};
};
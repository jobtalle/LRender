#pragma once

#include "renderer/passes/renderPass.h"
#include "renderer/uniforms/uniformsView.h"

namespace LRender {
	class RenderPassViewDefault final : public RenderPass {
	public:
		void render(
			const Shaders &shaders,
			const Orbit &orbit,
			const Matrix &projection,
			const std::vector<LRender::TerrainModel> &terrains,
			const std::vector<LRender::AgentModel> &agents) override final;

	private:
		UniformsView uniforms;
	};
};
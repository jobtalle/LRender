#pragma once

#include "renderer/passes/renderPass.h"
#include "renderer/uniforms/uniformsView.h"

namespace LRender {
	class RenderPassViewWireframe final : public RenderPass {
	public:
		void render(
			const Shaders &shaders,
			const Orbit &orbit,
			const Matrix &projection,
			const std::vector<TerrainModel> &terrains,
			const std::vector<AgentModel> &agents,
			const Renderer *renderer) override final;

	private:
		static const Vector CLEAR_COLOR;

		UniformsView uniforms;
	};
}
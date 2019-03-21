#pragma once

#include "renderer/passes/renderPass.h"
#include "renderer/uniforms/uniformsView.h"
#include "renderer/uniforms/uniformsLight.h"
#include "renderer/target/renderTargetDepth.h"
#include "renderPassShadows.h"

namespace LRender {
	class RenderPassViewDefault final : public RenderPass {
	public:
		RenderPassViewDefault();
		void render(
			const Shaders &shaders,
			const Orbit &orbit,
			const Matrix &projection,
			const std::vector<TerrainModel> &terrains,
			const std::vector<AgentModel> &agents,
			const Renderer *renderer) override final;

	private:
		static const Vector CLEAR_COLOR;
		static const size_t SHADOW_SIZE;
		Vector lightDirection;

		UniformsView uniformsView;
		UniformsLight uniformsLight;
		RenderTargetDepth shadowTarget;
		RenderPassShadows shadowPass;
	};
}

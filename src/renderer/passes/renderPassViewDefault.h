#pragma once

#include "renderer/passes/renderPass.h"
#include "renderer/uniforms/uniformsView.h"
#include "renderer/uniforms/uniformsLight.h"
#include "renderer/uniforms/uniformsShadows.h"
#include "renderer/target/renderTargetDepth.h"

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
		static const float LIGHT_DISTANCE;
		static const float LIGHT_ZNEAR;
		static const float LIGHT_ZFAR;
		static const Vector UP;
		Vector lightDirection;

		UniformsView uniformsView;
		UniformsLight uniformsLight;
		UniformsShadows uniformsShadows;
		RenderTargetDepth shadowTarget;
	};
}

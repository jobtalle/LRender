#pragma once

#include "renderer/passes/renderPass.h"
#include "renderer/uniforms/uniformsShadows.h"
#include "math/vector.h"

namespace LRender {
	class RenderPassShadows final : public RenderPass {
	public:
		RenderPassShadows();
		void setLightDirection(const Vector &direction);
		void render(
			const Shaders &shaders,
			const Orbit &orbit,
			const Matrix &projection,
			const std::vector<TerrainModel> &terrains,
			const std::vector<AgentModel> &agents,
			const Renderer *renderer) override final;

	private:
		static const Vector UP;
		static const float RADIUS;

		Matrix lightProjection;
		Vector lightDirection;
		UniformsShadows uniforms;
	};
}
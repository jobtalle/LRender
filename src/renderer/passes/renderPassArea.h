#pragma once

#include "renderer/passes/renderPass.h"
#include "report/reportLimits.h"
#include "renderer/uniforms/uniformsView.h"

namespace LRender {
	class RenderPassArea final : public RenderPass {
	public:
		RenderPassArea(const ReportLimits &limits);
		float getViewportWidth() const;
		float getViewportHeight() const;
		void setAngle(const float angle);
		void render(
			const Shaders &shaders,
			const Orbit &orbit,
			const Matrix &projection,
			const std::vector<LRender::TerrainModel> &terrains,
			const std::vector<LRender::AgentModel> &agents) override final;

	private:
		UniformsView uniforms;
		Vector center;
		Matrix projection;
		Matrix lookAt;

		struct {
			float width;
			float height;
		} viewport;

		void makeViewport(const ReportLimits &limits);
	};
}
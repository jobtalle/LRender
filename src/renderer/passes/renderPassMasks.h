#pragma once

#include "renderer/passes/renderPass.h"
#include "renderer/target/renderTargetUint.h"
#include "renderer/uniforms/uniformsView.h"

namespace LRender {
	class RenderPassMasks final : public RenderPass {
	public:
		RenderPassMasks(size_t width, size_t height);
		short sample(float x, float y) const;
		void render(
			const Shaders &shaders,
			const Orbit &orbit,
			const Matrix &projection,
			const std::vector<TerrainModel> &terrains,
			const std::vector<AgentModel> &agents,
			const Renderer *renderer) override final;

	private:
		UniformsView uniforms;
		std::shared_ptr<RenderTargetUint> target;
	};
}

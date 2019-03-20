#pragma once

#include "renderer/passes/renderPass.h"
#include "renderer/target/renderTargetUint.h"

namespace LRender {
	class RenderPassInteger final : public RenderPass {
	public:
		RenderPassInteger(std::shared_ptr<RenderTargetUint> image);
		~RenderPassInteger();
		void render(
			const Shaders &shaders,
			const Orbit &orbit,
			const Matrix &projection,
			const std::vector<TerrainModel> &terrains,
			const std::vector<AgentModel> &agents,
			const Renderer *renderer) override final;

	private:
		static const std::vector<float> VERTICES;
		const std::shared_ptr<RenderTargetUint> image;
		GLuint vao;
		GLuint vertices;
	};
}
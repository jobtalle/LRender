#pragma once

#include "renderer/passes/renderPass.h"
#include "renderer/target/renderTargetColor.h"
#include "glad/glad.h"

#include <memory>
#include <vector>

namespace LRender {
	class RenderPassImage final : public RenderPass {
	public:
		RenderPassImage(std::shared_ptr<RenderTargetColor> target);
		~RenderPassImage();
		void render(
			const Shaders &shaders,
			const Orbit &orbit,
			const Matrix &projection,
			const std::vector<LRender::TerrainModel> &terrains,
			const std::vector<LRender::AgentModel> &agents) override final;

	private:
		static const std::vector<float> VERTICES;
		const std::shared_ptr<RenderTargetColor> image;
		GLuint vao;
		GLuint vertices;
	};
}
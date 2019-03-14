#pragma once

#include "shader.h"
#include "renderer/shaders/shaderImage.h"

namespace LRender {
	class Shaders final {
	public:
		Shaders();
		const Shader &getBranches() const;
		const Shader &getLeaves() const;
		const Shader &getExposure() const;
		const ShaderImage &getImage() const;

	private:
		const Shader branches;
		const Shader leaves;
		const Shader exposure;
		const ShaderImage image;
	};
}
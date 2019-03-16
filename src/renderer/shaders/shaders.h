#pragma once

#include "shader.h"
#include "renderer/shaders/shaderImage.h"
#include "renderer/shaders/shaderExposure.h"
#include "renderer/shaders/shaderInteger.h"

namespace LRender {
	class Shaders final {
	public:
		Shaders();
		const Shader &getBranches() const;
		const Shader &getLeaves() const;
		const ShaderExposure &getExposure() const;
		const ShaderImage &getImage() const;
		const ShaderInteger &getInteger() const;

	private:
		const Shader branches;
		const Shader leaves;
		const ShaderExposure exposure;
		const ShaderImage image;
		const ShaderInteger integer;
	};
}
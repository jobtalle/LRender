#pragma once

#include "shader.h"
#include "renderer/shaders/shaderImage.h"
#include "renderer/shaders/shaderExposure.h"
#include "renderer/shaders/shaderInteger.h"
#include "renderer/shaders/shaderGeometryShadows.h"
#include "shaderLeavesShadows.h"

namespace LRender {
	class Shaders final {
	public:
		Shaders();
		const Shader &getBranches() const;
		const Shader &getLeaves() const;
		const Shader &getShadows() const;
		const ShaderExposure &getExposure() const;
		const ShaderImage &getImage() const;
		const ShaderInteger &getInteger() const;
		const ShaderGeometryShadows &getGeometryShadows() const;
		const ShaderLeavesShadows &getLeavesShadows() const;

	private:
		const Shader branches;
		const Shader leaves;
		const Shader shadows;
		const ShaderExposure exposure;
		const ShaderImage image;
		const ShaderInteger integer;
		const ShaderGeometryShadows geometryShadows;
		const ShaderLeavesShadows leavesShadows;
	};
}

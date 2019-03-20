#pragma once

#include "renderer/shaders/shader.h"

#include <string>

namespace LRender {
	class ShaderGeometryShadows final : public Shader {
	public:
		ShaderGeometryShadows();
		void setShadowMap(const GLuint texture) const;

	private:
		static const std::string SHADER_VERTEX;
		static const std::string SHADER_FRAGMENT;
		static const char *SHADOW_MAP_NAME;
		static const GLuint CHANNEL;

		GLuint shadowMapLocation;
	};
}
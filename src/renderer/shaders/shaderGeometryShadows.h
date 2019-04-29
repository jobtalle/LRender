#pragma once

#include "renderer/shaders/shader.h"

#include <string>

namespace LRender {
	class ShaderGeometryShadows final : public Shader {
	public:
		ShaderGeometryShadows();
		void setShadowMap(GLuint texture) const;
		void setColors(GLuint texture) const;

	private:
		static const std::string SHADER_VERTEX;
		static const std::string SHADER_FRAGMENT;
		static const std::string SHADER_SHADOWS;
		static const char *SHADOW_MAP_NAME;
		static const char *COLORS_NAME;
		static const GLuint CHANNEL_SHADOWS;
		static const GLuint CHANNEL_COLORS;

		GLuint shadowMapLocation;
		GLuint colorsLocation;
	};
}
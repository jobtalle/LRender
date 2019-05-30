#pragma once

#include "renderer/shaders/shader.h"

#include <string>

namespace LRender {
	class ShaderExposure final : public Shader {
	public:
		ShaderExposure();
		void setAgent(const unsigned int id) const;

	private:
		static const std::string SHADER_VERTEX;
		static const std::string SHADER_FRAGMENT;
		static const std::string SHADER_RANDOM;
		static const char *ID_NAME;

		GLuint idLocation;
	};
}
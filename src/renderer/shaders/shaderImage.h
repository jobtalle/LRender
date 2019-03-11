#pragma once

#include "renderer/shaders/shader.h"

#include <string>

namespace LRender {
	class ShaderImage final : public Shader {
	public:
		ShaderImage();
		void setImage(const GLuint texture) const;

	private:
		static const std::string SHADER_VERTEX;
		static const std::string SHADER_FRAGMENT;
		static const char *IMAGE_NAME;
		static const GLuint CHANNEL;

		GLuint imageLocation;
	};
}
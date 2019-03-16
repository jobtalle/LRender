#pragma once

#include "renderer/shaders/shader.h"

namespace LRender {
	class ShaderInteger final : public Shader {
	public:
		ShaderInteger();
		void setImage(const GLuint texture) const;

	private:
		static const std::string SHADER_VERTEX;
		static const std::string SHADER_FRAGMENT;
		static const char *IMAGE_NAME;
		static const GLuint CHANNEL;

		GLuint imageLocation;
	};
}
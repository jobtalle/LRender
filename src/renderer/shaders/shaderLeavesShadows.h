#pragma once

#include "renderer/shaders/shader.h"

namespace LRender {
	class ShaderLeavesShadows final : public Shader {
	public:
		ShaderLeavesShadows();
		void setShadowMap(const GLuint texture) const;

	private:
		static const std::string SHADER_VERTEX;
		static const std::string SHADER_FRAGMENT;
		static const char *SHADOW_MAP_NAME;
		static const GLuint CHANNEL;

		GLuint shadowMapLocation;
	};
}
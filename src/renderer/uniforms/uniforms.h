#pragma once

#include "glad/glad.h"

namespace LRender {
	class Uniforms {
	public:
		virtual ~Uniforms();
		virtual void update() const = 0;

	protected:
		Uniforms(const GLuint index);
		void updateBuffer(const GLsizeiptr payloadSize, const GLvoid *data) const;

	private:
		GLuint ubo;
	};
}
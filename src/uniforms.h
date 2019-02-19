#pragma once

#include "math/matrix.h"
#include "glad/glad.h"

namespace LRender {
	class Uniforms final {
	public:
		Uniforms();
		~Uniforms();
		void update() const;
		void setProjection(const Matrix &projection);

	private:
		GLuint ubo;

		struct payload {
			Matrix projection;
		} payload;
	};
}
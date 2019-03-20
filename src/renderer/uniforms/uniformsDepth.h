#pragma once

#include "renderer/uniforms/uniforms.h"
#include "math/matrix.h"

namespace LRender {
	class UniformsDepth final : public Uniforms {
	public:
		UniformsDepth();
		void update() const override final;
		void setProjection(const Matrix &projection);

	private:
		static const GLuint INDEX = 1;

		struct payload {
			Matrix projection;
		} payload;
	};
}
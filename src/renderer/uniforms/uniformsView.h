#pragma once

#include "renderer/uniforms/uniforms.h"
#include "math/matrix.h"

namespace LRender {
	class UniformsView final : public Uniforms {
	public:
		UniformsView();
		void update() const override final;
		void setProjection(const Matrix &projection);

	private:
		static const GLuint INDEX = 0;

		struct payload {
			Matrix projection;
		} payload;
	};
}
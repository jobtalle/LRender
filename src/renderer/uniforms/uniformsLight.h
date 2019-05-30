#pragma once

#include "renderer/uniforms/uniforms.h"
#include "math/vector.h"

namespace LRender {
	class UniformsLight final : public Uniforms {
	public:
		UniformsLight();
		void update() const override final;
		void setDirection(const Vector &direction);
		void setColor(const Vector &color);
		void setAmbient(float ambient);
		void setDiffuse(float diffuse);

	private:
		static const GLuint INDEX = 2;

		struct payload {
			Vector direction;
			float diffuse;
			Vector color;
			float ambient;
		} payload;
	};
}
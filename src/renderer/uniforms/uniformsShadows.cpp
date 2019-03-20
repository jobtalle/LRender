#include "uniformsShadows.h"

using namespace LRender;

const Matrix UniformsShadows::BIAS = Matrix().translate(1).scale(0.5f);

UniformsShadows::UniformsShadows() :
	Uniforms(INDEX) {

}

void UniformsShadows::update() const {
	updateBuffer(sizeof(payload), &payload);
}

void UniformsShadows::setProjection(const Matrix& projection) {
	payload.projection = projection;
	payload.sample = BIAS * projection;
}

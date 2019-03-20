#include "UniformsShadows.h"

using namespace LRender;

UniformsShadows::UniformsShadows() :
	Uniforms(INDEX) {
	
}

void UniformsShadows::update() const {
	updateBuffer(sizeof(payload), &payload);
}

void UniformsShadows::setProjection(const Matrix& projection) {
	payload.projection = projection;
}

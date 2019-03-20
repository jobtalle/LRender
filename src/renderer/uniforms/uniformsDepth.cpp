#include "uniformsDepth.h"

using namespace LRender;

UniformsDepth::UniformsDepth() :
	Uniforms(INDEX) {
	
}

void UniformsDepth::update() const {
	updateBuffer(sizeof(payload), &payload);
}

void UniformsDepth::setProjection(const Matrix& projection) {
	payload.projection = projection;
}

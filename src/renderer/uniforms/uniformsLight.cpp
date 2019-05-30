#include "uniformsLight.h"

using namespace LRender;

UniformsLight::UniformsLight() :
	Uniforms(INDEX) {
	
}

void UniformsLight::update() const {
	updateBuffer(sizeof(payload), &payload);
}

void UniformsLight::setDirection(const Vector& direction) {
	payload.direction = direction;
}

void UniformsLight::setColor(const Vector &color) {
	payload.color = color;
}

void UniformsLight::setAmbient(const float ambient) {
	payload.ambient = ambient;
}

void UniformsLight::setDiffuse(const float diffuse) {
	payload.diffuse = diffuse;
}
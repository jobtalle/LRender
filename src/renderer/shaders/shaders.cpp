#include "shaders.h"

using namespace LRender;

Shaders::Shaders() :
	branches(
		"LRender/glsl/vertexGeometry.glsl",
		"LRender/glsl/fragmentGeometry.glsl"),
	leaves(
		"LRender/glsl/vertexGeometry.glsl",
		"LRender/glsl/fragmentLeaf.glsl"),
	exposure(
		"LRender/glsl/vertexExposure.glsl",
		"LRender/glsl/fragmentExposure.glsl") {

}

const Shader &Shaders::getBranches() const {
	return branches;
}

const Shader &Shaders::getLeaves() const {
	return leaves;
}

const Shader &Shaders::getExposure() const {
	return exposure;
}

const ShaderImage& Shaders::getImage() const {
	return image;
}

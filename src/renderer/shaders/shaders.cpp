#include "shaders.h"

using namespace LRender;

Shaders::Shaders() :
	branches(
		"LRender/glsl/vertexGeometry.glsl",
		"LRender/glsl/fragmentGeometry.glsl"),
	leaves(
		"LRender/glsl/vertexGeometry.glsl",
		"LRender/glsl/fragmentLeaf.glsl") {

}

const Shader &Shaders::getBranches() const {
	return branches;
}

const Shader &Shaders::getLeaves() const {
	return leaves;
}

const ShaderExposure &Shaders::getExposure() const {
	return exposure;
}

const ShaderImage &Shaders::getImage() const {
	return image;
}

const ShaderInteger &Shaders::getInteger() const {
	return integer;
}
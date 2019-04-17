#include "shaders.h"

using namespace LRender;

Shaders::Shaders() :
	branches(
		"LRender/glsl/vertexGeometry.glsl",
		"LRender/glsl/fragmentGeometry.glsl"),
	leaves(
		"LRender/glsl/vertexGeometry.glsl",
		"LRender/glsl/fragmentLeaf.glsl"),
	shadows(
		"LRender/glsl/vertexShadows.glsl",
		"LRender/glsl/fragmentShadows.glsl"),
	geometrySelected(
		"LRender/glsl/vertexGeometry.glsl",
		"LRender/glsl/fragmentGeometrySelected.glsl") {

}

const Shader &Shaders::getBranches() const {
	return branches;
}

const Shader &Shaders::getLeaves() const {
	return leaves;
}

const Shader &Shaders::getShadows() const {
	return shadows;
}

const Shader &Shaders::getGeometrySelected() const {
	return geometrySelected;
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

const ShaderGeometryShadows& Shaders::getGeometryShadows() const {
	return geometryShadows;
}

const ShaderLeavesShadows& Shaders::getLeavesShadows() const {
	return leavesShadows;
}

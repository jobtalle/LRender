#include "shaderExposure.h"

using namespace LRender;

const std::string ShaderExposure::SHADER_VERTEX = "LRender/glsl/vertexExposure.glsl";
const std::string ShaderExposure::SHADER_FRAGMENT = "LRender/glsl/fragmentExposure.glsl";
const char *ShaderExposure::ID_NAME = "agent";

ShaderExposure::ShaderExposure() :
	Shader(SHADER_VERTEX, SHADER_FRAGMENT) {
	idLocation = glGetUniformLocation(program, ID_NAME);
}

void ShaderExposure::setAgent(const unsigned id) const {
	glUniform1ui(idLocation, id);
}


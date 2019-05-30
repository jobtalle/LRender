#include "shaderExposure.h"

using namespace LRender;

const std::string ShaderExposure::SHADER_VERTEX = "LRender/glsl/vertexExposure.glsl";
const std::string ShaderExposure::SHADER_FRAGMENT = "LRender/glsl/fragmentExposure.glsl";
const std::string ShaderExposure::SHADER_RANDOM = "LRender/glsl/random.glsl";
const char *ShaderExposure::ID_NAME = "agent";

ShaderExposure::ShaderExposure() :
	Shader(SHADER_VERTEX, SHADER_FRAGMENT, { SHADER_RANDOM }) {
	idLocation = glGetUniformLocation(program, ID_NAME);
}

void ShaderExposure::setAgent(const unsigned id) const {
	glUniform1ui(idLocation, id);
}


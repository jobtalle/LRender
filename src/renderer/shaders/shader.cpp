#include "shader.h"

#include <fstream>
#include <iostream>

using namespace LRender;

const std::string Shader::VERSION = "#version 440 core\n";
const std::vector<std::string> Shader::FILE_UNIFORM_BLOCKS = {
	"LRender/glsl/uniformsView.glsl",
	"LRender/glsl/uniformsLight.glsl",
	"LRender/glsl/uniformsShadows.glsl"
};

bool Shader::loadedPrefix = false;
std::string Shader::prefix;

Shader::Shader(
	const std::string &vertex,
	const std::string &fragment,
	const std::vector<std::string> &dependencies) {
	if(!loadedPrefix)
		loadPrefix();

	std::string prefixDependencies = prefix;

	for(const auto &dependency : dependencies)
		prefixDependencies += readFile(dependency);

	program = glCreateProgram();

	const GLuint shaderVertex = createShader(GL_VERTEX_SHADER, (prefixDependencies + readFile(vertex)).c_str());
	const GLuint shaderFragment = createShader(GL_FRAGMENT_SHADER, (prefixDependencies + readFile(fragment)).c_str());

	glAttachShader(program, shaderVertex);
	glAttachShader(program, shaderFragment);
	glLinkProgram(program);

	glDeleteShader(shaderVertex);
	glDeleteShader(shaderFragment);
}

Shader::Shader(const std::string &vertex, const std::string &fragment) :
	Shader(vertex, fragment, {}) {

}

Shader::~Shader() {
	glDeleteProgram(program);
}

void Shader::use() const {
	glUseProgram(program);
}

GLuint Shader::createShader(const GLenum type, const GLchar *code) {
	GLint success;
	GLuint shader = glCreateShader(type);

	glShaderSource(shader, 1, &code, nullptr);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if(!success) {
		char message[1024];

		glGetShaderInfoLog(shader, 1024, nullptr, message);
		
		std::cout << "Shader compilation failed:" << std::endl << message << std::endl;
	}

	return shader;
}

std::string Shader::readFile(const std::string &file) {
	std::string contents;
	std::ifstream source;
	std::string line;

	source.open(file);

	while(std::getline(source, line))
		contents += line;

	source.close();

	return contents;
}

void Shader::loadPrefix() {
	prefix = VERSION;

	for(auto &uboFile : FILE_UNIFORM_BLOCKS)
		prefix += readFile(uboFile);

	loadedPrefix = true;
}

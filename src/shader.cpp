#include "shader.h"

#include <fstream>
#include <iostream>

using namespace LRender;

const std::string Shader::VERSION = "#version 440 core\n";
const std::string Shader::FILE_UNIFORM_BLOCK = "glsl/uniforms.glsl";

Shader::Shader(const std::string &vertex, const std::string &fragment) {
	program = glCreateProgram();

	std::string uniforms = readFile(FILE_UNIFORM_BLOCK);
	GLuint shaderVertex = createShader(GL_VERTEX_SHADER, (VERSION + uniforms + readFile(vertex)).c_str());
	GLuint shaderFragment = createShader(GL_FRAGMENT_SHADER, (VERSION + uniforms + readFile(fragment)).c_str());

	glAttachShader(program, shaderVertex);
	glAttachShader(program, shaderFragment);
	glLinkProgram(program);

	glDeleteShader(shaderVertex);
	glDeleteShader(shaderFragment);
}

Shader::~Shader() {
	glDeleteProgram(program);
}

void Shader::use() const {
	glUseProgram(program);
}

GLuint Shader::createShader(const GLenum type, const GLchar *code) {
	GLuint shader;
	GLint success;

	shader = glCreateShader(type);

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
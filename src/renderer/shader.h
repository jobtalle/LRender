#pragma once

#include "glad/glad.h"

#include <string>
#include <vector>

namespace LRender {
	class Shader final {
	public:
		Shader(const std::string &vertex, const std::string &fragment);
		~Shader();
		void use() const;

	private:
		static const std::string VERSION;
		static const std::vector<std::string> FILE_UNIFORM_BLOCKS;
		static GLuint createShader(const GLenum type, const GLchar *code);
		static bool loadedPrefix;
		static std::string prefix;

		static void loadPrefix();
		static std::string readFile(const std::string &file);

		GLuint program;
	};
};
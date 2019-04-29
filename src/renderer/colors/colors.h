#pragma once

#include "glad/glad.h"

#include <string>

namespace LRender {
	class Colors final {
	public:
		Colors();
		~Colors();
		GLuint getBranches() const;
		GLuint getLeaves() const;
		GLuint getGround() const;

	private:
		static const std::string FILE_BRANCHES;
		static const std::string FILE_LEAVES;
		static const std::string FILE_GROUND;

		void load(GLuint texture, const std::string &file) const;

		GLuint branches;
		GLuint leaves;
		GLuint ground;
	};
}
#pragma once

#include "shader.h"

namespace LRender {
	class Shaders final {
	public:
		Shaders();
		const Shader &getBranches() const;
		const Shader &getLeaves() const;

	private:
		const Shader branches;
		const Shader leaves;
	};
}
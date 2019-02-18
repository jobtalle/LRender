#pragma once

#include <string>

namespace LRender {
	class Agent final {
	public:
		Agent(const std::string &symbols);

	private:
		const std::string symbols;
	};
}
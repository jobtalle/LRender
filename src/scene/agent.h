#pragma once

#include "math/vector.h"

#include <string>

namespace LRender {
	class Agent final {
	public:
		Agent(const LRender::Vector &position, const std::string &symbols);
		const Vector &getPosition() const;
		const std::string &getSymbols() const;

	private:
		const LRender::Vector position;
		const std::string symbols;
	};
}
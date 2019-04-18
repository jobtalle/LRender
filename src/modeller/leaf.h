#pragma once

#include "modeller/branch.h"

#include <list>

namespace LRender {
	class Leaf final {
		friend class AgentModel;

	public:
		Leaf();
		void addArea(float area);
		const std::list<Branch> &getBranches() const;
		float getArea() const;

	private:
		float area;
		std::list<Branch> branches;
	};
}
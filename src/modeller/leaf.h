#pragma once

#include "branch.h"

#include <list>

namespace LRender {
	class Leaf final {
		friend class AgentModel;

	public:
		Leaf();
		const std::list<Branch> &getBranches() const;

	private:
		std::list<Branch> branches;
	};
}
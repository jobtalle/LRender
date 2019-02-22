#pragma once

#include "branch.h"

#include <vector>

namespace LRender {
	class Leaf final {
	public:
		Leaf(const std::vector<Branch> &branches);
		const std::vector<Branch> &getBranches() const;

	private:
		std::vector<Branch> branches;
	};
}
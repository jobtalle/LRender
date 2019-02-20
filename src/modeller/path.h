#pragma once

#include "node.h"

#include <vector>

namespace LRender {
	class Path final {
	public:
		Path(const Node &root);
		const std::vector<Node> &getNodes() const;
		void add(const Node &node);
		void setRadius(const float radius);
		void attach(int index);
		void taper(std::vector<Path> &paths);
		size_t size() const;

	private:
		struct Attachment {
			Attachment(
				size_t node,
				size_t path);

			size_t node;
			size_t path;
		};

		std::vector<Node> nodes;
		std::vector<Attachment> attachments;
	};
}
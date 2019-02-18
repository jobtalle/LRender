#pragma once

#include "vertex.h"
#include "glad/glad.h"

#include <vector>
#include <stdint.h>

namespace LRender {
	class Model final {
	public:
		Model(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices);
		~Model();
		void draw() const;

	private:
		enum Buffer {
			BUFFER_VERTICES,
			BUFFER_INDICES,
			BUFFER_COUNT
		};

		GLuint vao;
		GLuint buffers[BUFFER_COUNT];

		void createBuffers();
		void upload(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices);
		void freeBuffers();
	};
};
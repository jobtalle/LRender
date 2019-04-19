#pragma once

#include "geometry.h"
#include "glad/glad.h"

#include <vector>

namespace LRender {
	class Model final {
	public:
		Model(const Geometry &geometry);
		~Model();
		void draw(bool wireframe = false) const;

	private:
		enum Buffer {
			BUFFER_VERTICES,
			BUFFER_INDICES,
			BUFFER_COUNT
		};

		GLuint vao;
		GLuint buffers[BUFFER_COUNT];
		GLsizei count;

		void createBuffers();
		void upload(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices);
		void freeBuffers();
	};
}
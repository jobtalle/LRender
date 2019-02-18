#pragma once

#include "scene/scene.h"
#include "math/vector.h"
#include "math/matrix.h"
#include "model.h"
#include "shader.h"

#include <memory>
#include <mutex>
#include <string>

namespace LRender {
	class Renderer final {
	public:
		Renderer();
		void setScene(std::shared_ptr<Scene> scene);
		void update();
		void render() const;

	private:
		static const std::string FILE_SHADER_VERTEX_GEOMETRY;
		static const std::string FILE_SHADER_FRAGMENT_GEOMETRY;
		static bool initialized;

		std::unique_ptr<Shader> shaderGeometry;
		std::mutex access;
		std::shared_ptr<Scene> nextScene;
		std::vector<Model> models;

		static void initializeGL();

		void loadScene(const Scene *scene);
	};
};
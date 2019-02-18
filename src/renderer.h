#pragma once

#include "scene/scene.h"
#include "math/vector.h"
#include "math/matrix.h"
#include "model.h"

#include <memory>
#include <mutex>

namespace LRender {
	class Renderer final {
	public:
		Renderer();
		void setScene(std::shared_ptr<Scene> scene);
		void update();
		void render() const;

	private:
		static bool initialized;

		std::mutex access;
		std::shared_ptr<Scene> nextScene;
		std::vector<Model> models;

		static void initializeGL();

		void loadScene(const Scene *scene);
	};
};
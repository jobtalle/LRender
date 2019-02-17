#pragma once

#include "scene/scene.h"

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

		static void initializeGL();

		void loadScene(const Scene *scene);
	};
};
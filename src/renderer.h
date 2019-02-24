#pragma once

#include "scene/scene.h"
#include "math/vector.h"
#include "math/matrix.h"
#include "model.h"
#include "shaders.h"
#include "uniforms.h"
#include "glFunctions.h"
#include "orbit.h"

#include <memory>
#include <mutex>
#include <string>
#include <random>

namespace LRender {
	class Renderer final {
	public:
		enum MouseButton {
			MOUSE_DRAG,
			MOUSE_PAN
		};

		Renderer(const size_t width, const size_t height);
		void setScene(std::shared_ptr<Scene> scene);
		void update();
		void render();
		void setSize(const size_t width, const size_t height);
		void mouseMove(const size_t x, const size_t y);
		void mousePress(const MouseButton button);
		void mouseRelease(const MouseButton button);
		void scrollUp();
		void scrollDown();

	private:
		static const float PROJECTION_ANGLE;
		static const float Z_NEAR;
		static const float Z_FAR;
		static const std::string FILE_SHADER_VERTEX_GEOMETRY;
		static const std::string FILE_SHADER_FRAGMENT_GEOMETRY;

		std::mt19937 randomizer;
		GLFunctions gl;
		Shaders shaders;
		Uniforms uniforms;
		Orbit orbit;
		Matrix projection;
		float aspect;
		std::mutex access;
		std::shared_ptr<Scene> nextScene;
		std::vector<std::shared_ptr<Model>> branches;
		std::vector<std::shared_ptr<Model>> leaves;

		void loadScene(const Scene *scene);
		void updateProjection();
	};
};
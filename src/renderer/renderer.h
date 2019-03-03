#pragma once

#include "scene/scene.h"
#include "math/vector.h"
#include "math/matrix.h"
#include "model/model.h"
#include "renderer/shaders/shaders.h"
#include "renderer/glFunctions.h"
#include "renderer/orbit.h"
#include "renderer/passes/renderPass.h"
#include "modeller/terrainModel.h"
#include "modeller/agentModel.h"
#include "report/report.h"

#include <memory>
#include <mutex>
#include <string>
#include <random>
#include <functional>

namespace LRender {
	class Renderer final {
	public:
		enum MouseButton {
			MOUSE_DRAG,
			MOUSE_PAN
		};

		enum RenderMode {
			RENDER_DEFAULT,
			RENDER_WIREFRAME
		};

		Renderer(const size_t width, const size_t height);
		void setMode(const RenderMode mode);
		void setScene(
			std::shared_ptr<Scene> scene,
			std::function<void(Report&)> callback);
		void update();
		void render();
		void setSize(const size_t width, const size_t height);
		void mouseMove(const size_t x, const size_t y);
		void mousePress(const MouseButton button);
		void mouseRelease(const MouseButton button);
		void scrollUp();
		void scrollDown();

	private:
		struct RenderTask {
			RenderTask(
				std::shared_ptr<Scene> scene,
				std::function<void(Report&)> report);

			std::shared_ptr<Scene> scene;
			std::function<void(Report&)> report;
		};

		static const float PROJECTION_ANGLE;
		static const float Z_NEAR;
		static const float Z_FAR;
		static const Vector CLEAR_COLOR;

		RenderMode mode;
		RenderMode nextMode;
		std::mt19937 randomizer;
		GLFunctions gl;
		Shaders shaders;
		Orbit orbit;
		Matrix projection;
		float aspect;
		std::unique_ptr<RenderPass> updatePass;
		std::mutex access;
		std::vector<RenderTask> renderTasks;
		std::vector<AgentModel> agents;
		std::vector<TerrainModel> terrains;

		void loadScene(const Scene *scene, Report &report);
		void updateProjection();
	};
};
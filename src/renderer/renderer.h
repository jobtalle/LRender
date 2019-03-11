#pragma once

#include "scene/scene.h"
#include "math/vector.h"
#include "math/matrix.h"
#include "renderer/shaders/shaders.h"
#include "renderer/glFunctions.h"
#include "renderer/orbit.h"
#include "renderer/passes/renderPass.h"
#include "modeller/terrainModel.h"
#include "modeller/agentModel.h"
#include "report/report.h"

#include <memory>
#include <mutex>
#include <random>

namespace LRender {
	class Renderer final {
	public:
		class Task;

		enum MouseButton {
			DRAG,
			PAN
		};

		enum Mode {
			DEFAULT,
			WIREFRAME
		};

		Renderer(const size_t width, const size_t height);
		void enqueue(const std::shared_ptr<Task>& task);
		void update();
		void bindDefault();
		void render() const;
		void render(RenderPass &pass) const;
		void center();
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
		static const Vector CLEAR_COLOR;

		std::mt19937 randomizer;
		GLFunctions gl;
		Shaders shaders;
		Orbit orbit;
		Matrix projection;
		Vector sceneCenter;
		float aspect;
		size_t width;
		size_t height;
		std::shared_ptr<RenderPass> updatePass;
		std::mutex access;
		std::vector<AgentModel> agents;
		std::vector<TerrainModel> terrains;
		std::vector<std::shared_ptr<Task>> tasks;

		void setMode(const Mode mode);
		void setPass(const std::shared_ptr<RenderPass> &pass);
		void loadScene(const Scene *scene, Report *report = nullptr);
		void updateProjection();
	};
}
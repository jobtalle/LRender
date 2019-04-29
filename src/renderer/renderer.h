#pragma once

#include "scene/scene.h"
#include "math/vector.h"
#include "math/matrix.h"
#include "renderer/shaders/shaders.h"
#include "renderer/glFunctions.h"
#include "renderer/orbit.h"
#include "renderer/target/renderTargetUint.h"
#include "renderer/passes/renderPass.h"
#include "modeller/terrainModel.h"
#include "modeller/agentModel.h"
#include "report/report.h"
#include "renderer/colors/colors.h"
#include "lparse.h"
 
#include <memory>
#include <mutex>

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

		Renderer(size_t width, size_t height);
		void enqueue(const std::shared_ptr<Task> &task);
		void update();
		void bindDefault() const;
		void render() const;
		void render(RenderPass &pass) const;
		void center();
		void focus();
		void setSize(size_t width, size_t height);
		void mouseMove(size_t x, size_t y);
		void mousePress(MouseButton button);
		void mouseRelease(MouseButton button);
		void scrollUp();
		void scrollDown();
		void setSelected(int selected);
		int getSelected() const;
		size_t getWidth() const;
		size_t getHeight() const;
		void setLastReport(const std::shared_ptr<Report> &report);
		const std::shared_ptr<Report> &getLastReport() const;
		const Colors &getColors() const;

		static const float Z_NEAR;
		static const float Z_FAR;

	private:
		struct AgentBatch {
			AgentBatch(
				std::vector<Agent>::const_iterator begin,
				std::vector<Agent>::const_iterator end,
				LParse::Randomizer randomizer);

			const std::vector<Agent>::const_iterator begin;
			const std::vector<Agent>::const_iterator end;
			LParse::Randomizer randomizer;
			std::vector<AgentModel> models;
			std::vector<ReportAgent> reports;
		};

		static const float PROJECTION_ANGLE;
		static const size_t BATCH_SIZE = 100;

		bool mouseMoved = false;
		int selected = -1;
		GLFunctions gl;
		Colors colors;
		Shaders shaders;
		Orbit orbit;
		Matrix projection;
		Vector sceneCenter;
		float aspect;
		size_t width;
		size_t height;
		size_t mouseX;
		size_t mouseY;
		std::shared_ptr<RenderPass> updatePass;
		std::mutex access;
		std::vector<AgentModel> agents;
		std::vector<TerrainModel> terrains;
		std::vector<std::shared_ptr<Task>> tasks;
		std::shared_ptr<Report> lastReport;

		static void modelBatches(
			std::vector<AgentBatch>::iterator begin,
			std::vector<AgentBatch>::iterator end,
			bool highQuality);
		void setMode(Mode mode);
		void setPass(const std::shared_ptr<RenderPass> &pass);
		void loadScene(
			const Scene *scene,
			size_t threadCount,
			bool highQuality,
			LParse::Randomizer &randomizer,
			Report *report = nullptr);
		void updateProjection();
	};
}

#pragma once

#include "scene/scene.h"
#include "math/vector.h"
#include "math/matrix.h"
#include "model.h"
#include "shader.h"
#include "uniforms.h"
#include "glFunctions.h"

#include <memory>
#include <mutex>
#include <string>

namespace LRender {
	class Renderer final {
	public:
		Renderer(const size_t width, const size_t height);
		void setScene(std::shared_ptr<Scene> scene);
		void update();
		void render() const;
		void setSize(const size_t width, const size_t height);
		void mouseMove(const size_t x, const size_t y);
		void mousePress();
		void mouseRelease();

	private:
		static const float PITCH_MIN;
		static const float PITCH_MAX;
		static const float RADIANS_PER_PIXEL;
		static const float PROJECTION_ANGLE;
		static const float Z_NEAR;
		static const float Z_FAR;
		static const std::string FILE_SHADER_VERTEX_GEOMETRY;
		static const std::string FILE_SHADER_FRAGMENT_GEOMETRY;

		GLFunctions gl;
		Uniforms uniforms;
		Matrix view;
		Matrix projection;
		float aspect;
		Shader *shader;
		bool dragging;
		size_t mouseX;
		size_t mouseY;
		float viewAngle;
		float viewPitch;
		std::unique_ptr<Shader> shaderGeometry;
		std::mutex access;
		std::shared_ptr<Scene> nextScene;
		std::vector<std::shared_ptr<Model>> models;

		void loadScene(const Scene *scene);
		void updateUniforms();
		void updateProjection();
		void updateView();
	};
};
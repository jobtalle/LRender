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

	private:
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
		std::unique_ptr<Shader> shaderGeometry;
		std::mutex access;
		std::shared_ptr<Scene> nextScene;
		std::vector<std::shared_ptr<Model>> models;

		void loadScene(const Scene *scene);
		void updateUBO() const;
		void updateProjection();
	};
};
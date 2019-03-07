#pragma once

#include "scene/terrain.h"
#include "model/model.h"

#include <memory>

namespace LRender {
	class TerrainModel final {
	public:
		TerrainModel(const Terrain &terrain);
		const Model &getModel() const;

	private:
		static const float RESOLUTION;

		std::unique_ptr<Model> model;

		void build(const Terrain &terrain);
	};
}
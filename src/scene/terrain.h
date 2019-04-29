#pragma once

#include <functional>
#include <memory>

namespace LRender {
	class Terrain final {
	public:
		Terrain(
			float width,
			float height,
			std::shared_ptr<const void> terrainSource,
			std::function<float(float x, float y)> get);
		float getWidth() const;
		float getHeight() const;
		float getY(float x, float y) const;

	private:
		const std::shared_ptr<const void> terrainSource;
		const std::function<float(float x, float y)> get;
		const float width;
		const float height;
	};
}
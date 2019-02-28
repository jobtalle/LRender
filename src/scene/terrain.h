#pragma once

#include <functional>
#include <vector>
#include <memory>

namespace LRender {
	class Terrain final {
	public:
		Terrain(
			const float width,
			const float height,
			const std::shared_ptr<void> terrainSource,
			const std::function<float(const float x, const float y)> get);
		float getWidth() const;
		float getHeight() const;
		float getY(const float x, const float y) const;

	private:
		const std::shared_ptr<void> terrainSource;
		const std::function<float(const float x, const float y)> get;
		const float width;
		const float height;
	};
}
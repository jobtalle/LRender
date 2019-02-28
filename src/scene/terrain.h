#pragma once

#include <functional>

namespace LRender {
	class Terrain final {
	public:
		Terrain(
			const float width,
			const float height,
			const std::function<float(const float x, const float y)> get);
		float getWidth() const;
		float getHeight() const;

	private:
		const std::function<float(const float x, const float y)> get;
		const float width;
		const float height;
	};
}
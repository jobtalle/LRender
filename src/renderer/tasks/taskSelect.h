#pragma once

#include "renderer/tasks/task.h"

namespace LRender {
	class Renderer::Task::Select final : public Task {
	public:
		Select(float x, float y);
		void perform(Renderer &renderer) override final;

	private:
		const float x;
		const float y;
	};
}
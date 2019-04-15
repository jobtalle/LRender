#pragma once

#include "renderer/tasks/task.h"

#include <future>

namespace LRender {
	class Renderer::Task::Select final : public Task {
	public:
		Select(float x, float y);
		void perform(Renderer &renderer) override final;
		int getSelected();

	private:
		const float x;
		const float y;

		std::promise<int> selected;
		std::future<int> selectedValue;
	};
}
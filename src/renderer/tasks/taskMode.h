#pragma once

#include "renderer/tasks/task.h"

namespace LRender {
	class Renderer::Task::Mode final : public Renderer::Task {
	public:
		Mode(const Renderer::Mode mode);
		void perform(Renderer &renderer) const override final;

	private:
		Renderer::Mode mode;
	};
};
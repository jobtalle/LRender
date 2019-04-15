#include "taskSelect.h"
#include "renderer/passes/renderPassMasks.h"

using namespace LRender;

Renderer::Task::Select::Select(float x, float y) :
	x(x),
	y(y) {
	
}

void Renderer::Task::Select::perform(Renderer &renderer) {
	auto pass = RenderPassMasks(renderer.getWidth(), renderer.getHeight());

	renderer.render(pass);
	renderer.setSelected(pass.sample(x, y));
	renderer.setMode(Renderer::Mode::DEFAULT);
}

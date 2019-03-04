#include "taskMode.h"

using namespace LRender;

Renderer::Task::Mode::Mode(const Renderer::Mode mode) :
	mode(mode) {

}

void Renderer::Task::Mode::perform(Renderer &renderer) {
	renderer.setMode(mode);
}
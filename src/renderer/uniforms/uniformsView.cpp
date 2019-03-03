#include "uniformsView.h"

using namespace LRender;

UniformsView::UniformsView() :
	Uniforms(INDEX) {

}

void UniformsView::update() const {
	updateBuffer(sizeof(payload), &payload);
}

void UniformsView::setProjection(const Matrix &projection) {
	payload.projection = projection;
}
#include "glFunctions.h"
#include "glad/glad.h"

using namespace LRender;

bool GLFunctions::initialized = false;

GLFunctions::GLFunctions() {
	if(!initialized) {
		gladLoadGL();

		initialized = true;
	}
}
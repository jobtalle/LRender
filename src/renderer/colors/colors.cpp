#include "colors.h"
#include "lodepng/lodepng.h"

using namespace LRender;

const std::string Colors::FILE_BRANCHES = "LRender/images/branches.png";
const std::string Colors::FILE_LEAVES = "LRender/images/leaves.png";
const std::string Colors::FILE_GROUND = "LRender/images/ground.png";

Colors::Colors() {
	glGenTextures(1, &branches);
	glGenTextures(1, &leaves);
	glGenTextures(1, &ground);

	load(branches, FILE_BRANCHES);
	load(leaves, FILE_LEAVES);
	load(ground, FILE_GROUND);
}

Colors::~Colors() {
	glDeleteTextures(1, &branches);
	glDeleteTextures(1, &leaves);
	glDeleteTextures(1, &ground);
}

GLuint Colors::getBranches() const {
	return branches;
}

GLuint Colors::getLeaves() const {
	return leaves;
}

GLuint Colors::getGround() const {
	return ground;
}

void Colors::load(GLuint texture, const std::string &file) const {
	std::vector<unsigned char> image;
	unsigned width, height;

	lodepng::decode(image, width, height, file);


}

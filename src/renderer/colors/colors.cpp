#include "colors.h"
#include "lodepng/lodepng.h"

using namespace LRender;

const std::string Colors::FILE_BRANCHES = "LRender/images/branches.png";
const std::string Colors::FILE_BRANCHES_SELECTED = "LRender/images/branchesSelected.png";
const std::string Colors::FILE_LEAVES = "LRender/images/leaves.png";
const std::string Colors::FILE_LEAVES_SELECTED = "LRender/images/leavesSelected.png";
const std::string Colors::FILE_GROUND = "LRender/images/ground.png";

Colors::Colors() {
	glGenTextures(1, &branches);
	glGenTextures(1, &branchesSelected);
	glGenTextures(1, &leaves);
	glGenTextures(1, &leavesSelected);
	glGenTextures(1, &ground);

	load(branches, FILE_BRANCHES);
	load(branchesSelected, FILE_BRANCHES_SELECTED);
	load(leaves, FILE_LEAVES);
	load(leavesSelected, FILE_LEAVES_SELECTED);
	load(ground, FILE_GROUND);
}

Colors::~Colors() {
	glDeleteTextures(1, &branches);
	glDeleteTextures(1, &branchesSelected);
	glDeleteTextures(1, &leaves);
	glDeleteTextures(1, &leavesSelected);
	glDeleteTextures(1, &ground);
}

GLuint Colors::getBranches() const {
	return branches;
}

GLuint Colors::getBranchesSelected() const {
	return branchesSelected;
}

GLuint Colors::getLeaves() const {
	return leaves;
}

GLuint Colors::getLeavesSelected() const {
	return leavesSelected;
}

GLuint Colors::getGround() const {
	return ground;
}

void Colors::load(const GLuint texture, const std::string &file) const {
	std::vector<unsigned char> image;
	unsigned width, height;

	lodepng::decode(image, width, height, file);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

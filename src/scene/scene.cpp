#include "scene.h"

using namespace LRender;

Scene::Scene() {

}

void Scene::addAgent(const Agent &agent) {
	agents.push_back(agent);
}
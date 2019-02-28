#include "scene.h"

using namespace LRender;

Scene::Scene(const Terrain &terrain) :
	terrain(terrain) {

}

void Scene::addAgent(const Agent &agent) {
	agents.push_back(agent);
}

const Terrain &Scene::getTerrain() const {
	return terrain;
}

const std::vector<Agent> &Scene::getAgents() const {
	return agents;
}
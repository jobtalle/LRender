#include "agent.h"
#include <utility>

using namespace LRender;

Agent::Agent(const Vector &position, std::string symbols) :
	position(position),
	symbols(std::move(symbols)) {

}

const Vector &Agent::getPosition() const {
	return position;
}

const std::string &Agent::getSymbols() const {
	return symbols;
}
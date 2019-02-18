#include "agent.h"

using namespace LRender;

Agent::Agent(const LRender::Vector &position, const std::string &symbols) :
	position(position),
	symbols(symbols) {

}

const Vector &Agent::getPosition() const {
	return position;
}

const std::string &Agent::getSymbols() const {
	return symbols;
}
#include "agent.h"
#include <iostream>
using namespace LRender;

Agent::Agent(const std::string &symbols) :
	symbols(symbols) {
	std::cout << symbols << std::endl;
}
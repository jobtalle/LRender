#include "agentModel.h"
#include "shapes/tube.h"
#include "shapes/leaf.h"
#include "../math/vector.h"
#include "../math/quaternion.h"
#include "../math/constants.h"

#include <cstdint>

using namespace LRender;

const float AgentModel::TURTLE_STEP = 0.05f;
const float AgentModel::TURTLE_ANGLE = 0.3;
const size_t AgentModel::TUBE_PRECISION = 7;

AgentModel::AgentModel(const Agent &agent, const RadiusSampler &radiusSampler, std::mt19937 &randomizer) :
	radiusSampler(radiusSampler) {
	build(agent, randomizer);
}

std::shared_ptr<Model> AgentModel::getBranches() {
	return modelBranches;
}

std::shared_ptr<Model> AgentModel::getLeaves() {
	return modelLeaves;
}

void AgentModel::build(const Agent &agent, std::mt19937 &randomizer) {
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	std::list<Branch> branches;
	std::list<Leaf> leaves;
	Node node(agent.getPosition(), std::uniform_real_distribution<float>(0, Constants::PI * 2)(randomizer));
	
	traceBranch(
		nullptr,
		false,
		branches,
		leaves,
		node,
		agent.getSymbols().begin(),
		agent.getSymbols().end());

	for(auto branch : branches)
		Shape::Tube::model(
			vertices,
			indices,
			Vector(0.53f, 0.39f, 0.78f),
			radiusSampler,
			TUBE_PRECISION,
			branch);

	for(auto leaf : leaves) for(auto branch : leaf.getBranches()) {
		for(auto &child : branch.getChildren())
			Shape::Leaf::model(
				vertices,
				indices,
				Vector(0.3f, 0.8f, 0.6f),
				branch.getNodes().begin() + child.index,
				branch.getNodes().end(),
				child.child->getNodes().begin(),
				child.child->getNodes().end());

		Shape::Tube::model(
			vertices,
			indices,
			Vector(0.3f, 0.8f, 0.6f),
			RadiusSampler(0.05f),
			TUBE_PRECISION,
			branch);
	}

	modelBranches.reset(new Model(vertices, indices));
}

Branch *AgentModel::traceBranch(
	Branch *parent,
	const bool leaf,
	std::list<Branch> &branches,
	std::list<Leaf> &leaves,
	Node node,
	std::string::const_iterator &at,
	const std::string::const_iterator &last) {
	Branch branch(node);
	Branch *lastChild = nullptr;

	while(at != last) {
		switch(*at++) {
		case SYM_LEAF:
			if(!leaf) {
				leaves.push_back(Leaf());

				branch.add(lastChild = traceBranch(&branch, true, (--leaves.end())->branches, leaves, node, at, last));

				break;
			}
		case SYM_BRANCH_OPEN:
			branch.add(lastChild = traceBranch(&branch, leaf, branches, leaves, node, at, last));

			break;
		case SYM_BRANCH_CLOSE:
			goto end;
		case SYM_PITCH_INCREMENT:
			node.pitch(TURTLE_ANGLE);
			
			break;
		case SYM_PITCH_DECREMENT:
			node.pitch(-TURTLE_ANGLE);

			break;
		case SYM_ROLL_INCREMENT:
			node.roll(TURTLE_ANGLE);

			break;
		case SYM_ROLL_DECREMENT:
			node.roll(-TURTLE_ANGLE);

			break;
		default:
			if(*(at - 1) >= SYM_STEP_MIN && *(at - 1) <= SYM_STEP_MAX) {
				branch.add(node.extrude(TURTLE_STEP));

				if(lastChild) {
					lastChild->setRoot({ *(branch.getNodes().end() - 2), *(branch.getNodes().end() - 1) });

					lastChild = nullptr;
				}
			}

			break;
		}
	}

end:
	if(branch.size() > 1) {
		branch.calculateTopDist();
		branches.push_back(branch);
		
		if(parent)
			parent->calculateTopDist(branch.getNodes()[0].topDist);
		
		if(lastChild)
			lastChild->setRoot({ *(branch.getNodes().end() - 1) });

		return &*(--branches.end());
	}

	return nullptr;
}
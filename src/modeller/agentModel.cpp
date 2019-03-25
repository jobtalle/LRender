#include "modeller/agentModel.h"
#include "modeller/shapes/branch.h"
#include "modeller/shapes/leaf.h"
#include "modeller/shapes/seed.h"
#include "math/vector.h"
#include "math/constants.h"

using namespace LRender;

const float AgentModel::TURTLE_STEP = 0.05f;
const float AgentModel::TURTLE_ANGLE = 0.2;
const size_t AgentModel::TUBE_PRECISION = 7;

AgentModel::AgentModel(const Agent &agent, LParse::Randomizer &randomizer) :
	minimum(agent.getPosition()),
	maximum(agent.getPosition()),
	area(0) {
	build(agent, randomizer);
}

const Model &AgentModel::getBranches() const {
	return *modelBranches;
}

const Model &AgentModel::getLeaves() const {
	return *modelLeaves;
}

const Vector &AgentModel::getMinimum() const {
	return minimum;
}

const Vector &AgentModel::getMaximum() const {
	return maximum;
}

float AgentModel::getArea() const {
	return area;
}

void AgentModel::build(const Agent &agent, LParse::Randomizer &randomizer) {
	RadiusSampler radiusSampler(0.1f);
	Geometry geometryBranches;
	Geometry geometryLeaves;
	std::list<Branch> branches;
	std::list<Leaf> leaves;
	std::list<Seed> seeds;
	Node node(agent.getPosition(), randomizer.makeFloat(0, Constants::PI * 2));
	
	auto at = agent.getSymbols().begin();
	
	traceBranch(
		nullptr,
		false,
		branches,
		leaves,
		seeds,
		node,
		at,
		agent.getSymbols().end());
	
	for(const auto &branch : branches)
		Shape::Branch::model(
			geometryBranches.vertices,
			geometryBranches.indices,
			Vector(0.53f, 0.39f, 0.78f),
			radiusSampler,
			TUBE_PRECISION,
			branch);

	for(auto &leaf : leaves) {
		for(const auto &branch : leaf.getBranches()) {
			Shape::Branch::model(
				geometryBranches.vertices,
				geometryBranches.indices,
				Vector(0.3f, 0.8f, 0.6f),
				radiusSampler,
				TUBE_PRECISION,
				branch);

			for(const auto &child : branch.getBranches())
				leaf.addArea(Shape::Leaf::model(
					geometryLeaves.vertices,
					geometryLeaves.indices,
					Vector(0.3f, 0.8f, 0.6f),
					branch.getNodes().begin() + child.index,
					branch.getNodes().end(),
					child.child->getNodes().begin(),
					child.child->getNodes().end()));
		}

		area += leaf.getArea();
	}

	for(const auto &seed : seeds)
		Shape::Seed::model(
			geometryBranches.vertices,
			geometryBranches.indices,
			Vector(0.6f, 0, 0),
			radiusSampler,
			seed);

	modelBranches = std::make_unique<Model>(geometryBranches);
	modelLeaves = std::make_unique<Model>(geometryLeaves);
}

Branch *AgentModel::traceBranch(
	Branch *const parent,
	const bool leaf,
	std::list<Branch> &branches,
	std::list<Leaf> &leaves,
	std::list<Seed> &seeds,
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

				branch.add(lastChild = traceBranch(&branch, true, (--leaves.end())->branches, leaves, seeds, node, at, last));

				break;
			}
		case SYM_BRANCH_OPEN:
			branch.add(lastChild = traceBranch(&branch, leaf, branches, leaves, seeds, node, at, last));

			break;
		case SYM_BRANCH_CLOSE:
			goto end;
		case SYM_SEED:
			if(!leaf) {
				seeds.push_back(Seed(node.position));

				branch.add(&*--seeds.end());
			}

			break;
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

				if(node.position.x < minimum.x)
					minimum.x = node.position.x;
				else if(node.position.x > maximum.x)
					maximum.x = node.position.x;

				if(node.position.y < minimum.y)
					minimum.y = node.position.y;
				else if(node.position.y > maximum.y)
					maximum.y = node.position.y;

				if(node.position.z < minimum.z)
					minimum.z = node.position.z;
				else if(node.position.z > maximum.z)
					maximum.z = node.position.z;

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

		return &*--branches.end();
	}

	return nullptr;
}

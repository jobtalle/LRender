#include "modeller/agentModel.h"
#include "modeller/shapes/branch.h"
#include "modeller/shapes/leaf.h"
#include "modeller/shapes/seed.h"
#include "math/vector.h"
#include "math/constants.h"
#include "shapes/standardLeaf.h"

using namespace LRender;

const float AgentModel::TURTLE_STEP = 0.05f;
const float AgentModel::TURTLE_ANGLE = 0.2;
const size_t AgentModel::TUBE_PRECISION_LOW = 3;
const size_t AgentModel::TUBE_PRECISION_HIGH = 5;

AgentModel::AgentModel(
	const Agent &agent,
	const bool highQuality,
	LParse::Randomizer &randomizer) :
	minimum(agent.getPosition()),
	maximum(agent.getPosition()) {
	build(agent, highQuality, randomizer);
}

const Model &AgentModel::getBranches() const {
	return *modelBranches;
}

const Model &AgentModel::getLeaves() const {
	return *modelLeaves;
}

const std::vector<Vector> &AgentModel::getSeedPositions() const {
	return seedPositions;
}

const std::vector<float> &AgentModel::getLeafAreas() const {
	return leafAreas;
}

const Vector &AgentModel::getMinimum() const {
	return minimum;
}

const Vector &AgentModel::getMaximum() const {
	return maximum;
}

const Vector &AgentModel::getAverage() const {
	return average;
}

void AgentModel::makeModels() {
	modelBranches = std::make_shared<Model>(*geometryBranches);
	modelLeaves = std::make_shared<Model>(*geometryLeaves);

	geometryBranches = nullptr;
	geometryLeaves = nullptr;
}

void AgentModel::build(
	const Agent &agent,
	const bool highQuality,
	LParse::Randomizer &randomizer) {
	const RadiusSampler radiusSampler(0.1f);
	std::list<Branch> branches;
	std::list<Leaf> leaves;
	std::list<StandardLeaf> standardLeaves;
	std::list<Seed> seeds;
	const Node node(agent.getPosition(), randomizer.makeFloat(0, Constants::PI * 2));

	geometryBranches = std::make_shared<Geometry>();
	geometryLeaves = std::make_shared<Geometry>();

	auto at = agent.getSymbols().begin();
	const auto fertility = 1.0f - agent.getPosition().y;
	const auto tubePrecision = highQuality ? TUBE_PRECISION_HIGH : TUBE_PRECISION_LOW;

	symbolCount = 0;
	average = Vector(0, 0, 0);

	traceBranch(
		nullptr,
		false,
		branches,
		leaves,
		standardLeaves,
		seeds,
		node,
		at,
		agent.getSymbols().end());

	average /= symbolCount;
	
	for(const auto &branch : branches)
		Shape::Branch::model(
			geometryBranches->vertices,
			geometryBranches->indices,
			radiusSampler,
			fertility,
			tubePrecision,
			branch);

	for(auto &leaf : leaves) {
		for(const auto &branch : leaf.getBranches()) {
			Shape::Branch::model(
				geometryBranches->vertices,
				geometryBranches->indices,
				radiusSampler,
				fertility,
				tubePrecision,
				branch);

			for(const auto &child : branch.getBranches())
				leaf.addArea(Shape::Leaf::model(
					geometryLeaves->vertices,
					geometryLeaves->indices,
					fertility,
					branch.getNodes().begin() + child.index,
					branch.getNodes().end(),
					child.child->getNodes().begin(),
					child.child->getNodes().end()));
		}

		leafAreas.emplace_back(leaf.getArea());
	}

	for(const auto &seed : seeds) {
		seedPositions.push_back(seed.getPosition());

		if(!highQuality)
			continue;

		Shape::Seed::model(
			geometryBranches->vertices,
			geometryBranches->indices,
			radiusSampler,
			seed);
	}

	for(const auto &standardLeaf : standardLeaves) {
		switch(standardLeaf.getType()) {
		case StandardLeaf::Type::A:
			leafAreas.emplace_back(Shape::StandardLeaf::modelA(
				geometryLeaves->vertices,
				geometryLeaves->indices,
				fertility,
				standardLeaf.getPosition(),
				standardLeaf.getOrientation()));

			break;
		}
	}
}

Branch *AgentModel::traceBranch(
	Branch *const parent,
	const bool leaf,
	std::list<Branch> &branches,
	std::list<Leaf> &leaves,
	std::list<StandardLeaf> &standardLeaves,
	std::list<Seed> &seeds,
	Node node,
	std::string::const_iterator &at,
	const std::string::const_iterator &last) {
	Branch branch(node);
	Branch *lastChild = nullptr;

	while(at != last) {
		switch(*at++) {
		case LParse::Legend::LEAF_OPEN:
			if(!leaf) {
				leaves.emplace_back();

				const auto traced = traceBranch(
					&branch, 
					true,
					(--leaves.end())->branches,
					leaves,
					standardLeaves,
					seeds,
					node,
					at,
					last);

				if(traced)
					branch.add(lastChild = traced);

				break;
			}
		case LParse::Legend::BRANCH_OPEN:
		{
			const auto traced = traceBranch(
				&branch,
				leaf,
				branches,
				leaves,
				standardLeaves,
				seeds,
				node,
				at,
				last);

			if(traced)
				branch.add(lastChild = traced);
		}

			break;
		case LParse::Legend::BRANCH_CLOSE:
			goto end;
		case LParse::Legend::LEAF_A:
			if(!leaf)
				standardLeaves.emplace_back(StandardLeaf::Type::A, node.position, node.getHeading());

			break;
		case LParse::Legend::SEED:
			if(!leaf) {
				seeds.emplace_back(node.position);

				branch.add(&*--seeds.end());
			}

			break;
		case LParse::Legend::PITCH_INCREMENT:
			node.pitch(TURTLE_ANGLE);
			
			break;
		case LParse::Legend::PITCH_DECREMENT:
			node.pitch(-TURTLE_ANGLE);

			break;
		case LParse::Legend::ROLL_INCREMENT:
			node.roll(TURTLE_ANGLE);

			break;
		case LParse::Legend::ROLL_DECREMENT:
			node.roll(-TURTLE_ANGLE);

			break;
		case LParse::Legend::YAW_INCREMENT:
			node.yaw(TURTLE_ANGLE);

			break;
		case LParse::Legend::YAW_DECREMENT:
			node.yaw(-TURTLE_ANGLE);

			break;
		default:
			if(*(at - 1) >= LParse::Legend::STEP_MIN && *(at - 1) <= LParse::Legend::STEP_MAX) {
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

				++symbolCount;
				average += node.position;

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

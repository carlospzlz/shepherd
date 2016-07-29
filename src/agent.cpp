#include <agent.h>


float Agent::distanceTo(const Agent& agent) {
	return (agent.getPosition() - m_position).magnitude();
}


void Agent::calculateNeighbours(std::vector<Agent*> agents) {
	m_neighbours.clear();
	std::vector<Agent*>::const_iterator end_agent = agents.end();
	for (std::vector<Agent*>::const_iterator current_agent=agents.begin();
			current_agent!=end_agent; ++current_agent) {
		if (this != *current_agent) {
			if (distanceTo(**current_agent) < VISION_RADIUS) {
				m_neighbours.push_back(*current_agent);
			}
		}
	}
}


void Agent::applyFlockingRules() {
	Vec2 centre_of_mass;
	Vec2 cohesion;
	Vec2 alignment;
	Vec2 separation;
	std::vector<Agent*>::const_iterator end_neighbour = m_neighbours.end();
	for (std::vector<Agent*>::const_iterator current_neighbour=m_neighbours.begin();
			current_neighbour!=end_neighbour; ++current_neighbour) {
		centre_of_mass += (*current_neighbour)->getPosition();
		alignment += (*current_neighbour)->getVelocity();
		separation += m_position - (*current_neighbour)->getPosition();
	}
	centre_of_mass /= m_neighbours.size();
	cohesion = centre_of_mass - m_position;
	alignment /= m_neighbours.size();

	cohesion.normalize(1);
	alignment.normalize(1);
	separation.normalize(1);

	m_velocity += cohesion + alignment + separation;
}


void Agent::update() {
	applyFlockingRules();
	m_velocity.normalize(MAX_SPEED);
	m_position += m_velocity;
}

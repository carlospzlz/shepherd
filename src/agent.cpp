#include <agent.h>


std::ostream& operator<<(std::ostream& lhs, const Agent& rhs) {
	lhs << &rhs << " [" << rhs.getType() << ", (" << rhs.getPosition().x
		<< ", "	<< rhs.getPosition().y << ", " << rhs.getPosition().z << ")"
		<< ", " << rhs.getNeighboursSize() << " ]";
	return lhs;
}


float Agent::distanceTo(const Agent& agent) {
	return glm::distance(m_position, agent.getPosition());
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
	glm::vec3 centre_of_mass;
	glm::vec3 cohesion;
	glm::vec3 alignment;
	glm::vec3 separation;
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

	cohesion = glm::length(cohesion) ? glm::normalize(cohesion) : cohesion;
	alignment = glm::length(alignment) ? glm::normalize(alignment) : alignment;
	separation = glm::length(separation) ? glm::normalize(separation) : separation;

	m_velocity += COHESION_FACTOR*cohesion
		+ ALIGNMENT_FACTOR*alignment
		+ SEPARATION_FACTOR*separation;
}


void Agent::update() {
	applyFlockingRules();
	if (glm::length(m_velocity)) {
		m_velocity = glm::normalize(m_velocity) *
			std::min(glm::length(m_velocity), MAX_SPEED);
	}
	m_position += m_velocity;
}

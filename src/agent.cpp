#include <agent.h>


std::ostream& operator<<(std::ostream& lhs, const Agent& rhs) {
	lhs << &rhs << " [" << rhs.getType() <<", (" << rhs.getPosition().x
		<< ", "	<< rhs.getPosition().y << ", " << rhs.getPosition().z << ")"
		<< ", (" << rhs.getVelocity().x << ", "	<< rhs.getVelocity().y << ", "
		<< rhs.getVelocity().z << ")" << ", " << rhs.getNeighboursSize() << "]";
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


glm::vec3 Agent::seek(glm::vec3 target) {
	/**
	 * Steer = desired - velocity
	 */
	if (glm::distance(m_position, target)==0) {
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
	glm::vec3 desired, steer;
	desired = target - m_position;
	desired = glm::normalize(desired) * MAX_SPEED;
	steer = desired - m_velocity;
	return glm::normalize(steer) * MAX_SPEED;
}


void Agent::applyFlockingRules() {
	if (getNeighboursSize() == 0) {
		return;
	}
	int non_overlapped_neighbours = 0;
	float distance;
	glm::vec3 centre_of_mass;
	glm::vec3 cohesion;
	glm::vec3 alignment;
	glm::vec3 separation;
	glm::vec3 desired_velocity;
	std::vector<Agent*>::const_iterator end_neighbour = m_neighbours.end();
	for (std::vector<Agent*>::const_iterator current_neighbour=m_neighbours.begin();
			current_neighbour!=end_neighbour; ++current_neighbour) {
		centre_of_mass += (*current_neighbour)->getPosition();
		alignment += (*current_neighbour)->getVelocity();
		distance = glm::distance(m_position, (*current_neighbour)->getPosition());
		if (distance>0) {
			separation += (m_position - (*current_neighbour)->getPosition()) /
				distance;
			++non_overlapped_neighbours;
		}
	}
	centre_of_mass /= m_neighbours.size();
	cohesion = seek(centre_of_mass);
	alignment /= m_neighbours.size();
	alignment = glm::normalize(alignment) * MAX_SPEED;
	if (non_overlapped_neighbours > 0) {
		separation /= m_neighbours.size();
		separation = glm::normalize(separation) * MAX_SPEED;
	}

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
	m_position.x = m_position.x < -1 ? m_position.x+2 : m_position.x;
	m_position.x = m_position.x >  1 ? m_position.x-2 : m_position.x;
	m_position.y = m_position.y < -1 ? m_position.y+2 : m_position.y;
	m_position.y = m_position.y >  1 ? m_position.y-2 : m_position.y;

}

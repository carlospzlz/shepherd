#include "agent.h"


const float STEP = 5E-5;

const float VISION_RADIUS = .2;


std::ostream& operator<<(std::ostream& lhs, const Agent& rhs) {
	lhs << &rhs << " [" << rhs.getType() <<", (" << rhs.getPosition().x
		<< ", "	<< rhs.getPosition().y << ", " << rhs.getPosition().z << ")"
		<< ", (" << rhs.getVelocity().x << ", "	<< rhs.getVelocity().y << ", "
		<< rhs.getVelocity().z << ")" << ", " << rhs.getNeighboursSize() << "]";
	return lhs;
}


float Agent::s_vision_radius = 0.2;

float Agent::s_max_speed = 1E-4;

float Agent::s_cohesion_factor = 1E-3;

float Agent::s_alignment_factor = 1E-3;

float Agent::s_separation_factor = 1E-3;

float Agent::s_repulsion_factor = 1E-4;


void Agent::increaseVisionRadius() {
	s_vision_radius += .1;
	std::cout << "s_visio_radius = " << s_vision_radius << std::endl;
}


void Agent::decreaseVisionRadius() {
	s_vision_radius -= .1;
	std::cout << "s_vision_radius = " << s_vision_radius << std::endl;
}


void Agent::increaseSpeed() {
	s_max_speed += 1E-5;
	std::cout << "s_max_speed = " << s_max_speed << std::endl;
}


void Agent::decreaseSpeed() {
	s_max_speed -= 1E-5;
	std::cout << "s_max_speed = " << s_max_speed << std::endl;
}


void Agent::increaseCohesion() {
	s_cohesion_factor += STEP;
	std::cout << "s_cohesion_factor = " << s_cohesion_factor << std::endl;
}


void Agent::decreaseCohesion() {
	s_cohesion_factor -= STEP;
	std::cout << "s_cohesion_factor = " << s_cohesion_factor << std::endl;
}


void Agent::increaseAlignment() {
	s_alignment_factor += STEP;
	std::cout << "s_alignment_factor = " << s_alignment_factor << std::endl;
}


void Agent::decreaseAlignment() {
	s_alignment_factor -= STEP;
	std::cout << "s_alignment_factor = " << s_alignment_factor << std::endl;
}


void Agent::increaseSeparation() {
	s_separation_factor += STEP;
	std::cout << "s_separation_factor = " << s_separation_factor << std::endl;
}


void Agent::decreaseSeparation() {
	s_separation_factor -= STEP;
	std::cout << "s_separation_factor = " << s_separation_factor << std::endl;
}

void Agent::increaseRepulsion() {
	s_repulsion_factor += STEP;
	std::cout << "s_repulsion_factor = " << s_repulsion_factor << std::endl;
}


void Agent::decreaseRepulsion() {
	s_repulsion_factor -= STEP;
	std::cout << "s_repulsion_factor = " << s_repulsion_factor << std::endl;
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


void Agent::observe(Environment env) {
	calculateNeighbours(env.getAgents());
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
	desired = glm::normalize(desired) * s_max_speed;
	steer = desired - m_velocity;
	if (glm::length(steer)) {
		steer = glm::normalize(steer) * s_max_speed;
	}
	return steer;
}


void Agent::applyFlockingRules() {
	if (m_neighbours.size() == 0) {
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
	if (glm::length(alignment) > 0) {
		alignment /= m_neighbours.size();
		alignment = glm::normalize(alignment) * s_max_speed;
	}
	if (non_overlapped_neighbours > 0) {
		separation /= m_neighbours.size();
		separation = glm::normalize(separation) * s_max_speed;
	}

	// Arbitrary weight the velocities
	m_velocity += s_cohesion_factor*cohesion
		+ s_alignment_factor*alignment
		+ s_separation_factor*separation;
}


void Agent::action(Environment env) {
	applyFlockingRules();
	if (glm::length(m_velocity)) {
		m_velocity = glm::normalize(m_velocity) *
			std::min(glm::length(m_velocity), s_max_speed);
	}
	m_position += m_velocity;
	m_position.x = m_position.x < -1 ? m_position.x+2 : m_position.x;
	m_position.x = m_position.x >  1 ? m_position.x-2 : m_position.x;
	m_position.y = m_position.y < -1 ? m_position.y+2 : m_position.y;
	m_position.y = m_position.y >  1 ? m_position.y-2 : m_position.y;

}


void Agent::repelFrom(float x, float y) {
	glm::vec3 repulsion_point(x, y, 0.0f);
	glm::vec3 repulsion;
	float distance = glm::distance(m_position, repulsion_point);
	if (distance > 0) {
		repulsion = (m_position - glm::vec3(x, y, 0.0f)) / distance;
		repulsion = seek(m_position + repulsion);
	}
	m_velocity += s_repulsion_factor * repulsion;
}

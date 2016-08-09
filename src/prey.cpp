#include <prey.h>


void Prey::observe(Environment env) {
	std::vector<Agent*> agents = env.getAgents();
	Agent* threat;
	glm::vec3 scape;
	float min_distance = FLT_MAX;
	float distance;
	std::vector<Agent*>::const_iterator end_agent = agents.end();
	for (std::vector<Agent*>::const_iterator current_agent=agents.begin();
			current_agent!=end_agent; ++current_agent) {
		distance = std::min(distanceTo(**current_agent), min_distance);
		if (distance < min_distance) {
			threat = *current_agent;
			min_distance = distance;
		}
	}

	scape = (m_position - threat->getPosition()) / min_distance;
	scape = glm::normalize(scape) * s_max_speed;
	m_velocity += scape;
}

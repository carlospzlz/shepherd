#include <world.h>


void World::createSheepHerd(glm::vec3 centre_of_mass, int number) {
	Agent* sheep;
	glm::vec3 initial_velocity;
	srand(time(NULL));
	for (unsigned int i=0; i<number; ++i) {
		initial_velocity = glm::vec3(rand()-RAND_MAX/2.0, rand()-RAND_MAX/2.0, 0);
		initial_velocity = glm::normalize(initial_velocity) *
			std::min(glm::length(initial_velocity), MAX_SPEED);
		sheep = new Agent(
			SHEEP, glm::vec3(0.0f, 0.0f, 0.0f), initial_velocity);
		m_sheep.push_back(sheep);
		m_agents.push_back(sheep);
	}
}


void World::update() {
	std::vector<Agent*>::const_iterator end_agent = m_agents.end();
	for (std::vector<Agent*>::const_iterator current_agent=m_agents.begin();
			current_agent!=end_agent; ++current_agent) {
		(*current_agent)->calculateNeighbours(m_agents);
	}
	for (std::vector<Agent*>::const_iterator current_agent=m_agents.begin();
			current_agent!=end_agent; ++current_agent) {
		(*current_agent)->update();
	}

}

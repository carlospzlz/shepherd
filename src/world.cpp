#include <world.h>


void World::createSheepHerd(glm::vec3 centre_of_mass, int number) {
	Agent* sheep;
	float x_displacement, y_displacement;
	srand(time(NULL));
	for (unsigned int i=0; i<number; ++i) {
		x_displacement = rand() / (float)RAND_MAX * VISION_RADIUS - VISION_RADIUS/2.0;
		y_displacement = rand() / (float)RAND_MAX * VISION_RADIUS - VISION_RADIUS/2.0;
		sheep = new Agent(
			SHEEP, glm::vec3(
				centre_of_mass.x + x_displacement,
				centre_of_mass.y + y_displacement,
				0));
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

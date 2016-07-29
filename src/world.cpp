#include <world.h>

void World::createSheepHerd(Vec2 position, int number) {
	Agent* sheep;
	for (unsigned int i=0; i<number; ++i) {
		sheep = new Agent(position, SHEEP);
		m_sheep.push_back(sheep);
		m_agents.push_back(sheep);
	}
}

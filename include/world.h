#include <vector>
#include "prey.h"
#include "predator.h"



class Prey;
class Predator;


class World {
	private:
		std::vector<Agent*> m_agents;
		Environment m_environment;

	public:
		void createAgents(AgentType type, glm::vec3 position, int number);
		std::vector<Agent*> allAgents() { return m_agents; }
		void setCursorPosition(float x, float y) {
			m_environment.setCursorPosition(glm::vec3(x, y, 0.0f)); }
		void update();
};

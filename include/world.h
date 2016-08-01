#include <vector>
#include <agent.h>


class World {
	private:
		std::vector<Agent*> m_agents;
		std::vector<Agent*> m_sheep;

	public:
		void createShepherdDog(glm::vec3 position) {};
		void createSheepHerd(glm::vec3 position, int number);
		void createWolvesPack(glm::vec3 position, int number);
		std::vector<Agent*> allAgents() { return m_agents; }
		void update();
};

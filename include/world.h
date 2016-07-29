#include <vector>
#include <agent.h>


enum AgentType {SHEEP, WOLF, SHEPHERD};


class World {
	private:
		std::vector<Agent*> m_agents;
		std::vector<Agent*> m_sheep;

	public:
		void createShepherdDog(Vec2 position) {};
		void createSheepHerd(Vec2 position, int number);
		void createWolvesPack(Vec2 position, int number);
};

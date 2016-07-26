#include <vector>

#include <agent.h>


class Group {
	private:
		std::vector<Agent> m_agents;

	public:
		Group(std::vector<Agent> _agents);
		std::vector<Group> ungroup();
		void info();
};

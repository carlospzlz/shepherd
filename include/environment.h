#include <vector>
#include <iostream>
#include <glm/glm.hpp>


class Agent;


class Environment {
	private:
		std::vector<Agent*> m_agents;
		glm::vec3 m_cursor_position;

	public:
		void addAgent(Agent* agent) { m_agents.push_back(agent); }
		void setCursorPosition(glm::vec3 cursor_position) {
			m_cursor_position = cursor_position; }
		glm::vec3 getCursorPosition() { return m_cursor_position; }
		std::vector<Agent*> getAgents() { return m_agents; }
};

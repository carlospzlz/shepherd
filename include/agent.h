#include <iostream>
#include <glm/glm.hpp>
#include <vector>


const float VISION_RADIUS = 2;
const float MAX_SPEED = 0.01;
const float COHESION_FACTOR = 0.001;
const float ALIGNMENT_FACTOR = 0.002;
const float SEPARATION_FACTOR = 0.002;


enum AgentType {SHEEP, WOLF, SHEPHERD};


class Agent {
	friend std::ostream& operator<<(std::ostream& lhs, const Agent& rhs);

	private:
		AgentType m_type;
		glm::vec3 m_position;
		glm::vec3 m_velocity;
		std::vector<Agent*> m_neighbours;
		float m_vision_radius;

		float distanceTo(const Agent& agent);
		void applyFlockingRules();

	public:
		Agent(AgentType type, glm::vec3 position):
			m_type(type), m_position(position) { }
		int getType() const { return m_type; }
		glm::vec3 getPosition() const { return m_position; }
		glm::vec3 getVelocity() const { return m_velocity; }
		int getNeighboursSize() const { return m_neighbours.size(); }
		void calculateNeighbours(std::vector<Agent*> agents);
		void update();
};

#include <iostream>
#include <glm/glm.hpp>
#include <vector>


const float VISION_RADIUS = .2;
const float MAX_SPEED = 1E-4;
const float COHESION_FACTOR = 1.2E-3;
const float ALIGNMENT_FACTOR = 1.2E-3;
const float SEPARATION_FACTOR = 1.3E-3;


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
		glm::vec3 seek(glm::vec3 target);
		void applyFlockingRules();

	public:
		Agent(AgentType type, glm::vec3 position):
			m_type(type), m_position(position) { }
		Agent(AgentType type, glm::vec3 position, glm::vec3 velocity):
			m_type(type), m_position(position), m_velocity(velocity) { }
		int getType() const { return m_type; }
		glm::vec3 getPosition() const { return m_position; }
		glm::vec3 getVelocity() const { return m_velocity; }
		int getNeighboursSize() const { return m_neighbours.size(); }
		void calculateNeighbours(std::vector<Agent*> agents);
		void update();
};

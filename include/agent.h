#ifndef AGENT_H
#define AGENT_H
#include <cmath>
#include "environment.h"


enum AgentType {PREY, PREDATOR, UNKNOWN};


class Agent {
	friend std::ostream& operator<<(std::ostream& lhs, const Agent& rhs);

	protected:
		static float s_vision_radius;
		static float s_max_speed;
		static float s_cohesion_factor;
		static float s_alignment_factor;
		static float s_separation_factor;
		static float s_repulsion_factor;
		AgentType m_type;
		glm::vec3 m_position;
		glm::vec3 m_velocity;
		std::vector<Agent*> m_neighbours;
		float m_vision_radius;

		float distanceTo(const Agent& agent);
		glm::vec3 seek(glm::vec3 target);
		void applyFlockingRules();

	public:
		static float getMaxSpeed() { return s_max_speed; }
		static void increaseVisionRadius();
		static void decreaseVisionRadius();
		static void increaseSpeed();
		static void decreaseSpeed();
		static void increaseCohesion();
		static void decreaseCohesion();
		static void increaseAlignment();
		static void decreaseAlignment();
		static void increaseSeparation();
		static void decreaseSeparation();
		static void increaseRepulsion();
		static void decreaseRepulsion();
		Agent(AgentType type, glm::vec3 position):
			m_type(type), m_position(position) { }
		Agent(AgentType type, glm::vec3 position, glm::vec3 velocity):
			m_type(type), m_position(position), m_velocity(velocity) { }
		int getType() const { return UNKNOWN; }
		glm::vec3 getPosition() const { return m_position; }
		glm::vec3 getVelocity() const { return m_velocity; }
		int getNeighboursSize() const { return m_neighbours.size(); }
		void calculateNeighbours(std::vector<Agent*> agents);
		void repelFrom(float x, float y);
		virtual void observe(Environment env);
		virtual void action(Environment env);
};
#endif

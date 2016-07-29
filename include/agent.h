#include <cmath>
#include <vector>
#include <vec2.h>


const float VISION_RADIUS = 0.1;
const float MAX_SPEED = 0.1;


class Agent {
	private:
		Vec2 m_position;
		Vec2 m_velocity;
		std::vector<Agent*> m_neighbours;
		int m_flock_id;
		float m_vision_radius;

		float distanceTo(const Agent& agent);
		void applyFlockingRules();

	public:
		Agent(Vec2 position, int flock_id):
			m_position(position), m_flock_id(flock_id) { }
		Vec2 getPosition() const { return m_position; }
		Vec2 getVelocity() const { return m_velocity; }
		void calculateNeighbours(std::vector<Agent*> agents);
		void update();
};

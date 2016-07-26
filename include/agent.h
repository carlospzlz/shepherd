#include <vector>


class Agent {
	private:
		std::vector<float> m_position;
		std::vector<float> m_acceleration;

	public:
		Agent(std::vector<float> _position):m_position(_position) { }
		void applyForce(std::vector<float> _force);
};

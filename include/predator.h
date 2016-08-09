#include "agent.h"


class Predator : public Agent {
	public:
		Predator(glm::vec3 position) : Agent(PREDATOR, position) { }
		Predator(glm::vec3 position, glm::vec3 velocity) :
			Agent(PREDATOR, position, velocity) { }
		//virtual void observe(Environment env);
		//virtual void action(Environment env);
};

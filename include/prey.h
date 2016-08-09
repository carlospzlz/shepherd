#include "agent.h"


class Prey : public Agent {
	public:
		Prey(glm::vec3 position) : Agent(PREY, position) { }
		Prey(glm::vec3 position, glm::vec3 velocity) :
			Agent(PREY, position, velocity) { }
		//void observe(Environment env);
		//virtual void action(Environment env);
};

#include <renderer.h>
#include <signal.h>


void sigintHandler(int s) {
	std::cout << "bye!" << std::endl;
	exit(1);
}


void printWorld(World w) {
	std::vector<Agent*> agents = w.allAgents();
	std::vector<Agent*>::const_iterator end_agent = agents.end();
	for (std::vector<Agent*>::const_iterator current_agent=agents.begin();
			current_agent!=end_agent; ++current_agent) {
		std::cout << **current_agent << std::endl;
	}
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_R:
				Agent::increaseVisionRadius();
				break;
			case GLFW_KEY_F:
				Agent::decreaseVisionRadius();
				break;
			case GLFW_KEY_Y:
				Agent::increaseSpeed();
				break;
			case GLFW_KEY_H:
				Agent::decreaseSpeed();
				break;
			case GLFW_KEY_U:
				Agent::increaseCohesion();
				break;
			case GLFW_KEY_J:
				Agent::decreaseCohesion();
				break;
			case GLFW_KEY_I:
				Agent::increaseAlignment();
				break;
			case GLFW_KEY_K:
				Agent::decreaseAlignment();
				break;
			case GLFW_KEY_O:
				Agent::increaseSeparation();
				break;
			case GLFW_KEY_L:
				Agent::decreaseSeparation();
				break;
			case GLFW_KEY_E:
				Agent::increaseRepulsion();
				break;
			case GLFW_KEY_D:
				Agent::decreaseRepulsion();
				break;
		}
	}
}


void shepherdWorld(GLFWwindow* window, World world) {
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	xpos = (xpos / 1280.0) * 2.0 - 1.0;
	ypos = (1.0 - ypos / 960.0) * 2.0 - 1.0;
	//world.repelFrom(xpos, ypos);
}


int run() {
	Renderer my_renderer;
	if (!my_renderer.initialiseGraphicContext()) {
		return 1;
	}
	my_renderer.allocateResources();
	glfwSetKeyCallback(my_renderer.getWindow(), keyCallback);
	World w;
	w.createAgents(PREY, glm::vec3(0.0f, 0.0f, 0.0f), 10);
	std::vector<Agent*> agents = w.allAgents();
	while (!my_renderer.windowShouldClose()) {
		//shepherdWorld(my_renderer.getWindow(), w);
		w.update();
		my_renderer.render(w);
		//printWorld(w);
		//std::cin.ignore();
		glfwPollEvents();
	}
	my_renderer.terminateGraphicContext();
	return 0;
}


int test() {
	Agent a = Agent(PREY, glm::vec3(0.0f, 0.0f, 0.0f));
	std::cout << a << std::endl;
	World w;
	w.createAgents(PREY, glm::vec3(0.0f, 0.0f, 0.0f), 50);

	signal(SIGINT, sigintHandler);
	while (true) {
		w.update();
		printWorld(w);
		//std::cin.ignore();
	}
	return 0;
}


int main() {
	return run();
}

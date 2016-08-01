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


int run() {
	Renderer my_renderer;
	if (!my_renderer.initialiseGraphicContext()) {
		return 1;
	}
	my_renderer.allocateResources();
	World w;
	w.createSheepHerd(glm::vec3(0.0f, 0.0f, 0.0f), 40);
	std::vector<Agent*> agents = w.allAgents();
	while (!my_renderer.windowShouldClose()) {
		w.update();
		my_renderer.render(w);
		printWorld(w);
		//std::cin.ignore();
	}
	my_renderer.terminateGraphicContext();
	return 0;
}


int test() {
	Agent a = Agent(SHEEP, glm::vec3(0.0f, 0.0f, 0.0f));
	std::cout << a << std::endl;
	World w;
	w.createSheepHerd(glm::vec3(0.0f, 0.0f, 0.0f), 5);

	signal(SIGINT, sigintHandler);
	while (true) {
		w.update();
		printWorld(w);
		std::cin.ignore();
	}
	return 0;
}


int main() {
	return run();
}

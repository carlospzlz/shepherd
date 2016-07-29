#include <renderer.h>


int main() {
	Renderer my_renderer;
	if (!my_renderer.initialiseGraphicContext()) {
		return 1;
	}
	my_renderer.allocateResources();
	while (!my_renderer.windowShouldClose()) {
		my_renderer.render(World());
	}
	my_renderer.terminateGraphicContext();
	return 0;
}

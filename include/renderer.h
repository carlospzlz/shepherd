#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <world.h>


class Renderer {
	private:
		const static char* s_vertex_shader;
		const static char* s_fragment_shader;
		GLFWwindow* m_window;
		GLuint m_shader_programme;
		GLuint m_vao;
	public:
		bool initialiseGraphicContext();
		void allocateResources();
		bool windowShouldClose();
		void render(World world);
		void terminateGraphicContext();
};

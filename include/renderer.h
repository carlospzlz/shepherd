#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
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
		GLFWwindow* getWindow() { return m_window; }
		bool initialiseGraphicContext();
		void allocateResources();
		bool windowShouldClose();
		void render(World world);
		void terminateGraphicContext();
};

#include <renderer.h>


const char* Renderer::s_vertex_shader =
	"#version 400\n"
	"in vec3 vp;\n"
	"void main () {\n"
	"	gl_Position = vec4(vp, 1.0);\n"
	"}";


const char* Renderer::s_fragment_shader =
	"#version 400\n"
	"out vec4 frag_colour;\n"
	"void main() {\n"
	"	frag_colour = vec4(0.5, 0.0, 0.4, 1.0);\n"
	"}";


bool Renderer::initialiseGraphicContext() {
	if (!glfwInit()) {
		std::cout << "ERROR: could not start GLFW3" << std::endl;
		return false;
	}

	m_window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!m_window) {
		std::cout << "ERROR: could not open window with GLF3" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(m_window);

	glewInit();
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* renderer = glGetString(GL_RENDERER);
	std::cout << "OpenGL   : " << version << std::endl;
	std::cout << "Renderer : " << renderer << std::endl;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	return true;
}


void Renderer::allocateResources() {
	float points[] = {
		-0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f
	};

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), points, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &s_vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &s_fragment_shader, NULL);
	glCompileShader(fs);

	m_shader_programme = glCreateProgram();
	glAttachShader(m_shader_programme, fs);
	glAttachShader(m_shader_programme, vs);
	glLinkProgram(m_shader_programme);
}


bool Renderer::windowShouldClose() {
	return glfwWindowShouldClose(m_window);
}


void Renderer::render(World world) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(m_shader_programme);
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glfwPollEvents();
	glfwSwapBuffers(m_window);
}


void Renderer::terminateGraphicContext() {
	glfwTerminate();
}

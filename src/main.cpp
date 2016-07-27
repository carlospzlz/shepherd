#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>


static struct {
	GLuint vertex_buffer, element_buffer;
} g_resources;


static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 0.0f
};


static const GLushort g_element_buffer_data[] = {0, 1, 2};


static GLuint makeBuffer(
		GLenum target, const void *buffer_data, GLsizei buffer_size) {
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(target, buffer);
	glBufferData(target, buffer_size, buffer_data, GL_STATIC_DRAW);
	return buffer;
}


static int makeResources(void) {
	g_resources.vertex_buffer = makeBuffer(
		GL_ARRAY_BUFFER, g_vertex_buffer_data, sizeof(g_vertex_buffer_data));
	g_resources.element_buffer = makeBuffer(
		GL_ELEMENT_ARRAY_BUFFER, g_element_buffer_data,
		sizeof(g_element_buffer_data));
	return 1;
}


static void updateFadeFactor(void) { }


static void render(void) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}



int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(400, 300);
	glutCreateWindow("Hello World");
	glutDisplayFunc(&render);
	glutIdleFunc(&updateFadeFactor);
	glewInit();

	if (!GLEW_VERSION_2_0) {
		std::cout << "OpenGl 2.0 not available" << std::endl;
		return 1;
	}

	if (!makeResources()) {
		std::cout << "Failed to load resources" << std::endl;
		return 1;
	}

	glutMainLoop();

	return 0;
}

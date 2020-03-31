/* Rony Sheik
   301258738
   rsheik@sfu.ca */
   
#include <GL/freeglut.h>
#include <iostream>
#include <GL/glut.h>
#include <stdio.h> 


//http://www.nongnu.org/pyformex/doc-1.0/ref/opengl.colors.html - color values can be picked from here

const GLuint WIDTH = 800, HEIGHT = 800; // defined the window size 800 * 800

void draw_three_shapes(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	// Drawing the rectangle on the first co-ordinate 
	glBegin(GL_QUADS);           // Each set of 4 vertices form a quad
	glColor3f(0.0f, 0.5f, 0.0f); // Dark Green
	glVertex2f(0.2f, 0.2f);      
	glVertex2f(0.7f, 0.2f);  
	glVertex2f(0.7f, 0.5f);
	glVertex2f(0.2f, 0.5f);
	glEnd();

	// Drawing the Pentagon on the second co-ordinate
	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.0f, 0.0f); // Dark Red
	glVertex2f(-0.4f, 0.0f);
	glVertex2f(-0.1f, 0.0f);
	glVertex2f(-0.1f, 0.2f);
	glVertex2f(-0.25f, 0.3f);
	glVertex2f(-0.4f, 0.2f);
	glEnd();

	// Drawing the triangle on the third co-ordinate
	glBegin(GL_TRIANGLES);       // Each set of 3 vertices form a triangle
	glColor3f(0.0f, 1.0f, 1.0f); // Cyan
	glVertex2f(-0.2f, -0.2f);
	glVertex2f(-0.4f, -0.6f);
	glVertex2f(0.0f, -0.6f);
	glEnd();
	glFlush();

}

int main(int argc, char** argv)
{
	// OpenGL
	glutInit(&argc, argv);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(200, 200);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Problem Answer 1");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glutDisplayFunc(draw_three_shapes);
	glutMainLoop();

	std::cin.get();
	return 0;
}

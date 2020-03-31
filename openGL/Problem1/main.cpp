#include <GL/freeglut.h>
#include <iostream>
#include <GL/glut.h>
#include <stdio.h> 


// https://community.khronos.org/t/color-tables/22518/3 - color values can be picked from here

const GLuint WIDTH = 600, HEIGHT = 600; // defined the window size 600 * 600

void drawrect()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 1.0f);
	glLineWidth(30);



	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < 360; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(360);//get the current angle

		float x = 0.5 * cosf(theta);//calculate the x component
		float y = 0.5 * sinf(theta);//calculate the y component

		glVertex2f(x + 0, y + 0);//output vertex

	}
	glEnd();

	// Drawing the rectangle on the first co-ordinate 
	glBegin(GL_QUADS);           // Each set of 4 vertices form a quad
	glColor3f(0.0f, 0.5f, 0.0f); // Dark Green
	glVertex2f(0.2f, 0.2f);      
	glVertex2f(0.7f, 0.2f);  
	glVertex2f(0.7f, 0.5f);
	glVertex2f(0.2f, 0.5f);
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
// The MAIN function, from here we start the application and run the game loop
// Game loop here refers to as the continues execution of the program.
int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(200, 200);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Window");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glutDisplayFunc(drawrect);
	glutMainLoop();

	return 0;
}

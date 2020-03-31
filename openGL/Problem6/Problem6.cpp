/* Rony Sheik
   301258738
   rsheik@sfu.ca */

#include<iostream>
#include<string>
#include <GL/freeglut.h>
#include <iostream>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <vector>
#include<stdlib.h>
#include<time.h>

const int WIDTH = 500, HEIGHT = 500;

// function to draw text on the window 
void drawText(const char *text, int len, int x_val, int y_val) {

	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x_val, y_val);

	for (int i = 0; i < len; i++) 
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);

	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}


void visualize_MSNE()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2.5);
	glColor3f(0.0f, 0.5f, 0.0f); // dark green
	glBegin(GL_LINES);

	glVertex2i(5, 10);
	glVertex2i(5, 90);
	glVertex2i(5, 10);
	glVertex2i(90, 10);
	glVertex2i(90, 10);
	glVertex2i(90, 90);

	glColor3f(1.0f, 1.0f, 0.0f); //yellow
	glVertex2i(5, 26);
	glVertex2i(90, 42);
	glVertex2i(5, 74);
	glVertex2i(90, 26);

	glColor3f(0.0f, 0.5f, 0.0f); // dark green
	glVertex2i(5, 26);
	glVertex2i(6, 26);
	glVertex2i(5, 42);
	glVertex2i(6, 42);
	glVertex2i(5, 58);
	glVertex2i(6, 58);
	glVertex2i(5, 74);
	glVertex2i(6, 74);
	glVertex2i(89, 26);
	glVertex2i(90, 26);
	glVertex2i(89, 42);
	glVertex2i(90, 42);
	glVertex2i(89, 58);
	glVertex2i(90, 58);
	glVertex2i(89, 74);
	glVertex2i(90, 74);

	glColor3f(0.5f, 0.0f, 0.0f); //dark red
	glVertex2i(69, 10);
	glVertex2i(69, 38.3);
	glVertex2i(5, 38.3);
	glVertex2i(69, 38);

	glColor3f(0.0f, 0.5f, 0.0f); // dark green
	glVertex2i(5, 110);
	glVertex2i(5, 190);
	glVertex2i(5, 110);
	glVertex2i(90, 110);
	glVertex2i(90, 110);
	glVertex2i(90, 190);

	glColor3f(1.0f, 1.0f, 0.0f); //yellow
	glVertex2i(5, 149);
	glVertex2i(90, 188);
	glVertex2i(05, 175);
	glVertex2i(90, 123);

	glColor3f(0.0f, 0.5f, 0.0f); // dark green
	glVertex2i(5, 123);
	glVertex2i(6, 123);
	glVertex2i(5, 136);
	glVertex2i(6, 136);
	glVertex2i(5, 149);
	glVertex2i(6, 149);
	glVertex2i(5, 162);
	glVertex2i(6, 162);
	glVertex2i(5, 175);
	glVertex2i(6, 175);
	glVertex2i(5, 188);
	glVertex2i(6, 188);
	glVertex2i(89, 123);
	glVertex2i(90, 123);
	glVertex2i(89, 136);
	glVertex2i(90, 136);
	glVertex2i(89, 149);
	glVertex2i(90, 149);
	glVertex2i(89, 162);
	glVertex2i(90, 162);
	glVertex2i(89, 175);
	glVertex2i(90, 175);
	glVertex2i(89, 188);
	glVertex2i(90, 188);

	glColor3f(0.5f, 0.0f, 0.0f);
	glVertex2i(29.2, 110);
	glVertex2i(29.2, 160);
	glVertex2i(5, 160);
	glVertex2i(29.2, 160.2);

	glEnd();
	glFlush();

	glColor3f(0.0f, 0.0f, 0.0f);
	std::string t1, t2, t3, t4, t5, t6, t11, t12, t13, tp1, tp2, tPlayer1, tPlayer2;
	t1 = "0"; t2 = "1"; t3 = "2"; t4 = "3"; t5 = "4"; t6 = "5";
	t11 = "-1"; t12 = "-2"; t13 = "-3"; tp1 = "P2 = 0.75"; tp2 = "P1 = 0.29";
	tPlayer1 = "Player 2 MSNE";
	tPlayer2 = "Player 1 MSNE";

	drawText(t1.data(), t1.size(), 11, 25);
	drawText(t2.data(), t2.size(), 11, 75);
	drawText(t3.data(), t3.size(), 11, 123);
	drawText(t4.data(), t4.size(), 11, 171);
	drawText(t5.data(), t5.size(), 11, 218);

	drawText(t1.data(), t1.size(), 723, 25);
	drawText(t2.data(), t2.size(), 723, 75);
	drawText(t3.data(), t3.size(), 723, 123);
	drawText(t4.data(), t4.size(), 723, 171);
	drawText(t5.data(), t5.size(), 723, 218);

	drawText(t13.data(), t13.size(), 11, 365);
	drawText(t12.data(), t12.size(), 11, 405);
	drawText(t11.data(), t11.size(), 11, 444);
	drawText(t1.data(), t1.size(), 11, 483);
	drawText(t2.data(), t2.size(), 11, 522);
	drawText(t3.data(), t3.size(), 11, 561);

	drawText(t13.data(), t13.size(), 723, 365);
	drawText(t12.data(), t12.size(), 723, 405);
	drawText(t11.data(), t11.size(), 723, 444);
	drawText(t1.data(), t1.size(), 723, 483);
	drawText(t2.data(), t2.size(), 723, 522);
	drawText(t3.data(), t3.size(), 723, 561);

	drawText(tp1.data(), tp1.size(), 520, 16);
	drawText(tp2.data(), tp2.size(), 220, 315);
	drawText(tPlayer2.data(), tPlayer1.size(), 320, 580);
	drawText(tPlayer1.data(), tPlayer2.size(), 320, 280);
	glutSwapBuffers();
}


int main(int argc, char **argv) {

	// first row given
	double A1[] = { 2.0, -3.0 };
	double A2[] = { 1.0, 2.0 };

	// second row given 
	double B1[] = { 1.0,  1.0 };
	double B2[] = { 4.0, -1.0 };

	// From the sloved handwritten problem, we can use the calulated players mixed strategy
	// For Player 1
	double p1 = 0.29;
	double not_p1 = 1.0 - p1;

	// For Player 2
	double p2 = 0.75;
	double not_p2 = 1.0 - p2;

	// We have the MSNE now
	std::cout << "MSNE = Mixed Strategy Nash Equlibrium" << std::endl;
	// For player1
	std::cout << "Player1 MSNE :" << p1 << ", " << not_p1 << std::endl;

	// For player2
	std::cout << "Player2 MSNE :" << p2 << ", " << not_p2 << std::endl;
	std::cout << "\n";

	// Let's calculate the payoffs for each player
	// Player's 1 payoff 
	double payoff_player1 = A1[0] * p1 * p2 + A2[0] * p1 * not_p2 + B1[0] * not_p1 * p2 + B2[0] * not_p1 * not_p2;
	std::cout << "Player1 Payoff :" << payoff_player1 << std::endl;

	// Player's 2 payoff 
	double payoff_player2 = A1[1] * p1 * p2 + A2[1] * p1 * not_p2 + B1[1] * not_p1 * p2 + B2[1] * not_p1 * not_p2;
	std::cout << "Player2 Payoff :" << payoff_player2 << std::endl;

	// OpenGL 
	glutInit(&argc, argv);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(200, 200);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Problem 6 Answer");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 100.0, 0.0, 200.0, -2.0, 2.0);
	glutDisplayFunc(visualize_MSNE);
	glutMainLoop();

	system("pause");
	return 0;
}
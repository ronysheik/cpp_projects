/* Rony Sheik
   301258738
   rsheik@sfu.ca */
   
   
/* -- the decision matrix we can have for this problem

    ------------------------------------
	       | Win(1/38) | Loss(37/38)
	------------------------------------
	  bet  | $(35*bet) | $(-bet)
	------------------------------------
	 No_bet| $0        | $0
	------------------------------------
	
*/

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

// defining the window size
const int WIDTH = 400, HEIGHT = 400;


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


// function to draw decision tree on the window
void draw_decision_tree(int &val)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(3.0);
	glColor3f(0.0f, 0.5f, 0.0f); // drak green
	glBegin(GL_LINES);
	//first line
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.4f, 0.4f);

	//second line
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.6f, -0.4f);
	
	//third line
	glVertex2f(0.2f, 0.2f);
	glVertex2f(0.6f, 0.6f);
	
	//fourth line
	glVertex2f(0.2f, 0.2f);
	glVertex2f(0.6f, 0.0f);
	
	glEnd();
	glFlush();

	// Need to draw text over the decission tree
	std::string bet, No_bet, Win, Loss, Zero, Lost_val, WinVal, title;
	bet = "Bet";
	No_bet = "No Bet";
	Win = "Win";
	Loss = "Loss";
	Zero = "$0";

	title = "Decision Tree of the Roulette Game";
	drawText(title.data(), title.size(), 100, 550);

	// if you lost the value needs to be shown in negative
	Lost_val = "$-" + std::to_string(val);
	WinVal = "$" + std::to_string(val * 35);

	drawText(bet.data(), bet.size(), 450, 405);
	drawText(No_bet.data(), No_bet.size(), 450, 175);

	drawText(Win.data(), Win.size(), 580, 500);
	drawText(Loss.data(), Loss.size(), 580, 270);

	drawText(WinVal.data(), WinVal.size(), 650, 480);
	drawText(Lost_val.data(), Lost_val.size(), 650, 290);

	drawText(Zero.data(), Zero.size(), 650, 180);

	glutSwapBuffers();
}

int main(int argc, char **argv)
{

	int value, bet_Value, bet_Money;
	
	srand(time(0));
	value = rand() % 38;

	std::cout << "Please Enter the bet value in dollars: ";
	std::cin >> bet_Value;
	std::cout << "\n";

	std::cout << "Please Enter the amount you want to bet in dollars: ";
	std::cin >> bet_Money;
	std::cout << "\n";
	
	std::cout << "The value is coming from Roulette[randomly] :" << value << std::endl;

	if (value == bet_Value) {
		std::cout << "You have won " << 35 * bet_Money << std::endl;
	}
	else {
		std::cout << "Opps! You have lost!!" << std::endl;
	}

	glutInit(&argc, argv);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(200, 200);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Problem 4 Answer");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	draw_decision_tree(bet_Money);
	//glutDisplayFunc(draw_decision_tree);
	Sleep(1000000);
	glutMainLoop();
	
	std::cin.get();
	return 0;

}
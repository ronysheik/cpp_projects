/* Rony Sheik
   301258738
   rsheik@sfu.ca */


#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <math.h>
#include <windows.h>

using namespace std;


// Globals
extern const int WIDTH = 700, HEIGHT = 600;
vector<int> Count, Count1, count2;


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

//Calculate the mean = sum / N
int mean(vector<string> &myvec) {

	int sum = 0;
	for (int i = 0; i < myvec.size(); i++) {
		sum = sum + stoi(myvec[i]);
	}
	return sum / myvec.size();
}

//Calculate the Variance = (x-u)^2/N
int variance(vector<string> &myvec, int mean) {

	int sum = 0;
	for (int i = 0; i < myvec.size(); i++) {
		sum = sum + ((stoi(myvec[i]) - mean)*(stoi(myvec[i]) - mean));
	}
	return sum / myvec.size();
}

// calculate the Bhattacharaya distance using the computation formula from lecture slide
double Bhatta(double var1, double var2, double mean1, double mean2) {

	double result = 0.25*log(0.25*((var1 / var2) + (var2 / var1) + 2)) + 0.25*(((mean1 - mean2)*(mean1 - mean2)) / (var1 + var2));
	return result;
}

//Calculate the histogram

void histogram(vector<string> &vec)
{
	for (int i = 0; i < 8; i++) {
		Count.push_back(0);
	}
	for (int i = 0; i < vec.size(); i++) {
		if (stoi(vec[i]) <= 200 && stoi(vec[i]) > 0) {
			Count[0] = Count[0] + 1;
		}
		else if (stoi(vec[i]) <= 400 && stoi(vec[i]) > 200) {
			Count[1] = Count[1] + 1;
		}
		else if (stoi(vec[i]) <= 800 && stoi(vec[i]) > 400) {
			Count[2] = Count[2] + 1;
		}
		else if (stoi(vec[i]) <= 1000 && stoi(vec[i]) > 800) {
			Count[3] = Count[3] + 1;
		}
		else if (stoi(vec[i]) <= 1200 && stoi(vec[i]) > 1000) {
			Count[4] = Count[4] + 1;
		}
		else if (stoi(vec[i]) <= 2000 && stoi(vec[i]) > 1200) {
			Count[5] = Count[5] + 1;
		}
		else if (stoi(vec[i]) <= 4000 && stoi(vec[i]) > 2000) {
			Count[6] = Count[6] + 1;
		}
		else if (stoi(vec[i]) <= 10000 && stoi(vec[i]) > 4000) {
			Count[7] = Count[7] + 1;
		}
	}
}

void histogram2(vector<string> &vec)
{
	for (int i = 0; i < 8; i++) {
		Count1.push_back(0);
	}
	for (int i = 0; i < vec.size(); i++) {
		if (stoi(vec[i]) == 10) {
			Count1[0] = Count1[0] + 1;
		}
		else if (stoi(vec[i]) == 20) {
			Count1[1] = Count1[1] + 1;
		}
		else if (stoi(vec[i]) == 30) {
			Count1[2] = Count1[2] + 1;
		}
		else if (stoi(vec[i]) == 40) {
			Count1[3] = Count1[3] + 1;
		}
		else if (stoi(vec[i]) == 50) {
			Count1[4] = Count1[4] + 1;
		}
		else if (stoi(vec[i]) == 60) {
			Count1[5] = Count1[5] + 1;
		}
		else if (stoi(vec[i]) == 70) {
			Count1[6] = Count1[6] + 1;
		}
		else if (stoi(vec[i]) == 80) {
			Count1[7] = Count1[7] + 1;
		}
	}
}


void draw_histograms(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2.5);

	//first bin 0 - 200
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.1, 0.0);
	glVertex2i(5, 10);
	glVertex2i(30, 10);
	glVertex2i(30, 60);
	glVertex2i(5, 60);
	glEnd();

	//second bin 201 - 400
	glBegin(GL_POLYGON);
	glVertex2i(40, 10);
	glVertex2i(65, 10);
	glVertex2i(65, 80);
	glVertex2i(40, 80);
	glEnd();

	//third bin 401 - 800
	glBegin(GL_POLYGON);
	glVertex2i(75, 10);
	glVertex2i(100, 10);
	glVertex2i(100, 100);
	glVertex2i(75, 100);
	glEnd();

	//fourth bin 801 - 1000
	glBegin(GL_POLYGON);
	glVertex2i(110, 10);
	glVertex2i(135, 10);
	glVertex2i(135, 32);
	glVertex2i(110, 32);
	glEnd();

	//fifth bin 1001 - 1200
	glBegin(GL_POLYGON);
	glVertex2i(145, 10);
	glVertex2i(170, 10);
	glEnd();

	//sixth bin 1201 - 2000
	glBegin(GL_POLYGON);
	glVertex2i(180, 10);
	glVertex2i(205, 10);
	glVertex2i(205, 32);
	glVertex2i(180, 32);
	glEnd();

	//seventh bin 2001 - 4000
	glBegin(GL_POLYGON);
	glVertex2i(215, 10);
	glVertex2i(240, 10);
	glVertex2i(240, 15);
	glVertex2i(215, 15);
	glEnd();

	//eighth bin 4001 - 10000
	glBegin(GL_POLYGON);
	glVertex2i(250, 10);
	glVertex2i(275, 10);
	glVertex2i(275, 13);
	glVertex2i(250, 13);
	glEnd();

	//graph axes
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(5, 10);
	glVertex2i(300, 10);

	glVertex2i(5, 10);
	glVertex2i(5, 120);
	glEnd();



	//Putting text on the histogram (i.e x axis, y axis and name of the graph)
	glColor3f(0, 0, 0);
	string h1_x1, h1_x2, h1_x3, h1_x4, h1_x5, h1_x6, h1_x7, h1_x8;
	string n0, n1, n2, n3, n4, n5, n6, n7, n8;
	string title;
	title = "Histogram 1";
	h1_x1 = "0-200"; h1_x2 = "201-400"; h1_x3 = "401-800"; h1_x4 = "801-1000";
	h1_x5 = "1001-1200"; h1_x6 = "12001-2000"; h1_x7 = "2001-4000"; h1_x8 = "4001-10000";
	
	n0 = "0"; n1 = "5"; n2 = "10"; n3 = "15"; n4 = "20";
	n5 = "25"; n6 = "30"; n7 = "35"; n8 = "40"; 

	drawText(title.data(), title.size(), 300, 570);

	drawText(h1_x1.data(), h1_x1.size(), 10, 40);
	drawText(h1_x2.data(), h1_x2.size(), 100, 40);
	drawText(h1_x3.data(), h1_x3.size(), 200, 40);
	drawText(h1_x4.data(), h1_x4.size(), 300, 40);
	drawText(h1_x5.data(), h1_x5.size(), 380, 40);
	drawText(h1_x6.data(), h1_x6.size(), 480, 40);
	drawText(h1_x7.data(), h1_x7.size(), 580, 40);
	drawText(h1_x8.data(), h1_x8.size(), 680, 40);
	
	drawText(n0.data(), n0.size(), 0, 55);
	drawText(n1.data(), n1.size(), 0, 120);
	drawText(n2.data(), n2.size(), 0, 180);
	drawText(n3.data(), n3.size(), 0, 280);
	drawText(n4.data(), n4.size(), 0, 350);
	drawText(n5.data(), n5.size(), 0, 420);
	drawText(n6.data(), n6.size(), 0, 490);
	drawText(n7.data(), n7.size(), 0, 590);
	
	

	glFlush();
}
int main(int argc, char **argv)
{
	//open the file called "data1.csv"
	ifstream  data("data1.csv");

	//if the file not open successfully return 0 or exit
	if (!data.is_open()) {
		cout << "File is not open successfully!" << endl;
		cin.get();
		return 0;
	}

	//reading the data from data1.csv and store the data to vectors 
	vector<string> myvec1, myvec2, myvec3;
	
	string line;
	while (getline(data, line))
	{
		stringstream  lineStream(line);
		string        cell;
		while (getline(lineStream, cell, ','))
		{
			// keep adding to vectors
			myvec1.push_back(cell);
			getline(lineStream, cell, ',');

			myvec2.push_back(cell);
			getline(lineStream, cell, ',');

			myvec3.push_back(cell);
		}
	}


	histogram(myvec1);
	histogram2(myvec2);

	cout << "Histogram 1\n" << endl;
	cout << 0 << "-" << 200 << "      = " << Count[0] << endl;
	cout << 201 << "-" << 400 << "    = " << Count[1] << endl;
	cout << 401 << "-" << 800 << "    = " << Count[2] << endl;
	cout << 801 << "-" << 1000 << "   = " << Count[3] << endl;
	cout << 1001 << "-" << 1200 << "  = " << Count[4] << endl;
	cout << 1201 << "-" << 2000 << "  = " << Count[5] << endl;
	cout << 2001 << "-" << 4000 << "  = " << Count[6] << endl;
	cout << 4001 << "-" << 10000 << " = " << Count[7] << endl << endl;

	double mn1 = mean(myvec1);
	double mn2 = mean(myvec2);

	cout << "Mean 1 = " << mn1 << endl;
	cout << "Variance 1 = " << variance(myvec1, mn1) << endl;
	cout << endl;

	cout << "Histogram 2\n" << endl;
	cout << 0 << "-" << 10 << "   = " << Count1[0] << endl;
	cout << 11 << "-" << 20 << "  = " << Count1[1] << endl;
	cout << 21 << "-" << 30 << "  = " << Count1[2] << endl;
	cout << 31 << "-" << 40 << "  = " << Count1[3] << endl;
	cout << 41 << "-" << 50 << "  = " << Count1[4] << endl;
	cout << 51 << "-" << 60 << "  = " << Count1[5] << endl;
	cout << 61 << "-" << 70 << "  = " << Count1[6] << endl;
	cout << 71 << "-" << 80 << "  = " << Count1[7] << endl << endl;

	cout << "Mean 2 = " << mn2 << endl;
	cout << "Variance 2 = " << variance(myvec2, mn2) << endl << endl;

	// output the Bhattacharyya coefficient
	cout << endl;
	double bhattResult = Bhatta(variance(myvec1, mn1), variance(myvec2, mn2), mn1, mn2);
	cout << "Bhattacharyya Distance from 1 to 2 = " << bhattResult << endl << endl;

	glutInit(&argc, argv);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(200, 200);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Problem 7 Answer");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 300.0, 0.0, 100.0, -2.0, 2.0);
	glutDisplayFunc(draw_histograms);
	glutMainLoop();

	std::cin.get();
	return 0;

}


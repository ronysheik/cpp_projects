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

//vector<string> myvec1, myvec2, myvec3;
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

// calculate the Bhattacharaya distance 
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

	cin.get();
	return 0;
}


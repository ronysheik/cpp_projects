/* Rony Sheik
   301258738
   rsheik@sfu.ca */

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <windows.h>

using namespace std;

//Globals
vector<string> myVec1, myVec2, myVec3;


// function to calculate mean
double mean(vector<string> &vec) {
	double sum = 0;
	for (int i = 0; i < vec.size(); i++) {
		sum = sum + stoi(vec[i]);
	}
	return sum / vec.size();
}

// function to calculate variance
double variance(vector<string> &vec, double mean) {
	double sum = 0;
	for (int i = 0; i < vec.size(); i++) {
		sum = sum + ((stoi(vec[i]) - mean)*(stoi(vec[i]) - mean));
	}
	return sum / vec.size();
}

// function to calculate covariance
double covariance(vector<string> &vec1, vector<string> &vec2, double mean1, double mean2) {
	double sum = 0;
	for (int i = 0; i < vec1.size(); i++) {
		sum += (stoi(vec1[i]) - mean1)*(stoi(vec2[i]) - mean2);
	}
	return sum / (vec1.size() - 1);
}

double standardDev(vector<string> &vec, double mean) {
	double sum = 0;
	for (int i = 0; i < vec.size(); i++) {
		sum += (stoi(vec[i]) - mean)*(stoi(vec[i]) - mean);
	}
	sum = sum / (vec.size() - 1);
	return sqrt(sum);
}

// function to calculate coorrelation
double correlation(vector<string> &vec1, vector<string> &vec2, double mean1, double mean2, double std1, double std2) {
	double sum = 0;
	for (int i = 0; i < vec1.size(); i++) {
		sum += ((stoi(vec1[i]) - mean1) / std1)*((stoi(vec2[i]) - mean2) / std2);
	}
	return sum / (vec1.size() - 1);
}

int main(int argc, char **argv)
{
	// read the file
	ifstream  file("data1.csv");
	if (!file.is_open()) {
		cout << "Could not open file!so exit" << endl;
		cin.get();
		return 0;
	}

	string line;
	while (getline(file, line))
	{
		stringstream  lineStream(line);
		string        cell;
		while (getline(lineStream, cell, ','))
		{
			// store in vectors
			myVec1.push_back(cell);
			getline(lineStream, cell, ',');
			myVec2.push_back(cell);
			getline(lineStream, cell, ',');
			myVec3.push_back(cell);

		}
	}
	double mean1 = mean(myVec1);
	double mean2 = mean(myVec2);
	double mean3 = mean(myVec3);

	double var1 = variance(myVec1, mean1);
	double var2 = variance(myVec2, mean2);
	double var3 = variance(myVec3, mean3);

	double covar12 = covariance(myVec1, myVec2, mean1, mean2);
	double covar13 = covariance(myVec1, myVec3, mean1, mean3);
	double covar23 = covariance(myVec2, myVec3, mean2, mean3);

	double sdn1 = standardDev(myVec1, mean1);
	double sdn2 = standardDev(myVec2, mean2);
	double sdn3 = standardDev(myVec3, mean3);

	double cor1 = correlation(myVec1, myVec2, mean1, mean2, sdn1, sdn2);
	double cor2 = correlation(myVec1, myVec3, mean1, mean3, sdn1, sdn3);
	double cor3 = correlation(myVec2, myVec3, mean2, mean3, sdn2, sdn3);
	double covarMatrix[3][3] = { {var1, covar12, covar13},{covar12, var2, covar23}, {covar13, covar23, var3} };

	cout << "Mean's of the data sets =>" << endl;
	cout << "Mean one : " << mean1 << endl;
	cout << "Mean two : " << mean2 << endl;
	cout << "Mean three : " << mean3 << endl << endl;

	cout << "Variance's of the data sets =>" << endl;
	cout << "Variance one : " << var1 << endl;
	cout << "Variance two : " << var2 << endl;
	cout << "Variance three : " << var3 << endl << endl;

	cout << "Covariance's of the data sets =>" << endl;
	cout << "Covariance for first and second data : " << covar12 << endl;
	cout << "Covariance for first and third data : " << covar13 << endl;
	cout << "Covariance for second and third data " << covar23 << endl << endl;


	cout << "Correlation's of the data sets =>" << endl;
	cout << "Correlation one : " << cor1 << endl;
	cout << "Correlation two : " << cor2 << endl;
	cout << "Correlation three : " << cor3 << endl;
	cout << endl;
	
	double A[3][3] = { { var1,covar12, covar13},{ covar12,var2,covar23 },{ covar13,covar23,var3 } };
	cout << "3x3 Covariance Matrix =>" << endl;
	for (int i = 0; i < 3; i++) {
		cout << "[ ";
		for (int j = 0; j < 3; j++) {
			cout << A[i][j] << " ";
		};
		cout << "]" << endl;
	};

	cin.get();
	return 0;
}

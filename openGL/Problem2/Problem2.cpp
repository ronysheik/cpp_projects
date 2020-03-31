/* Rony Sheik
   301258738
   rsheik@sfu.ca */

#include<iostream>
#include<string>
#include <GL/freeglut.h>
#include <iostream>
#include <GL/glut.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <time.h>
#include <windows.h>

const int WIDTH = 700, HEIGHT = 500;
const int size_of_array = 4;

template <class T>

void NameSort(T arr[], int left, int right) {

	int i = left, j = right;
	int temp;
	int pivot = arr[(left + right) / 2]; //get the pivot

	/* partition */
	//use toupper function to make all letters into upper case and cast to int to compare 
	while (i <= j) {
		while (toupper((int)arr[i]) < toupper((int)pivot))
			i++;
		while (toupper((int)arr[j]) > toupper((int)pivot))
			j--;
		// condition for swapping 
		if (i <= j) {
			// swap 
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
		}
	};
	// Separately sort elements before 
	// partition and after partition 
	if (left < j)
		NameSort(arr, left, j);
	if (i < right)
		NameSort(arr, i, right);

}


void quickSort(float arr[], int left, int right) {
	int i = left, j = right;
	double tmp;
	double pivot = arr[(left + right) / 2];
	/* partition */
	while (i <= j) {
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};
	/* recursion */
	if (left < j)
		quickSort(arr, left, j);
	if (i < right)
		quickSort(arr, i, right);
}


void Draw_Blocks(float arr[4])
{
	// first and second two blocks are in the first co-ordinate (-,+)
	glBegin(GL_QUADS);
	glColor3f(arr[0], 0.5f, 0.0f);
	glVertex2f(-0.6f, 0.2f);
	glVertex2f(-0.8f, 0.2f);
	glVertex2f(-0.8f, 0.5f);
	glVertex2f(-0.6f, 0.5f);
	glEnd();

	glBegin(GL_QUADS);           
	glColor3f(arr[1], 0.5f, 0.0f); 
	glVertex2f(-0.2f, 0.2f);
	glVertex2f(-0.4f, 0.2f);
	glVertex2f(-0.4f, 0.5f);
	glVertex2f(-0.2f, 0.5f);
	glEnd();

	// third  and fourth blocks are in the second co-ordinate (+,+)
	glBegin(GL_QUADS);           
	glColor3f(arr[2], 0.5f, 0.0f);
	glVertex2f(0.0f, 0.2f);
	glVertex2f(0.2f, 0.2f);
	glVertex2f(0.2f, 0.5f);
	glVertex2f(0.0f, 0.5f);
	glEnd();

	glBegin(GL_QUADS);          
	glColor3f(arr[3], 0.5f, 0.0f);
	glVertex2f(0.4f, 0.2f);
	glVertex2f(0.6f, 0.2f);
	glVertex2f(0.6f, 0.5f);
	glVertex2f(0.4f, 0.5f);
	glEnd();

	// sort the values of R 
	quickSort(arr, 0, 3);

	// output to the console 
	std::cout << "\nR values after being sorted: \n" << std::endl;
	for (int i = 0;i < size_of_array;i++)
	{
		std::cout << "value " << i + 1 << " :";
		std::cout << arr[i] << std::endl;
	}

	// draw blocks after sort based on R values
	// first and second two blocks are in the first co-ordinate (-,+)
	
	glBegin(GL_QUADS);
	glColor3f(arr[0], 0.5f, 0.0f); 
	glVertex2f(-0.6f, -0.2f);
	glVertex2f(-0.8f, -0.2f);
	glVertex2f(-0.8f, -0.5f);
	glVertex2f(-0.6f, -0.5f);
	glEnd();

	glBegin(GL_QUADS);           
	glColor3f(arr[1], 0.5f, 0.0f); 
	glVertex2f(-0.2f, -0.2f);
	glVertex2f(-0.4f, -0.2f);
	glVertex2f(-0.4f, -0.5f);
	glVertex2f(-0.2f, -0.5f);
	glEnd();


	glBegin(GL_QUADS);          
	glColor3f(arr[2], 0.5f, 0.0f);
	glVertex2f(0.0f, -0.2f);
	glVertex2f(0.2f, -0.2f);
	glVertex2f(0.2f, -0.5f);
	glVertex2f(0.0f, -0.5f);
	glEnd();


	glBegin(GL_QUADS);          
	glColor3f(arr[3], 0.5f, 0.0f);
	glVertex2f(0.4f, -0.2f);
	glVertex2f(0.6f, -0.2f);
	glVertex2f(0.6f, -0.5f);
	glVertex2f(0.4f, -0.5f);
	glEnd();

	glFlush();

}


int main(int argc, char **argv)
{

	// Part 1 sort the student Name
	char name[] = "RonySheik";
	int size = (sizeof(name) / sizeof(name[0]));
	int low = 0;

	std::cout << "Before sort Name:";
	for (int i = 0;i < size;i++)
	{
		std::cout << name[i];
	}

	// sorting
	NameSort<char>(name, 0, size);
	// Name after sort
	std::cout << "\nAfter  sort Name:";
	// index from to avoid the null character
	for (int i = 1;i <= size;i++)
	{
		std::cout << name[i];
	}

	std::cout << "\n" << std::endl;

	// part 2 sort graphical blocks based on the given R values
	std::cout << "the R values given by the user for the blocks: \n" << std::endl;
	float input_array[size_of_array];

	for (int i = 0;i < size_of_array;i++)
	{
		std::cout << "value " << i+1 << " :";
		std::cin >> input_array[i];
	}

	glutInit(&argc, argv);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(200, 200);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Problem 2 Answer");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	Draw_Blocks(input_array);
	Sleep(1000000);
	glutMainLoop();

	std::cin.get();
	return 0;


}

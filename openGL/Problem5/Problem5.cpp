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

// Return the max value
int get_PD_best_response(std::vector<int> &myvec)
{
	int max = myvec[0];
	for (int i = 1; i < 4;i++)
	{
		if (myvec[i] > max)
		{
			max = myvec[i];
		}
	}
	return max;
}

int main(int argc, char **argv)
{
	// We have two players
	int player1[2][2], player2[2][2];

	std::cout << "NC = Not Confess\n";
	std::cout << "C  = Confess\n";

	// Get the user inputs
	std::cout << "Enter the NC value for both the players:\n";
	std::cin >> player1[0][0] >> player2[0][0];

	std::cout << "Enter the C value for both the players:\n";
	std::cin >> player1[1][1] >> player2[1][1];

	std::cout << "Enter the NC value for the player1 and C value for palyer2:\n";
	std::cin >> player1[0][1] >> player2[0][1];

	std::cout << "Enter the C value for player1 and NC value for palyer2:\n";
	std::cin >> player1[1][0] >> player2[1][0];
	std::cout << "\n";
    
	// From perspective of palyer 1

	// if player2 not confess
	if (player1[0][0] > player1[1][0])
		std::cout << "if player2 not confess then player1 not confess as well" << std::endl;
	else
		std::cout << "if player2 not confess then player1 confess" << std::endl;

	// // if player2 confess
	if(player1[0][1] > player1[1][1])
		std::cout << "if player2 confess player1 not confess" << std::endl;
	else
		std::cout << "if player2 confess player1 confess as well" << std::endl;


	// From perspective of palyer 2

	// if player 1 not confess 
	if(player2[0][0] > player2[0][1])
		std::cout << "if player1 not confess player2 not Confess as well" << std::endl;
	else
		std::cout << "if player1 not confess player2 confess" << std::endl;

	// if player 1 confess 
	if (player2[1][1] > player2[1][0])
		std::cout << "if player1 confess then player2 confess as well" << std::endl;
	else
		std::cout << "if player1 confess then player2 not confess" << std::endl;

	// Need to calculate the best response 

	std::cout << "\n";
	std::vector<int> vec;

	vec.push_back(player1[0][0] + player2[0][0]);
	vec.push_back(player1[0][1] + player2[0][1]);
	vec.push_back(player1[1][0] + player2[1][0]);
	vec.push_back(player1[1][1] + player2[1][1]);

	int result = get_PD_best_response(vec);

	if (result == vec.at(0)) std::cout << "The best joint strategy for both players is to not confess";
	if (result == vec.at(1)) std::cout << "The best joint strategy is player1 NOT confess, player2 confess";
	if (result == vec.at(2)) std::cout << "The best joint strategy is player1 confess, player2 NOT confess";
	if (result == vec.at(3)) std::cout << "The best joint strategy for both players is to confess";

	Sleep(1000000);
	std::cin.get();
	return 0;
}

// ProgrammingDemo.cpp : Defines the entry point for the console application.
//

#include "D:\ENSC488\files/ensc-488.h"
#include "D:\ENSC488\files/Globals.h"
#include <iostream>
#include "D:\ENSC488\files\StdAfx.h"


using namespace std;

//////////////////////////////////////////////////////
///function declarations
//////////////////////////////////////////////////////
// function to initialize translation matrix with desired DH values
void init_trans_matrix(double theta, double alpha, double a_val, double d_val, double arr[4][4]) {
	
	// initialize first row of trans mtrx
	arr[0][0] = cos(theta * PI / 180);
	arr[0][1] = (-1) * sin(theta * PI / 180);
	arr[0][2] = 0;
	arr[0][3] = a_val;
	// initialize first row of trans mtrx
	arr[1][0] = (sin(theta * PI / 180)) * (cos(alpha * PI / 180));
	arr[1][1] = (cos(theta * PI / 180)) * (cos(alpha * PI / 180));
	arr[1][2] = (-1) * (sin(alpha * PI / 180));
	arr[1][3] = (-1) * (sin(alpha * PI / 180) * d_val);
	// initialize third row of trans mtrx
	arr[2][0] = (sin(theta * PI / 180)) * (sin(alpha * PI / 180));
	arr[2][1] = (cos(theta * PI / 180)) * (sin(alpha * PI / 180));
	arr[2][2] = (cos(alpha * PI / 180));
	arr[2][3] = (cos(alpha * PI / 180) * d_val);
	// initialize fourth row of trans mtrx
	arr[3][0] = 0;
	arr[3][1] = 0;
	arr[3][2] = 0;
	arr[3][3] = 1;
}

// function to perform multiplication of 2, 4x4 matrices
void matrix_multiplication(double mtrx_1[4][4], double mtrx_2[4][4], double temp[4][4]) {
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			temp[i][j] = 0;
			for (int k = 0; k < 4; ++k)
				temp[i][j] = temp[i][j] + (mtrx_1[i][k] * mtrx_2[k][j]);
			//cout << c[i][j] << " ";
		}
	}
}

// function to copy contents of source matrix to destination
void copy_mtrx_contents(double src[4][4], double destn[4][4]) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			destn[i][j] = src[i][j];
		}
	}
}

//function to display the contents of a matrix
void print_mtrx(double src[4][4]) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			cout << src[i][j] << " ";
		}
		cout << "\n";
	}
}

void display_orientation(double src[4][4]) {
	cout << "	Px = " << src[0][3] << "\n";
	cout << "	Py = " << src[1][3] << "\n";
	cout << "	Pz = " << src[2][3] << "\n";
}



//function to display main menu and recieve input
int main_menu() {
	int input;
	cout << "Please make a selection:" << "\n";
	cout << " 1. EMULATOR" << "\n";
	cout << " 2. FORWARD KINEMATICS" << "\n";
	cout << " 3. INVERSE KINEMATICS" << "\n";
	cout << " 4. Pick and Place" << "\n";
	cout << " 5. EXIT" << "\n\n";
	
	cin >> input;
	return input;
}


void solve(double x, double y, double z, double phi)
{
	double theta2 = 0.0f;
	double theta1 = 0.0f;
	double theta4 = 0.0f;
	double d3 = 0.0f;
	double a1 = 195;
	double a2 = 142;
	double d5 = 275;
	double d2 = 70;
	double d1 = 405;

	// solved equations for inverse kinematics
	double cos_theta2 = ((x * x) + (y * y) - (a1 * a1) - (a2 * a2)) / (2 * a1 * a2);
	double sin_pos_theta2 = sqrt(1 - pow(cos_theta2, 2));
	double sin_neg_theta2 = -sqrt(1 - pow(cos_theta2, 2));
	double theta2_pos = RAD2DEG(atan2(sin_pos_theta2, cos_theta2));
	double theta2_neg = RAD2DEG(atan2(sin_neg_theta2, cos_theta2));

	//double temp2 = atan2((a2 * sin(theta2) * x) + ((a1 + a2 * cos(theta2)) * y), (a1 + a2 * cos(theta2)) * x - (a2 * sin(theta2) * y));
	//double temp2 = acos((x * (142 * cos(theta2) + 195) + (142 * sin(theta2) * y)) / (pow(142 * cos(theta2) + 195,2) + pow(142 * sin(theta2),2)));
	double k2_pos = a2 * sin_pos_theta2;
	double k2_neg = a2 * sin_neg_theta2;
	double k1 = a1 + (a2 * cos_theta2);
	double theta1_pos = RAD2DEG((atan2(y, x) - atan2(k2_pos, k1)));
	double theta1_neg = RAD2DEG((atan2(y, x) - atan2(k2_neg, k1)));
	//theta1 = RAD2DEG(temp2);

	double theta4_pos = theta1_pos + theta2_pos - phi;
	double theta4_neg = theta1_neg + theta2_neg - phi;
	
	d3 = -z-70-140;

	cout << " the values are " << endl;
	cout << "theta1 positive :" << endl;
	cout << theta1_pos << endl;
	cout << "theta1 negative :" << endl;
	cout << theta1_neg << endl;
	cout << "theta2 positive:" << endl;
	cout << theta2_pos << endl;
	cout << "theta2 negative :" << endl;
	cout << theta2_neg << endl;

	cout << "d3" << endl;
	cout << d3 << endl;
	cout << "theta4 positive" << endl;
	cout << theta4_pos << endl;
	cout << "theta4 negative :" << endl;
	cout << theta4_neg << endl;

	// solution vectors
	JOINT sol1 = { theta1_pos, theta2_pos, d3, theta4_pos };
	JOINT sol2 = { theta1_neg, theta2_neg, d3, theta4_neg };

	JOINT speedy;
	GetConfiguration(speedy);
	cout << "The current position of the robot is" << endl;
	cout << speedy[0] << endl;
	cout << speedy[1] << endl;
	cout << speedy[2] << endl;
	cout << speedy[3] << endl;

	bool sol1_valid = false;
	bool sol2_valid = false;
	bool near_sol1 = false;
	bool near_sol2 = false;
	double diffsum_sol1 = 0.0f;
	double diffsum_sol2 = 0.0f;
	
	JOINT sol_1, sol_2;

	if (Theta1Check(sol1[0]) && Theta2Check(sol1[1]) && Theta4Check(sol1[3]) && D3Check(sol1[2]))
	{
		sol1_valid = true;
	}
	if (Theta1Check(sol2[0]) && Theta2Check(sol2[1]) && Theta4Check(sol2[3]) && D3Check(sol2[2]))
	{
		sol2_valid = true;
	}

	if (sol1_valid) {
		
		double r1 = sol1[0] - speedy[0];
		double r2 = sol1[1] - speedy[1];
		double r3 = sol1[2] - speedy[2];
		double r4 = sol1[3] - speedy[3];

		sol_1[0] = abs(r1);
		sol_1[1] = abs(r2);
		sol_1[2] = abs(r3);
		sol_1[3] = abs(r4);
		diffsum_sol1 = sol_1[0] + sol_1[1] + sol_1[2] + sol_1[3];
	}
	if (sol2_valid)
	{
		double r5 = sol2[0] - speedy[0];
		double r6 = sol2[1] - speedy[1];
		double r7 = sol2[2] - speedy[2];
		double r8 = sol2[3] - speedy[3];

		sol_2[0] = abs(r5);
		sol_2[1] = abs(r6);
		sol_2[2] = abs(r7);
		sol_2[3] = abs(r8);
		
		diffsum_sol2 = sol_2[0] + sol_2[1] + sol_2[2] + sol_2[3];
	}
	
	// getting the nearest and farthest solutions
	int choose = 0;
	if (diffsum_sol1 < diffsum_sol2)
	{
		near_sol1 = true;
		cout << "The nearets Solution is this" << endl;
		cout << sol1[0] << " " << sol1[1] << " " << sol1[2] << " " << sol1[3] << endl;
	}
	else if  (diffsum_sol1 > diffsum_sol2)
	{
		near_sol2 = true;
		cout << "The nearets Solution is this" << endl;
		cout << sol2[0] << " " << sol2[1] << " " << sol2[2] << " " << sol2[3] << endl;
	}

	if (!near_sol1)
	{
		cout << "The farthest Solution is this" << endl;
		cout << sol1[0] << " " << sol1[1] << " " << sol1[2] << " " << sol1[3] << endl;
	}
	else if (!near_sol2)
	{
		cout << "The farthest Solution is this" << endl;
		cout << sol2[0] << " " << sol2[1] << " " << sol2[2] << " " << sol2[3] << endl;
	}

	cout << "Choose which solution you want to choose:" << endl;
	cout << "please hit 1 to choose The nearest Solution " << endl;
	cout << "please hit 2 to choose The farthest Solution" << endl;
	cout << "3. BYE BYE THEN" << endl;
	
	//Let the use choose b/w nearest & furthest solution
	cin >> choose;
	if (choose == 1 ) {

		if (near_sol1)
		{
			MoveToConfiguration(sol1, true);
			cout << "sol1" << endl; }
		else{
			MoveToConfiguration(sol2, true);
			cout << "sol2" << endl;
		}
		
	}
	else if (choose == 2)
	{
		if (!near_sol1)
		{
			MoveToConfiguration(sol1, true);}
		else{
			MoveToConfiguration(sol2, true);
		}
	}
	else
	{
		cout << "press enter to exit " << endl;
	}

}

// function to pick the object from the position given by the user position
void pick(double& x, double& y, double& z, double& obj_height)
{
	int offset = 5;
	obj_height = obj_height + offset;
	offset = 0;
	solve(x, y, -100, 0);
	
	JOINT current_config;
	GetConfiguration(current_config);
	current_config[2] = -200 + obj_height;
	MoveToConfiguration(current_config, true);
	Grasp(true);
}

// function to place the object based on the given user position
void place(double& a, double& b, double& c, double& objh)
{
	int offset = 5;
	objh = objh + offset;
	offset = 0;
	solve(a, b, -100, 0);
	
	JOINT current_config;
	GetConfiguration(current_config);
	current_config[2] = -200 + objh;
	MoveToConfiguration(current_config, true);
	Grasp(false);
}

////////////////////////////////////////  MAIN  ////////////////////////////////
int main(int argc, char* argv[]) {

	JOINT q2 = { 90, 90, -200, 45 };
	printf("Keep this window in focus, and...\n");

	char ch;
	int c;
	int menu_input = 0;

	//User joint variable input
	double in_theta1 = 0, in_theta2 = 0, in_theta4 = 0;
	double in_d_val3 = 0;
	double phi = 0;

	//DH parameters

	double theta1 = 0, theta2 = 0, theta3 = 0, theta4 = 0, theta5 = 0;
	double d_val1 = 405, d_val2 = 70, d_val3 = 0, d_val4 = 410, d_val5 = 275;
	double a_val1 = 0, a_val2 = 195, a_val3 = 142, a_val4 = 0, a_val5 = 0;
	double alpha1 = 0, alpha2 = 0, alpha3 = 180, alpha4 = 0, alpha5 = 0;

	//Translation matrices for frames 0 to 5
	double trans0_1[4][4];
	double trans1_2[4][4];
	double trans2_3[4][4];
	double trans3_4[4][4];
	double trans4_5[4][4];

	// temp matrix storage
	double temp_mtrx1[4][4];
	double temp_mtrx2[4][4];
	double final_trans_mtrx[4][4];

	const int ESC = 27;
	JOINT q1;

	menu_input = main_menu();
	if (menu_input == 1) {
		// GET EMULATOR USER IMPUT
		std::cout << "  ---EMULATOR--- " << std::endl;
		std::cout << "Please enter the first variable THETA1: " << std::endl;
		std::cin >> in_theta1;
		std::cout << "Please enter the second variable THETA2: " << std::endl;
		std::cin >> in_theta2;
		std::cout << "Please enter the third variable D3: " << std::endl;
		std::cin >> in_d_val3;
		std::cout << "Please enter the fourth variable THETA4: " << std::endl;
		std::cin >> in_theta4;
		JOINT q4 = { in_theta1, in_theta2, in_d_val3, in_theta4 };
		MoveToConfiguration(q4, true);
	}
	else if (menu_input == 2) {
		// GET FORWARD KIN USER IMPUT
		std::cout << "  ---FORWARD KINEMATICS--- " << std::endl;
		std::cout << "Please enter the first variable THETA1: " << std::endl;
		std::cin >> in_theta1;
		std::cout << "Please enter the second variable THETA2: " << std::endl;
		std::cin >> in_theta2;
		std::cout << "Please enter the third variable D3: " << std::endl;
		std::cin >> in_d_val3;
		std::cout << "Please enter the fourth variable THETA4: " << std::endl;
		std::cin >> in_theta4;

		if ((in_theta1 > THETA1_MAX ||  in_theta1 < THETA1_MIN) || ((in_theta2 > THETA2_MAX || in_theta2 < THETA2_MIN)) ||
			(in_d_val3 > D3_MAX || in_d_val3 < D3_MIN) || (in_theta4 > THETA4_MAX || in_theta4 < THETA4_MIN))
		{
			cout << " user giving the invalid inputs" << endl;
			system("pause");
		}

		JOINT q3 = { in_theta1, in_theta2, in_d_val3, in_theta4 };
		for (int i = 0; i <= 3; i++)
		{
			q1[i] = q3[i];
		}
		MoveToConfiguration(q3, true);
		//cout << in_theta1 << " " << in_theta2 << " " << in_d_val3 << " " << in_theta4 << "\n\n";

		//INITIALIZE T-MATRICES WITH USER IMPUT
		init_trans_matrix(theta1 + in_theta1, alpha1, a_val1, d_val1, trans0_1);
		init_trans_matrix(theta2 + in_theta2, alpha2, a_val2, d_val2, trans1_2);
		init_trans_matrix(theta3, alpha3, a_val3, d_val3 + in_d_val3, trans2_3);
		init_trans_matrix(theta4 + in_theta4, alpha4, a_val4, d_val4, trans3_4);
		init_trans_matrix(theta5, alpha5, a_val5, d_val5, trans4_5);
		print_mtrx(trans0_1);
		cout << "\n\n";
		print_mtrx(trans1_2);
		cout << "\n\n";
		print_mtrx(trans2_3);
		cout << "\n\n";

		print_mtrx(trans3_4);
		cout << "\n\n";
		print_mtrx(trans4_5);
		cout << "\n\n";

		//COMPUTE T MATRIX FROM 0 TO 5

		matrix_multiplication(trans0_1, trans1_2, temp_mtrx1);      //multiply to 0_2
		cout << "first matrix\n";
		//print_mtrx(temp_mtrx1);
		matrix_multiplication(temp_mtrx1, trans2_3, temp_mtrx2);	//multiply to 0_3
		//cout << "second matrix\n";
		//print_mtrx(trans2_3);
		cout << "0 3 mtrx\n";
		//print_mtrx(temp_mtrx2);
		matrix_multiplication(temp_mtrx2, trans3_4, temp_mtrx1);	//multiply to 0_4
		matrix_multiplication(temp_mtrx1, trans4_5, temp_mtrx2);	//multiply to 0_5
		cout << "\n\n";
		print_mtrx(temp_mtrx2);
		cout << "\n\n";
		copy_mtrx_contents(temp_mtrx2, final_trans_mtrx);


		print_mtrx(final_trans_mtrx);
		cout << "\nFor input of :" << in_theta1 << ", " << in_theta2 << ", " << in_d_val3 << ", " << in_theta4 << "\n";
		cout << "  Current position of the tool is:" << "\n";
		display_orientation(final_trans_mtrx);
		cout << "  Current orientation of the tool is:" << "\n\n";
		//phi = in_theta1 + in_theta2 + in_theta4;
		//cout << "    " << phi << " degrees." << "\n";

		JOINT speedy;
		GetConfiguration(speedy);
		cout << "Robot is here:" << speedy[0] << " " << speedy[1] << " " << speedy[2] << " " << speedy[3] << "\n";
	}
	else if (menu_input == 3) {
		
		//doing the inverse kinematics
		//INVKIN(final_trans_mtrx, q1, false);
		double x, y, z, phi;
		std::cout << "Input the configuration for the tool frame relative to the station frame" << std::endl;
		std::cout << " X position :" << endl;
		std::cin >> x;
		std::cout << "Y position : " << std::endl;
		std::cin >> y;
		std::cout << " Z position" << std::endl;
		std::cin >> z;
		std::cout << "phi angle" << std::endl;
		std::cin >> phi;

		solve(x, y, z, phi);
		//matrix T_dpos_matrix = { {cos(d_pos[3]),-sin(d_pos[3]),0,d_pos[0]},
			//{sin(d_pos[3]),cos(d_pos[3]),0,d_pos[1]},
			//{0,0,-1,d_pos[2]},
			//{0,0,0,1} };
	}
	else if (menu_input == 4) {
		
	// doing the pick and place
		double x, y, z, obj_height;
		double a, b, c, d;

		std::cout << "Input the goal frame." << std::endl;
		std::cout << "x position >";
		std::cin >> x;
		std::cout << "y position >";
		std::cin >> y;
		std::cout << "z position >";
		std::cin >> z;
		std::cout << "object height >";
		std::cin >> obj_height;
		pick(x, y, z, obj_height);

		double objh = obj_height;

		std::cout << "Please give the position to place the object" << std::endl;
		std::cout << "Input the goal frame." << std::endl;
		std::cout << "x position >";
		std::cin >> a;
		std::cout << "y position >";
		std::cin >> b;
		std::cout << "z position >";
		std::cin >> c;
		place(a,b,c, objh);
	}

	system("pause");
	cin.get();
	return 0;

}
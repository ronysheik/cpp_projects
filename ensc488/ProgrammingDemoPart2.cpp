// ProgrammingDemo.cpp : Defines the entry point for the console application.
//
#include <fstream>
#include <iostream>
#include "D:\ENSC488\files/ensc-488.h"
#include "D:\ENSC488\files/Globals.h"
#include <iostream>
#include "D:\ENSC488\files\StdAfx.h"
#include <windows.h>
#include <cmath>
#include <time.h>


#define S_TO_MILIS 1000.0
using namespace std;

JOINT via_point_sol = { 0,0,0,0};
double forward_POS[4] = { 0,0,0,0 };

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
	cout << " 5. TRAJECTORY PLANNER" << "\n";
	cout << " 6. EXIT" << "\n\n";
	
	cin >> input;
	system("cls");
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
	double d5 = 275; //275
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


	//double theta4_pos = phi - theta1_pos - theta2_pos;
	//double theta4_neg = -phi - theta1_pos - theta2_pos;
	
	double theta4_pos = theta1_pos + theta2_pos - phi;
	double theta4_neg = theta1_neg + theta2_neg - phi;
	
	d3 = -150;//z - 70 - 140;
	//d3 = 75 - z;

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
	cout << "\n" << endl;

	// solution vectors
	JOINT sol1 = { theta1_pos, theta2_pos, d3, theta4_pos };
	JOINT sol2 = { theta1_neg, theta2_neg, d3, theta4_neg };

	
	JOINT speedy;
	GetConfiguration(speedy);
	cout << "The current position of the robot is" << endl;
	cout << speedy[0] << "," << speedy[1] << "," << speedy[2] << "," << speedy[3] << endl;
	cout << "\n";

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
		cout << "The nearest Solution is this" << endl;
		cout << sol1[0] << " " << sol1[1] << " " << sol1[2] << " " << sol1[3] << endl;
		cout << "\n" << endl;
	}
	else if  (diffsum_sol1 > diffsum_sol2)
	{
		near_sol2 = true;
		cout << "The nearest Solution is this" << endl;
		cout << sol2[0] << " " << sol2[1] << " " << sol2[2] << " " << sol2[3] << endl;
		cout << "\n"<< endl;
	}

	if (!near_sol1)
	{
		cout << "The farthest Solution is this" << endl;
		cout << sol1[0] << " " << sol1[1] << " " << sol1[2] << " " << sol1[3] << endl;
		cout << "\n" << endl;
	}
	else if (!near_sol2)
	{
		cout << "The farthest Solution is this" << endl;
		cout << sol2[0] << " " << sol2[1] << " " << sol2[2] << " " << sol2[3] << endl;
		cout << "\n" << endl;
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
			//MoveToConfiguration(sol1, true);

			for (int i = 0; i < 4;i++)
			{
				via_point_sol[i] = sol1[i];
			}
			
			cout << "sol1" << endl; }
		else{
			//MoveToConfiguration(sol2, true);
			for (int i = 0; i < 4;i++)
			{
				via_point_sol[i] = sol2[i];
			}
			cout << "sol2" << endl;
		}
		
	}
	else if (choose == 2)
	{
		if (!near_sol1)
		{
			for (int i = 0; i < 4;i++)
			{
				via_point_sol[i] = sol1[i];
			}
			//MoveToConfiguration(sol1, true);
		}
		else{

			for (int i = 0; i < 4;i++)
			{
				via_point_sol[i] = sol2[i];
			}
			//MoveToConfiguration(sol2, true);
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
	solve(x, y, z, 0);
	
	JOINT current_config;

	GetConfiguration(current_config);
	double temp = current_config[2];
	temp = temp  + 100 ;
	current_config[2] = current_config[2] + (-1 * temp) - 10;
	temp = 0;
	MoveToConfiguration(current_config, true);
	Grasp(true);
}

// function to place the object based on the given user position
void place(double& a, double& b, double& c, double& objh)
{
	int offset = 5;
	objh = objh + offset;
	offset = 0;
	solve(a, b, c, 0);
	
	JOINT current_config;

	GetConfiguration(current_config);
	double temp = current_config[2];
	temp = temp + 100;
	current_config[2] = current_config[2] + (-1 * temp) - 10;
	temp = 0;
	MoveToConfiguration(current_config, true);
	Grasp(false);
}

void ForwardKIN(double &val1, double &val2, double &val3, double &val4 )
{


	//User joint variable input
	double in_theta1 = val1, in_theta2 = val2, in_theta4 = val4;
	double in_d_val3 = val3;
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


	if ((in_theta1 > THETA1_MAX || in_theta1 < THETA1_MIN) || ((in_theta2 > THETA2_MAX || in_theta2 < THETA2_MIN)) ||
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
	

	//COMPUTE T MATRIX FROM 0 TO 5

	matrix_multiplication(trans0_1, trans1_2, temp_mtrx1);      //multiply to 0_2
	matrix_multiplication(temp_mtrx1, trans2_3, temp_mtrx2);	//multiply to 0_3
	
	matrix_multiplication(temp_mtrx2, trans3_4, temp_mtrx1);	//multiply to 0_4
	matrix_multiplication(temp_mtrx1, trans4_5, temp_mtrx2);	//multiply to 0_5
	

	copy_mtrx_contents(temp_mtrx2, final_trans_mtrx);

	for (int i = 0; i < 4; i++)
	{
		forward_POS[i] = final_trans_mtrx[i][3];
	}
	//print_mtrx(final_trans_mtrx);
}


void TracGeneration()
{
	double in_theta1 = 0, in_theta2 = 0, in_theta4 = 0;
	double in_d_val3 = 0;double phi = 0;
	double tf_x1, tf_x2, tf_x3;
	double tf_y1, tf_y2, tf_y3;
	double tf_z1, tf_z2, tf_z3;

	double tf_phi1, tf_phi2, tf_phi3;

	// goal pos
	double tf_x_goal, tf_y_goal, tf_z_goal, tf_phi_goal;
	double travel_time_in;
	/////// TRAJ PLANNING
	std::cout << "  ---TRAJECTORY/PATH PLANNER--- " << std::endl;
	std::cout << "Move: Please the starting configuration for the trajectory to be planned:" << std::endl;
	std::cout << "   Please enter the first variable THETA1: ";
	std::cin >> in_theta1;
	std::cout << "   Please enter the second variable THETA2: ";
	std::cin >> in_theta2;
	std::cout << "   Please enter the third variable D3: ";
	std::cin >> in_d_val3;
	std::cout << "   Please enter the fourth variable THETA4: ";
	std::cin >> in_theta4;

	if ((in_theta1 > THETA1_MAX || in_theta1 < THETA1_MIN) || ((in_theta2 > THETA2_MAX || in_theta2 < THETA2_MIN)) ||
		(in_d_val3 > D3_MAX || in_d_val3 < D3_MIN) || (in_theta4 > THETA4_MAX || in_theta4 < THETA4_MIN))
	{
		cout << " user giving the invalid inputs" << endl;
		system("pause");
	}

	
	JOINT initial_move = { in_theta1, in_theta2, in_d_val3, in_theta4 };

	std::cout << "   Moving to configuration [" << in_theta1 << ", " << in_theta2 << ", " << in_d_val3 << ", " << in_theta4 << "] ..." << std::endl;

	// move to intial config
	MoveToConfiguration(initial_move, true);
	ForwardKIN(in_theta1, in_theta2, in_d_val3, in_theta4);

	
	std::cout << "\nPlease input the three desired intermediate tool frames [x, y, z, phi]:" << std::endl;
	std::cout << " The first intermediate tool frame:" << std::endl;
	std::cout << "\t\t x value: ";
	std::cin >> tf_x1;
	std::cout << "\t\t y value: ";
	std::cin >> tf_y1;
	std::cout << "\t\t z value: ";
	std::cin >> tf_z1;
	std::cout << "\t\t phi value: ";
	std::cin >> tf_phi1;
	
	std::cout << " The second intermediate tool frame:" << std::endl;
	std::cout << "\t\t x value: ";
	std::cin >> tf_x2;
	std::cout << "\t\t y value: ";
	std::cin >> tf_y2;
	std::cout << "\t\t z value: ";
	std::cin >> tf_z2;
	std::cout << "\t\t phi value: ";
	std::cin >> tf_phi2;
	std::cout << " The third intermediate tool frame:" << std::endl;
	std::cout << "\t\t x value: ";
	std::cin >> tf_x3;
	std::cout << "\t\t y value: ";
	std::cin >> tf_y3;
	std::cout << "\t\t z value: ";
	std::cin >> tf_z3;
	std::cout << "\t\t phi value: ";
	std::cin >> tf_phi3;
	std::cout << "\nPlease input the desired tool goal frame [x, y, z, phi]:" << std::endl;
	std::cout << "\t\t x value: ";

	// goal points 
	std::cin >> tf_x_goal;
	std::cout << "\t\t y value: ";
	std::cin >> tf_y_goal;
	std::cout << "\t\t z value: ";
	std::cin >> tf_z_goal;
	std::cout << "\t\t phi value: ";
	std::cin >> tf_phi_goal;
	
	std::cout << "\nPlease input the total desired time (in seconds): ";
	std::cin >> travel_time_in;

	solve(tf_x1, tf_y1, tf_z1, tf_phi1);
	
	
	// sloving inverse for via points and stores 
	JOINT via_Point_1st_sol;
	JOINT via_Point_2nd_sol;
	JOINT via_Point_3rd_sol;
	JOINT via_Point_goal_sol;

	for (int i = 0; i < 4; i++)
	{
		via_Point_1st_sol[i] = via_point_sol[i];
	}

	solve(tf_x2, tf_y2, tf_z2, tf_phi2);
	for (int i = 0; i < 4; i++)
	{
		via_Point_2nd_sol[i] = via_point_sol[i];
	}

	solve(tf_x3, tf_y3, tf_z3, tf_phi3);
	for (int i = 0; i < 4; i++)
	{
		via_Point_3rd_sol[i] = via_point_sol[i];
	}

	solve(tf_x_goal, tf_y_goal, tf_z_goal, tf_phi_goal);
	for (int i = 0; i < 4; i++)
	{
		via_Point_goal_sol[i] = via_point_sol[i];
	}

	
	double time_sqr = pow(travel_time_in, 2);
	double time_interval = travel_time_in / 4;
	double time_sqr_div = pow(time_interval, 2);
	
	// for the 1st via point
	double a0_via_1st_x = in_theta1;
	double a1_via_1st_x = 0;
	double a2_via_1st_x = -1 * ((3.0f * ((14 * via_Point_2nd_sol[0]) - (52 * via_Point_1st_sol[0]) - (4 * via_Point_3rd_sol[0]) + via_Point_goal_sol[0] + (41 * in_theta1))) / (56 * time_sqr));
	double a3_via_1st_x = ((42 * via_Point_2nd_sol[0]) - (100 * via_Point_1st_sol[0]) - (12 * via_Point_3rd_sol[0]) + (3 * via_Point_goal_sol[0]) + (67 * in_theta1)) / (56 * time_sqr * travel_time_in);

	//double pos_via_x_1 = a0_via_1st_x + (a1_via_1st_x * time_interval) + (a2_via_1st_x * time_sqr_div) + (a3_via_1st_x * time_interval * time_sqr_div);
	//double vel_via_x_1 = a1_via_1st_x + (2.0f * a2_via_1st_x  * time_interval) + (3.0f * a3_via_1st_x * time_sqr_div);
	//double acc_via_x_1 = 2.0f * a2_via_1st_x + (6.0f * a3_via_1st_x * time_interval);

	double pos_via_x_1 = a0_via_1st_x + (a1_via_1st_x * travel_time_in) + (a2_via_1st_x * time_sqr) + (a3_via_1st_x * travel_time_in * time_sqr);
	double vel_via_x_1 = a1_via_1st_x + (2.0f * a2_via_1st_x  * travel_time_in) + (3.0f * a3_via_1st_x * time_sqr);
	double acc_via_x_1 = 2.0f * a2_via_1st_x + (6.0f * a3_via_1st_x * travel_time_in);


	double a0_via_1st_y = in_theta2;
	double a1_via_1st_y = 0;
	double a2_via_1st_y = -1 * ((3.0f * ((14 * via_Point_2nd_sol[1]) - (52 * via_Point_1st_sol[1]) - (4 * via_Point_3rd_sol[1]) + via_Point_goal_sol[1] + (41 * in_theta2))) / (56 * time_sqr));
	double a3_via_1st_y = ((42 * via_Point_2nd_sol[1]) - (100 * via_Point_1st_sol[1]) - (12 * via_Point_3rd_sol[1]) + (3 * via_Point_goal_sol[1]) + (67 * in_theta2)) / (56 * time_sqr * travel_time_in);

	//double pos_via_y_1 = a0_via_1st_y + a1_via_1st_y * time_interval + a2_via_1st_y * time_sqr_div + a3_via_1st_y * time_interval * time_sqr_div;
	//double vel_via_y_1 = a1_via_1st_y + (2.0f * a2_via_1st_y  * time_interval) + (3.0f * a3_via_1st_y * time_sqr_div);
	//double acc_via_y_1 = 2 * a2_via_1st_y + (6.0f * a3_via_1st_y * time_interval);

	double pos_via_y_1 = a0_via_1st_y + a1_via_1st_y * travel_time_in + a2_via_1st_y * time_sqr + a3_via_1st_y * travel_time_in * time_sqr;
	double vel_via_y_1 = a1_via_1st_y + (2.0f * a2_via_1st_y  * travel_time_in) + (3.0f * a3_via_1st_y * time_sqr);
	double acc_via_y_1 = 2 * a2_via_1st_y + (6.0f * a3_via_1st_y * travel_time_in);

	double a0_via_1st_z = in_theta4;
	double a1_via_1st_z = 0;
	double a2_via_1st_z = -1 * ((3.0f * ((14 * via_Point_2nd_sol[3]) - (52 * via_Point_1st_sol[3]) - (4 * via_Point_3rd_sol[3]) + via_Point_goal_sol[3] + (41 * in_theta4))) / (56 * time_sqr));
	double a3_via_1st_z = ((42 * via_Point_2nd_sol[3]) - (100 * via_Point_1st_sol[3]) - (12 * via_Point_3rd_sol[3]) + (3 * via_Point_goal_sol[3]) + (67 * in_theta4)) / (56 * time_sqr * travel_time_in);

	//double pos_via_z_1 = a0_via_1st_z + a1_via_1st_z * time_interval + a2_via_1st_z * time_sqr_div + a3_via_1st_z * time_interval * time_sqr_div;
	//double vel_via_z_1 = a1_via_1st_z + (2.0f * a2_via_1st_z  * time_interval) + (3.0f * a3_via_1st_z * time_sqr_div);
	//double acc_via_z_1 = 2 * a2_via_1st_z + 6 * a3_via_1st_z * time_interval;


	double pos_via_z_1 = a0_via_1st_z + a1_via_1st_z * travel_time_in + a2_via_1st_z * time_sqr + a3_via_1st_z * travel_time_in * time_sqr;
	double vel_via_z_1 = a1_via_1st_z + (2.0f * a2_via_1st_z  * travel_time_in) + (3.0f * a3_via_1st_z * time_sqr);
	double acc_via_z_1 = 2 * a2_via_1st_z + 6 * a3_via_1st_z * travel_time_in;
	
	double a0_via_1st_d3 = in_d_val3;
	double a1_via_1st_d3 = 0;
	double a2_via_1st_d3 = -1 * ((3.0f * ((14 * via_Point_2nd_sol[2]) - (52 * via_Point_1st_sol[2]) - (4 * via_Point_3rd_sol[2]) + via_Point_goal_sol[2] + (41 * in_d_val3))) / (56 * time_sqr));
	double a3_via_1st_d3 = ((42 * via_Point_2nd_sol[2]) - (100 * via_Point_1st_sol[2]) - (12 * via_Point_3rd_sol[2]) + (3 * via_Point_goal_sol[2]) + (67 * in_d_val3)) / (56 * time_sqr * travel_time_in);

	//double pos_via_d3_1 = a0_via_1st_d3 + a1_via_1st_d3 * time_interval + a2_via_1st_d3 * time_sqr_div + a3_via_1st_d3 * time_interval * time_sqr_div;
	//double vel_via_d3_1 = a1_via_1st_d3 + (2.0f * a2_via_1st_d3  * time_interval) + (3.0f * a3_via_1st_d3 * time_sqr_div);
	//double acc_via_d3_1 = 2 * a2_via_1st_d3 + (6.0f * a3_via_1st_d3 * time_interval);


	double pos_via_d3_1 = a0_via_1st_d3 + a1_via_1st_d3 * travel_time_in + a2_via_1st_d3 * time_sqr + a3_via_1st_d3 * travel_time_in * time_sqr;
	double vel_via_d3_1 = a1_via_1st_d3 + (2.0f * a2_via_1st_d3  * travel_time_in) + (3.0f * a3_via_1st_d3 * time_sqr);
	double acc_via_d3_1 = 2 * a2_via_1st_d3 + (6.0f * a3_via_1st_d3 * travel_time_in);
	
	// we putting d3 as zero for vel and acc
	JOINT config_via_1 = { pos_via_x_1, pos_via_y_1, pos_via_d3_1 ,pos_via_z_1 };
	JOINT vel_via_1 = { vel_via_x_1, vel_via_y_1, vel_via_d3_1, vel_via_z_1 };
	JOINT acc_via_1 = { acc_via_x_1, acc_via_y_1, acc_via_d3_1 , acc_via_z_1 };

	bool config_limit_1 = false;
	if (Theta1Check(config_via_1[0]) && Theta2Check(config_via_1[1]) && Theta4Check(config_via_1[3]) && D3Check(config_via_1[2]))
	{
		config_limit_1 = true;
	}

	bool config_vel_1 = false;
	if (VelCheck(vel_via_1[0]) && VelCheck(vel_via_1[1]) && VelCheck(vel_via_1[3]) && vel_D3Check(vel_via_1[2]))
	{
		config_vel_1 = true;
	}

	bool config1_acc_1 = false;
	if (AccCheck(acc_via_1[0]) && AccCheck(acc_via_1[1]) && AccCheck(acc_via_1[3]) && acc_D3Check(acc_via_1[2]))
	{
		config1_acc_1 = true;
	}

	
	if (config_limit_1 && config_vel_1 && config1_acc_1)
	{
		MoveWithConfVelAcc(config_via_1, vel_via_1, acc_via_1);
		DWORD time_to_finish = (DWORD)(travel_time_in * 1000);
		Sleep(time_to_finish);
		//Sleep(travel_time_in * 1000);
	}
	else
	{
		cout << " Out of Range For Via Points 1" << endl;
	}
	
	 
	// for the 2nd via point 
	double a0_via_2nd_x = via_Point_1st_sol[0];
	double a1_via_2nd_x = (3 * ((4 * via_Point_1st_sol[0]) + (14 * via_Point_2nd_sol[0]) - (4 * via_Point_3rd_sol[0]) + via_Point_goal_sol[0] - (15 * in_theta1))) / (56 * travel_time_in);
	double a2_via_2nd_x = ((3.0f * ((14 * via_Point_2nd_sol[0]) - (24 * via_Point_1st_sol[0]) - (4 * via_Point_3rd_sol[0]) + via_Point_goal_sol[0] + (13 * in_theta1))) / (28 * time_sqr));
	double a3_via_2nd_x = -1 * (((70 * via_Point_2nd_sol[0]) - (76 * via_Point_1st_sol[0]) - (36 * via_Point_3rd_sol[0]) + (9 * via_Point_goal_sol[0]) + (33 * in_theta1)) / (56 * time_sqr * travel_time_in));

	//double pos_via_x_2 = a0_via_2nd_x + a1_via_2nd_x * time_interval + a2_via_2nd_x * time_sqr_div + a3_via_2nd_x * time_interval * time_sqr_div;
	//double vel_via_x_2 = a1_via_2nd_x + 2 * a2_via_2nd_x  * time_interval + 3 * a3_via_2nd_x * time_sqr_div;
	//double acc_via_x_2 = 2 * a2_via_2nd_x + 6 * a3_via_2nd_x * time_interval;
	double pos_via_x_2 = a0_via_2nd_x + a1_via_2nd_x * travel_time_in + a2_via_2nd_x * time_sqr + a3_via_2nd_x * travel_time_in * time_sqr;
	double vel_via_x_2 = a1_via_2nd_x + 2 * a2_via_2nd_x  * travel_time_in + 3 * a3_via_2nd_x * time_sqr;
	double acc_via_x_2 = 2 * a2_via_2nd_x + 6 * a3_via_2nd_x * travel_time_in;


	double a0_via_2nd_y = via_Point_1st_sol[1];
	double a1_via_2nd_y = (3 * ((4 * via_Point_1st_sol[1]) + (14 * via_Point_2nd_sol[1]) - (4 * via_Point_3rd_sol[1]) + via_Point_goal_sol[1] - (15 * in_theta2))) / (56 * travel_time_in);
	double a2_via_2nd_y = ((3.0f * ((14 * via_Point_2nd_sol[1]) - (24 * via_Point_1st_sol[1]) - (4 * via_Point_3rd_sol[1]) + via_Point_goal_sol[1] + (13 * in_theta2))) / (28 * time_sqr));
	double a3_via_2nd_y = -1 * (((70 * via_Point_2nd_sol[1]) - (76 * via_Point_1st_sol[1]) - (36 * via_Point_3rd_sol[1]) + (9 * via_Point_goal_sol[1]) + (33 * in_theta2)) / (56 * time_sqr * travel_time_in));

	//double pos_via_y_2 = a0_via_2nd_y + a1_via_2nd_y * time_interval + a2_via_2nd_y * time_sqr_div + a3_via_2nd_y * time_interval * time_sqr_div;
	//double vel_via_y_2 = a1_via_2nd_y + 2 * a2_via_2nd_y  * time_interval + 3 * a3_via_2nd_y * time_sqr_div;
	//double acc_via_y_2 = 2 * a2_via_2nd_y + 6 * a3_via_2nd_y * time_interval;

	double pos_via_y_2 = a0_via_2nd_y + a1_via_2nd_y * travel_time_in + a2_via_2nd_y * time_sqr + a3_via_2nd_y * travel_time_in * time_sqr;
	double vel_via_y_2 = a1_via_2nd_y + 2 * a2_via_2nd_y  * travel_time_in + 3 * a3_via_2nd_y * time_sqr;
	double acc_via_y_2 = 2 * a2_via_2nd_y + 6 * a3_via_2nd_y * travel_time_in;

	double a0_via_2nd_z = via_Point_1st_sol[3];
	double a1_via_2nd_z = (3 * ((4 * via_Point_1st_sol[3]) + (14 * via_Point_2nd_sol[3]) - (4 * via_Point_3rd_sol[3]) + via_Point_goal_sol[3] - (15 * in_theta4))) / (56 * travel_time_in);
	double a2_via_2nd_z = ((3.0f * ((14 * via_Point_2nd_sol[3]) - (24 * via_Point_1st_sol[3]) - (4 * via_Point_3rd_sol[3]) + via_Point_goal_sol[3] + (13 * in_theta4))) / (28 * time_sqr));
	double a3_via_2nd_z = -1 * (((70 * via_Point_2nd_sol[3]) - (76 * via_Point_1st_sol[3]) - (36 * via_Point_3rd_sol[3]) + (9 * via_Point_goal_sol[3]) + (33 * in_theta4)) / (56 * time_sqr * travel_time_in));

	//double pos_via_z_2 = a0_via_2nd_z + a1_via_2nd_z * time_interval + a2_via_2nd_z * time_sqr_div + a3_via_2nd_z * time_interval * time_sqr_div;
	//double vel_via_z_2 = a1_via_2nd_z + 2 * a2_via_2nd_z  * time_interval + 3 * a3_via_2nd_z * time_sqr_div;
	//double acc_via_z_2 = 2 * a2_via_2nd_z + 6 * a3_via_2nd_z * time_interval;

	double pos_via_z_2 = a0_via_2nd_z + a1_via_2nd_z * travel_time_in + a2_via_2nd_z * time_sqr + a3_via_2nd_z * travel_time_in * time_sqr;
	double vel_via_z_2 = a1_via_2nd_z + 2 * a2_via_2nd_z  * travel_time_in + 3 * a3_via_2nd_z * time_sqr;
	double acc_via_z_2 = 2 * a2_via_2nd_z + 6 * a3_via_2nd_z * travel_time_in;

	double a0_via_2nd_d3 = via_Point_1st_sol[2];
	double a1_via_2nd_d3 = (3 * ((4 * via_Point_1st_sol[2]) + (14 * via_Point_2nd_sol[2]) - (4 * via_Point_3rd_sol[2]) + via_Point_goal_sol[2] - (15 * in_d_val3))) / (56 * travel_time_in);
	double a2_via_2nd_d3 = ((3.0f * ((14 * via_Point_2nd_sol[2]) - (24 * via_Point_1st_sol[2]) - (4 * via_Point_3rd_sol[2]) + via_Point_goal_sol[2] + (13 * in_d_val3))) / (28 * time_sqr));
	double a3_via_2nd_d3 = -1 * (((70 * via_Point_2nd_sol[2]) - (76 * via_Point_1st_sol[2]) - (36 * via_Point_3rd_sol[2]) + (9 * via_Point_goal_sol[2]) + (33 * in_d_val3)) / (56 * time_sqr * travel_time_in));

	//double pos_via_d3_2 = a0_via_2nd_d3 + a1_via_2nd_d3 * time_interval + a2_via_2nd_d3 * time_sqr_div + a3_via_2nd_d3 * time_interval * time_sqr_div;
	//double vel_via_d3_2 = a1_via_2nd_d3 + (2.0f * a2_via_2nd_d3  * time_interval) + (3.0f * a3_via_2nd_d3 * time_sqr_div);
	//double acc_via_d3_2 = 2 * a2_via_2nd_d3 + (6.0f * a3_via_2nd_d3 * time_interval);

	double pos_via_d3_2 = a0_via_2nd_d3 + a1_via_2nd_d3 * travel_time_in + a2_via_2nd_d3 * time_sqr + a3_via_2nd_d3 * travel_time_in * time_sqr;
	double vel_via_d3_2 = a1_via_2nd_d3 + (2.0f * a2_via_2nd_d3  * travel_time_in) + (3.0f * a3_via_2nd_d3 * time_sqr);
	double acc_via_d3_2 = 2 * a2_via_2nd_d3 + (6.0f * a3_via_2nd_d3 * travel_time_in);

	// we putting d3 as zero for vel and acc
	JOINT config_via_2 = { pos_via_x_2, pos_via_y_2,pos_via_d3_2,pos_via_z_2 };
	JOINT vel_via_2 = { vel_via_x_2, vel_via_y_2, vel_via_d3_2, vel_via_z_2 };
	JOINT acc_via_2 = { acc_via_x_2, acc_via_y_2, acc_via_d3_2 , acc_via_z_2 };


	bool config_limit_2 = false;
	if (Theta1Check(config_via_1[0]) && Theta2Check(config_via_1[1]) && Theta4Check(config_via_1[3]) && D3Check(config_via_1[2]))
	{
		config_limit_2 = true;
	}

	bool config_vel_2 = false;
	if (VelCheck(vel_via_1[0]) && VelCheck(vel_via_1[1]) && VelCheck(vel_via_1[3]) && vel_D3Check(vel_via_1[2]))
	{
		config_vel_2 = true;
	}

	bool config1_acc_2 = false;
	if (AccCheck(acc_via_1[0]) && AccCheck(acc_via_1[1]) && AccCheck(acc_via_1[3]) && acc_D3Check(acc_via_1[2]))
	{
		config1_acc_2 = true;
	}

	if (config_limit_2 && config_vel_2 && config1_acc_2)
	{
		MoveWithConfVelAcc(config_via_2, vel_via_2, acc_via_2);
		DWORD time_to_finish = (DWORD)(travel_time_in * 1000);
		Sleep(time_to_finish);
		//Sleep(travel_time_in * 1000);
	}
	else
	{
		cout << " Out of Range For Via Points 2" << endl;
	}
	
	// for the 3rd via point 
	
	double a0_via_3rd_x = via_Point_2nd_sol[0];
	double a1_via_3rd_x = -1 * ((3 * ((4 * via_Point_1st_sol[0]) - ( 4 * via_Point_3rd_sol[0]) + via_Point_goal_sol[0]  - in_theta1)) / (14 * travel_time_in ));
	double a2_via_3rd_x = -1 * ((3 * ((6 * via_Point_2nd_sol[0]) - (4 * via_Point_1st_sol[0])  - (4 * via_Point_3rd_sol[0] ) + via_Point_goal_sol[0] + in_theta1)) / (8 * time_sqr));
	double a3_via_3rd_x = ((70 * via_Point_2nd_sol[0]) - (36 * via_Point_1st_sol[0]) - (76 * via_Point_3rd_sol[0]) + (33 * via_Point_goal_sol[0]) + (9 * in_theta1)) / (56 * time_sqr * travel_time_in);

	//double pos_via_x_3 = a0_via_3rd_x + a1_via_3rd_x * time_interval + a2_via_3rd_x * time_sqr_div + a3_via_3rd_x * time_interval * time_sqr_div;
	//double vel_via_x_3 = a1_via_3rd_x + 2 * a2_via_3rd_x  * time_interval + 3 * a3_via_3rd_x * time_sqr_div;
	//double acc_via_x_3 = 2 * a2_via_3rd_x + 6 * a3_via_3rd_x * time_interval;

	double pos_via_x_3 = a0_via_3rd_x + a1_via_3rd_x * travel_time_in + a2_via_3rd_x * time_sqr + a3_via_3rd_x * travel_time_in * time_sqr;
	double vel_via_x_3 = a1_via_3rd_x + 2 * a2_via_3rd_x  * travel_time_in + 3 * a3_via_3rd_x * time_sqr;
	double acc_via_x_3 = 2 * a2_via_3rd_x + 6 * a3_via_3rd_x * travel_time_in;

	double a0_via_3rd_y = via_Point_2nd_sol[1];
	double a1_via_3rd_y = -1 * ((3 * ((4 * via_Point_1st_sol[1]) - (4 * via_Point_3rd_sol[1]) + via_Point_goal_sol[1] - in_theta2)) / (14 * travel_time_in));
	double a2_via_3rd_y = -1 * ((3 * ((6 * via_Point_2nd_sol[1]) - (4 * via_Point_1st_sol[1]) - (4 * via_Point_3rd_sol[1]) + via_Point_goal_sol[1] + in_theta2)) / (8 * time_sqr));
	double a3_via_3rd_y = ((70 * via_Point_2nd_sol[1]) - (36 * via_Point_1st_sol[1]) - (76 * via_Point_3rd_sol[1]) + (33 * via_Point_goal_sol[1]) + (9 * in_theta2)) / (56 * time_sqr * travel_time_in);

	//double pos_via_y_3 = a0_via_3rd_y + a1_via_3rd_y * time_interval + a2_via_3rd_y * time_sqr_div + a3_via_3rd_y * time_interval * time_sqr_div;
	//double vel_via_y_3 = a1_via_3rd_y + 2 * a2_via_3rd_y  * time_interval + 3 * a3_via_3rd_y * time_sqr_div;
	//double acc_via_y_3 = 2 * a2_via_3rd_y + 6 * a3_via_3rd_y * time_interval;

	double pos_via_y_3 = a0_via_3rd_y + a1_via_3rd_y * travel_time_in + a2_via_3rd_y * time_sqr + a3_via_3rd_y * travel_time_in * time_sqr;
	double vel_via_y_3 = a1_via_3rd_y + 2 * a2_via_3rd_y  * travel_time_in + 3 * a3_via_3rd_y * time_sqr;
	double acc_via_y_3 = 2 * a2_via_3rd_y + 6 * a3_via_3rd_y * travel_time_in;

	double a0_via_3rd_z = via_Point_2nd_sol[3];
	double a1_via_3rd_z = -1 * ((3 * ((4 * via_Point_1st_sol[3]) - (4 * via_Point_3rd_sol[3]) + via_Point_goal_sol[3] - in_theta4)) / (14 * travel_time_in));
	double a2_via_3rd_z = -1 * ((3 * ((6 * via_Point_2nd_sol[3]) - (4 * via_Point_1st_sol[3]) - (4 * via_Point_3rd_sol[3]) + via_Point_goal_sol[3] + in_theta4)) / (8 * time_sqr));
	double a3_via_3rd_z = ((70 * via_Point_2nd_sol[3]) - (36 * via_Point_1st_sol[3]) - (76 * via_Point_3rd_sol[3]) + (33 * via_Point_goal_sol[3]) + (9 * in_theta4)) / (56 * time_sqr * travel_time_in);

	//double pos_via_z_3 = a0_via_3rd_z + a1_via_3rd_z * time_interval + a2_via_3rd_z * time_sqr_div + a3_via_3rd_z * time_interval * time_sqr_div;
	//double vel_via_z_3 = a1_via_3rd_z + 2 * a2_via_3rd_z  * time_interval + 3 * a3_via_3rd_z * time_sqr_div;
	//double acc_via_z_3 = 2 * a2_via_3rd_z + 6 * a3_via_3rd_z * time_interval;


	double pos_via_z_3 = a0_via_3rd_z + a1_via_3rd_z * travel_time_in + a2_via_3rd_z * time_sqr + a3_via_3rd_z * travel_time_in * time_sqr;
	double vel_via_z_3 = a1_via_3rd_z + 2 * a2_via_3rd_z  * travel_time_in + 3 * a3_via_3rd_z * time_sqr;
	double acc_via_z_3 = 2 * a2_via_3rd_z + 6 * a3_via_3rd_z * travel_time_in;

	double a0_via_3rd_d3 = via_Point_2nd_sol[2];
	double a1_via_3rd_d3 = -1 * ((3 * ((4 * via_Point_1st_sol[2]) - (4 * via_Point_3rd_sol[2]) + via_Point_goal_sol[2] - in_d_val3)) / (14 * travel_time_in));
	double a2_via_3rd_d3 = -1 * ((3 * ((6 * via_Point_2nd_sol[2]) - (4 * via_Point_1st_sol[2]) - (4 * via_Point_3rd_sol[2]) + via_Point_goal_sol[2] + in_d_val3)) / (8 * time_sqr));
	double a3_via_3rd_d3 = ((70 * via_Point_2nd_sol[2]) - (36 * via_Point_1st_sol[2]) - (76 * via_Point_3rd_sol[2]) + (33 * via_Point_goal_sol[2]) + (9 * in_d_val3)) / (56 * time_sqr * travel_time_in);

	//double pos_via_d3_3 = a0_via_3rd_d3 + a1_via_3rd_d3 * time_interval + a2_via_3rd_d3 * time_sqr_div + a3_via_3rd_d3 * time_interval * time_sqr_div;
	//double vel_via_d3_3 = a1_via_3rd_d3 + (2.0f * a2_via_3rd_d3  * time_interval) + (3.0f * a3_via_3rd_d3 * time_sqr_div);
	//double acc_via_d3_3 = 2 * a2_via_3rd_d3 + (6.0f * a3_via_3rd_d3 * time_interval);

	double pos_via_d3_3 = a0_via_3rd_d3 + a1_via_3rd_d3 * travel_time_in + a2_via_3rd_d3 * time_sqr + a3_via_3rd_d3 * travel_time_in * time_sqr;
	double vel_via_d3_3 = a1_via_3rd_d3 + (2.0f * a2_via_3rd_d3  * travel_time_in) + (3.0f * a3_via_3rd_d3 * time_sqr);
	double acc_via_d3_3 = 2 * a2_via_3rd_d3 + (6.0f * a3_via_3rd_d3 * travel_time_in);

	// we putting d3 as zero for vel and acc
	JOINT config_via_3 = { pos_via_x_3, pos_via_y_3, pos_via_d3_3, pos_via_z_3 };
	JOINT vel_via_3 = { vel_via_x_3, vel_via_y_3, vel_via_d3_3, vel_via_z_3 };
	JOINT acc_via_3 = { acc_via_x_3, acc_via_y_3, acc_via_d3_3 , acc_via_z_3 };


	bool config_limit_3 = false;
	if (Theta1Check(config_via_1[0]) && Theta2Check(config_via_1[1]) && Theta4Check(config_via_1[3]) && D3Check(config_via_1[2]))
	{
		config_limit_3 = true;
	}

	bool config_vel_3 = false;
	if (VelCheck(vel_via_1[0]) && VelCheck(vel_via_1[1]) && VelCheck(vel_via_1[3]) && vel_D3Check(vel_via_1[2]))
	{
		config_vel_3 = true;
	}

	bool config1_acc_3 = false;
	if (AccCheck(acc_via_1[0]) && AccCheck(acc_via_1[1]) && AccCheck(acc_via_1[3]) && acc_D3Check(acc_via_1[2]))
	{
		config1_acc_3 = true;
	}

	if (config_limit_3 && config_vel_3 && config1_acc_3)
	{
		MoveWithConfVelAcc(config_via_3, vel_via_3, acc_via_3);
		DWORD time_to_finish = (DWORD) (travel_time_in * 1000);
		Sleep(time_to_finish);
		//Sleep(travel_time_in * 1000);
	}
	else
	{
		cout << " Out of Range For Via Points 3" << endl;
	}

	// for the 3rd to goal via point 

	double a0_gx = via_Point_3rd_sol[0];
	double a1_gx = -1 * ((3 * ((14 * via_Point_2nd_sol[0]) - (4 * via_Point_1st_sol[0]) + (4 * via_Point_3rd_sol[0]) - (15 * via_Point_goal_sol[0]) + in_theta1)) / (56 * travel_time_in));
	double a2_gx = ((3 * ((14 * via_Point_2nd_sol[0]) - (4 * via_Point_1st_sol[0]) - (24 * via_Point_3rd_sol[0]) + (13 * via_Point_goal_sol[0]) + in_theta1)) / (28 * time_sqr));
	double a3_gx = -1 * (((42 * via_Point_2nd_sol[0]) - (12 * via_Point_1st_sol[0]) - (100 * via_Point_3rd_sol[0]) + (67 * via_Point_goal_sol[0]) + (3 * in_theta1)) / (56 * travel_time_in * time_sqr));

	//double pos_via_x_g = a0_gx + a1_gx * time_interval + a2_via_3rd_x * time_sqr_div + a3_gx * time_interval * time_sqr_div;
	//double vel_via_x_g = a1_gx + 2 * a2_gx  * time_interval + 3 * a3_gx * time_sqr_div;
	//double acc_via_x_g = 2 * a2_gx + 6 * a3_gx * time_interval;

	double pos_via_x_g = a0_gx + a1_gx * travel_time_in + a2_gx * time_sqr + a3_gx * travel_time_in * time_sqr;
	double vel_via_x_g = a1_gx + 2 * a2_gx  * travel_time_in + 3 * a3_gx * time_sqr;
	double acc_via_x_g = 2 * a2_gx + 6 * a3_gx * travel_time_in;

	double a0_yg = via_Point_3rd_sol[1];
	double a1_yg = -1 * ((3 * ((14 * via_Point_2nd_sol[1]) - (4 * via_Point_1st_sol[1]) + (4 * via_Point_3rd_sol[1]) - (15 * via_Point_goal_sol[1]) + in_theta2)) / (56 * travel_time_in));
	double a2_yg = ((3 * ((14 * via_Point_2nd_sol[1]) - (4 * via_Point_1st_sol[1]) - (24 * via_Point_3rd_sol[1]) + (13 * via_Point_goal_sol[1]) + in_theta2)) / (28 * time_sqr));
	double a3_yg = -1 * (((42 * via_Point_2nd_sol[1]) - (12 * via_Point_1st_sol[1]) - (100 * via_Point_3rd_sol[1]) + (67 * via_Point_goal_sol[1]) + (3 * in_theta2)) / (56 * travel_time_in * time_sqr));

	//double pos_via_y_g = a0_yg + a1_yg * time_interval + a2_yg * time_sqr_div + a3_yg * time_interval * time_sqr_div;
	//double vel_via_y_g = a1_yg + 2 * a2_yg  * time_interval + 3 * a3_yg * time_sqr_div;
	//double acc_via_y_g = 2 * a2_yg + 6 * a3_yg * time_interval;

	double pos_via_y_g = a0_yg + a1_yg * travel_time_in + a2_yg * time_sqr + a3_yg * travel_time_in * time_sqr;
	double vel_via_y_g = a1_yg + 2 * a2_yg  * travel_time_in + 3 * a3_yg * time_sqr;
	double acc_via_y_g = 2 * a2_yg + 6 * a3_yg * travel_time_in;

	double a0_gz = via_Point_3rd_sol[3];
	double a1_gz = -1 * ((3 * ((14 * via_Point_2nd_sol[3]) - (4 * via_Point_1st_sol[3]) + (4 * via_Point_3rd_sol[3]) - (15 * via_Point_goal_sol[3]) + in_theta4)) / (56 * travel_time_in));
	double a2_gz = ((3 * ((14 * via_Point_2nd_sol[3]) - (4 * via_Point_1st_sol[3]) - (24 * via_Point_3rd_sol[3]) + (13 * via_Point_goal_sol[3]) + in_theta4)) / (28 * time_sqr));
	double a3_gz = -1 * (((42 * via_Point_2nd_sol[3]) - (12 * via_Point_1st_sol[3]) - (100 * via_Point_3rd_sol[3]) + (67 * via_Point_goal_sol[3]) + (3 * in_theta4)) / (56 * travel_time_in * time_sqr));


	//double pos_via_z_g = a0_gz + a1_via_3rd_z * time_interval + a2_gz * time_sqr_div + a3_gz * time_interval * time_sqr_div;
	//double vel_via_z_g = a1_gz + 2 * a3_gz  * time_interval + 3 * a3_gz * time_sqr_div;
	//double acc_via_z_g = 2 * a2_gz + 6 * a3_gz * time_interval;

	double pos_via_z_g = a0_gz + a1_gz * travel_time_in + a2_gz * time_sqr + a3_gz * travel_time_in * time_sqr;
	double vel_via_z_g = a1_gz + 2 * a2_gz  * travel_time_in + 3 * a3_gz * time_sqr;
	double acc_via_z_g = 2 * a2_gz + 6 * a3_gz * travel_time_in;



	double a0_via_g_d3 = via_Point_3rd_sol[2];
	double a1_via_g_d3 = -1 * ((3 * ((14 * via_Point_2nd_sol[2]) - (4 * via_Point_1st_sol[2]) + (4 * via_Point_3rd_sol[2]) - (15 * via_Point_goal_sol[2]) + in_d_val3)) / (56 * travel_time_in));
	double a2_via_g_d3 = ((3 * ((14 * via_Point_2nd_sol[2]) - (4 * via_Point_1st_sol[2]) - (24 * via_Point_3rd_sol[2]) + (13 * via_Point_goal_sol[2]) + in_d_val3)) / (28 * time_sqr));
	double a3_via_g_d3 = -1 * (((42 * via_Point_2nd_sol[2]) - (12 * via_Point_1st_sol[2]) - (100 * via_Point_3rd_sol[2]) + (67 * via_Point_goal_sol[2]) + (3 * in_d_val3)) / (56 * travel_time_in * time_sqr));

	//double pos_via_d3_g = a0_via_g_d3 + a1_via_g_d3 * time_interval + a2_via_g_d3 * time_sqr_div + a3_via_g_d3 * time_interval * time_sqr_div;
	//double vel_via_d3_g = a1_via_g_d3 + (2.0f * a2_via_g_d3  * time_interval) + (3.0f * a3_via_g_d3 * time_sqr_div);
	//double acc_via_d3_g = 2 * a2_via_g_d3 + (6.0f * a3_via_g_d3 * time_interval);

	double pos_via_d3_g = a0_via_g_d3 + a1_via_g_d3 * travel_time_in + a2_via_g_d3 * time_sqr + a3_via_g_d3 * travel_time_in * time_sqr;
	double vel_via_d3_g = a1_via_g_d3 + (2.0f * a2_via_g_d3  * travel_time_in) + (3.0f * a3_via_g_d3 * time_sqr);
	double acc_via_d3_g = 2 * a2_via_g_d3 + (6.0f * a3_via_g_d3 * travel_time_in);

	// we putting d3 as zero for vel and acc
	JOINT config_via_g = { pos_via_x_g, pos_via_y_g, pos_via_d3_g,pos_via_z_g };
	JOINT vel_via_g = { vel_via_x_g, vel_via_y_g, vel_via_d3_g, vel_via_z_g };
	JOINT acc_via_g = { acc_via_x_g, acc_via_y_g, acc_via_d3_g , acc_via_z_g };

	bool config_limit_g = false;
	if (Theta1Check(config_via_1[0]) && Theta2Check(config_via_1[1]) && Theta4Check(config_via_1[3]) && D3Check(config_via_1[2]))
	{
		config_limit_g = true;
	}

	bool config_vel_g = false;
	if (VelCheck(vel_via_1[0]) && VelCheck(vel_via_1[1]) && VelCheck(vel_via_1[3]) && vel_D3Check(vel_via_1[2]))
	{
		config_vel_g = true;
	}

	bool config1_acc_g = false;
	if (AccCheck(acc_via_1[0]) && AccCheck(acc_via_1[1]) && AccCheck(acc_via_1[3]) && acc_D3Check(acc_via_1[2]))
	{
		config1_acc_g = true;
	}


	if (config_limit_g && config_vel_g && config1_acc_g)
	{	
		MoveWithConfVelAcc(config_via_g, vel_via_g, acc_via_g);
		//Sleep(travel_time_in * 1000);
	}
	else
	{
		cout << " Out of Range For Goal points" << endl;
	}
	

	
	// storing the values in files
	ofstream outfile1;
	outfile1.open("via_pos.txt");

	outfile1 << in_theta1 << "    " << config_via_1[0] << "    " << config_via_2[0] << "    " << config_via_3[0] << "    " << config_via_g[0] << "\n";
	outfile1 << in_theta2 << "    " << config_via_1[1] << "    " << config_via_2[1] << "    " << config_via_3[1] << "    " << config_via_g[1] << "\n";
	outfile1 << in_d_val3 << "    " << config_via_1[2] << "    " << config_via_2[2] << "    " << config_via_3[2] << "    " << config_via_g[2] << "\n";
	outfile1 << in_theta4 << "    " << config_via_1[3] << "    " << config_via_2[3] << "    " << config_via_3[3] << "    " << config_via_g[3] << "\n";
	
	outfile1.close();

	ofstream outfile2;
	outfile2.open("via_vel.txt");
	
	outfile2 << vel_via_1[0] << "    " << vel_via_2[0] << "    " << vel_via_3[0] << "    " << vel_via_g[0] << "\n";
	outfile2 << vel_via_1[1] << "    " << vel_via_2[1] << "    " << vel_via_3[1] << "    " << vel_via_g[1] << "\n";
	outfile2 << vel_via_1[2] << "    " << vel_via_2[2] << "    " << vel_via_3[2] << "    " << vel_via_g[2] << "\n";
	outfile2 << vel_via_1[3] << "    " << vel_via_2[3] << "    " << vel_via_3[3] << "    " << vel_via_g[3] << "\n";

	outfile2.close();

	ofstream outfile3;
	outfile3.open("via_acc.txt");
	
	outfile3 << acc_via_1[0] << "    " << acc_via_2[0] << "    " << acc_via_3[0] << "    " << acc_via_g[0] << "\n";
	outfile3 << acc_via_1[1] << "    " << acc_via_2[1] << "    " << acc_via_3[1] << "    " << acc_via_g[1] << "\n";
	outfile3 << acc_via_1[2] << "    " << acc_via_2[2] << "    " << acc_via_3[2] << "    " << acc_via_g[2] << "\n";
	outfile3 << acc_via_1[3] << "    " << acc_via_2[3] << "    " << acc_via_3[3] << "    " << acc_via_g[3] << "\n";

	outfile3.close();


	ofstream outfile4;
	outfile4.open("via_XY.txt");


	outfile4 << forward_POS[0]<< "    " <<tf_x1 << "    " << tf_y1 << "    " << tf_z1 << "    " << tf_x_goal << "\n";
	outfile4 << forward_POS[1]<< "    " <<tf_x2 << "    " << tf_y2 << "    " << tf_z2 << "    " << tf_y_goal << "\n";
	
	outfile4.close();


	ofstream outfile5;
	outfile5.open("time.txt");

	outfile5 << travel_time_in << endl;
	outfile5.close();
}

////////////////////////////////////////  MAIN  ////////////////////////////////
int main(int argc, char* argv[]) {

	JOINT q2 = { 90, 90, -200, 45 };
	printf("Keep this window in focus, and...\n");

	//char ch;
	//int c;
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
		double a, b, c;

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
	else if (menu_input == 5) {
	
		TracGeneration();

	}
	else if (menu_input == 6) {
		exit(0);
	}


	system("pause");
	cin.get();
	return 0;

}
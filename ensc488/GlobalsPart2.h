#ifndef Globals_h__
#define Globals_h__

#include <iostream>


const double L1 = 405.0;
const double L2 = 70.0;  
const double L3 = 195.0; //a2
const double L4 = 142.0; //a4
const double L5 = 410.0;
const double L6 = 80.0;
const double L7 = 60.0;
const double L8 = 30.0;

const double THETA1_MAX = 150.0f;
const double THETA1_MIN = -150.0f;


const double THETA2_MAX = 100.0f;
const double THETA2_MIN = -100.0f;

const double D3_MAX = -100.0f;
const double D3_MIN = -200.0f;

const double THETA4_MAX = 160.0f;
const double THETA4_MIN = -160.0f;


const double Vel_MAX = 150.0f;
const double Vel_MIN = -150.0f;

const double acc_MAX = 600.0f;
const double acc_MIN = -600.0f;

const double vel_D3_MAX = 50.0f;
const double vel_D3_MIN = -50.0f;

const double acc_D3_MAX = 200.0f;
const double acc_D3_MIN = -200.0f;


// Limit Check Functions //
bool Theta1Check(double ang)
{
  return ((ang > THETA1_MAX || ang < THETA1_MIN) ? false : true);
}

bool Theta2Check(double ang)
{
  return ((ang > THETA2_MAX || ang < THETA2_MIN) ? false : true);
}

bool Theta4Check(double ang)
{
  return ((ang > THETA4_MAX || ang < THETA4_MIN) ? false : true);
}

bool D3Check(double dist)
{
  return ((dist > D3_MAX || dist < D3_MIN) ? false : true);
}

bool Theta1Check2(double ang)
{
  return ((ang >= THETA1_MAX || ang <= THETA1_MIN) ? false : true);
}

bool Theta2Check2(double ang)
{
  return ((ang >= THETA2_MAX || ang <= THETA2_MIN) ? false : true);
}

bool Theta4Check2(double ang)
{
  return ((ang >= THETA4_MAX || ang <= THETA4_MIN) ? false : true);
}

bool D3Check2(double dist)
{
  return ((dist <= D3_MAX || dist >= D3_MIN) ? false : true);
}


bool VelCheck(double vel)
{
	return ((vel > Vel_MAX || vel < Vel_MIN) ? false : true);
}

bool AccCheck(double vel)
{
	return ((vel > acc_MAX || vel < acc_MIN) ? false : true);
}

bool vel_D3Check(double vel)
{
	return ((vel > vel_D3_MAX || vel < vel_D3_MIN) ? false : true);
}


bool acc_D3Check(double vel)
{
	return ((vel > acc_D3_MAX || vel < acc_D3_MIN) ? false : true);
}

#endif // Globals_h__
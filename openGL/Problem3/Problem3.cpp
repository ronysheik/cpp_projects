/* Rony Sheik
   301258738
   rsheik@sfu.ca */

#include<iostream>
#include<string>
#include <windows.h>
#include <vector>
#include <tuple>

// Function to get minimum value from an array 
int get_minimum(int arr[4])
{
	int min = arr[0];
	for (int i = 1; i < 4;i++)
	{
		if (arr[i] < min )
		{
			min = arr[i];
		}
	}
	return min;
}

// Function to get maximum value from an array 
int get_maximum(int arr[4])
{
	int max = arr[0];
	for (int i = 1; i < 4;i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	return max;
}

// Function to print 
void print_val(std::vector<int> &vec)
{
	for(int i=0;i< vec.size();i++)
		std::cout << " a"<<i+1<<":"<<vec.at(i) << std::endl;
}


// Function to calculate maximin value from 2D array or, decision matrix
std::tuple<std::vector<int>, int, int> get_maximin(int arr[4][4])
{

	int temp_arr[4];
	std::vector<int> store_min;

	for (int i = 0; i < 4;i++)
	{
		for (int j = 0; j < 4;j++)
		{
			temp_arr[j] = arr[i][j];
		}

		store_min.push_back(get_minimum(temp_arr));
	}

	int max = store_min.at(0);
	int result;
	for (int i = 1; i < store_min.size();i++)
	{
		if (store_min.at(i) > max)
		{
			max = store_min.at(i);
			result = i;
		}
	}
	return {store_min, max, result};
}


// Function to calculate maximax value from 2D array or, decision matrix
std::tuple<std::vector<int>, int, int> get_maximax(int arr[4][4])
{

	int temp_arr[4];
	std::vector<int> store_max;

	for (int i = 0; i < 4;i++)
	{
		for (int j = 0; j < 4;j++)
		{
			temp_arr[j] = arr[i][j];
		}
		store_max.push_back(get_maximum(temp_arr));
	}

	int max = store_max[0];
	int result;
	for (int i = 0; i < store_max.size();i++)
	{
		if (max < store_max[i])
		{
			max = store_max[i];
			result = i;
		}
	}

	return {store_max, max, result};
}

// Function to calculate minimax regret value from 2D array or, decision matrix
int get_minimax_regret(int arr[4][4])
{
	int temp_arr[4];
	std::vector<int> store_max;

	for (int i = 0; i < 4;i++)
	{
		for (int j = 0; j < 4;j++)
		{
			temp_arr[j] = arr[j][i];
		}
		store_max.push_back(get_maximum(temp_arr));
	}

	int regret_matrix[4][4];

	for (int i = 0; i < 4;i++)
	{
		for (int j = 0; j < 4;j++)
		{
			regret_matrix[j][i] = arr[j][i] - store_max[i];
		}
	}

	std::vector<int> myvec; int reg_value; int reg_result;
	std::tie(myvec, reg_value, reg_result) = get_maximin(regret_matrix);
	std::cout<<"\n";
	print_val(myvec);
	std::cout << " Max Value:" << reg_value << std::endl;

	return reg_result;
}

// Function to calculate optimisim pessimism value from 2D array or, decision matrix
int get_optimisim_pessimism(int arr[4][4])
{
	double alpha = 0.25;

	int temp_arr[4];
	std::vector<double> store_val;

	for (int i = 0; i < 4;i++)
	{
		for (int j = 0; j < 4;j++)
		{
			temp_arr[j] = arr[i][j];
		}
		double max = get_maximum(temp_arr);
		double min = get_minimum(temp_arr);
	    double formula = alpha * max + (1 - alpha) * min;
		store_val.push_back(formula);
	}

	double max = store_val[0];
	int result;
	std::cout << "\n";
	for (int i = 0; i < store_val.size();i++)
	{
		std::cout << " a" << i + 1 << ": " << store_val[i] << std::endl;
		if (max <= store_val[i])
		{
			max = store_val[i];
			result = i;
		}
	}
	std::cout << " Max value: " << max << std::endl;
	return result;
}

// Function to calculate principle of sufficient reason value from 2D array or, decision matrix
int get_principle_of_sufficient_reason(int arr[4][4])
{
	double temp_arr[4] = { 0.0, 0.0, 0.0, 0.0 };
	std::vector<double> store_val;
	double temp = 0;
	for (int i = 0; i < 4;i++)
	{
		for (int j = 0; j < 4;j++)
			temp_arr[j] =  arr[i][j];

		for (int k = 0;k < 4;k++)
			temp += 0.25 * temp_arr[k];
		store_val.push_back(temp);
		temp = 0;
	}

	double max = store_val[0];
	int result;
	std::cout << "\n Final matrix for principle of sufficient reason:" << std::endl;
	for (int i = 0; i < store_val.size();i++)
	{
		std::cout << " a" << i + 1 <<": "<< store_val[i] << std::endl;
		if (max <= store_val[i])
		{
			max = store_val[i];
			result = i;
		}
	}

	return result;
}

int main(int argc, char **argv)
{

	// given decision matrix
	int matrix_Of_acts[4][4] =
	{
		20, 20, 0, 10,
		10, 10, 10, 10,
		0, 40, 0, 0,
		10, 30, 0, 0
	};

	// output all the acts to the console 
	std::vector<int> myvec1; int maximin_value; int maximin_result;
	std::tie(myvec1, maximin_value, maximin_result) = get_maximin(matrix_Of_acts);
	print_val(myvec1);
	std::cout << " Max value: " << maximin_value << " \n So, the act has choosen based on maximin rule is:" << " a" << maximin_result + 1 <<std::endl;
	std::cout << "\n";

	std::vector<int> myvec2; int maximax_value; int maximax_result;
	std::tie(myvec2, maximax_value, maximax_result) = get_maximax(matrix_Of_acts);
	print_val(myvec2);
	std::cout << " Max value: " << maximax_value << "\n So, the act has choosen based on maximax rule is:" << " a" << maximax_result + 1 << std::endl;

	int minimax_regret_result = get_minimax_regret(matrix_Of_acts);
	std::cout << " So, the act has choosen based on minimax regret rule is:" << " a" << minimax_regret_result + 1 << std::endl;

	int optimisim_pessimism_result = get_optimisim_pessimism(matrix_Of_acts);
	std::cout << " So, the act has choosen based on optimisim pessimism rule is:" << " a" << optimisim_pessimism_result + 1 << std::endl;

	int principle_of_sufficient_reason_result = get_principle_of_sufficient_reason(matrix_Of_acts);
	std::cout << " So, the act has choosen based on principle of sufficient reason rule is:" << " a" << principle_of_sufficient_reason_result + 1 << std::endl;
	
	std::cin.get();
	return 0;


}


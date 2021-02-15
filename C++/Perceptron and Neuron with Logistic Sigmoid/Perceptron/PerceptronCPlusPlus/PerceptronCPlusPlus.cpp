// PerceptronCPlusPlus.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <math.h>

#pragma comment(lib, "Winmm.lib")

using namespace std;

// Random number with Gaussian Distribution
static void RandomWeight(double minimumValue, double maximumValue, double weight[][2])
{
	//srand(timeGetTime());
	for (int ROW = 0; ROW < 4; ROW++)
	{
		for (int i = 0; i < 2; i++)
		{
			double random = (double)rand()/(RAND_MAX+1.0);
			weight[ROW][i] = minimumValue + (maximumValue-minimumValue)*random;
		}
	}
}
static int Activation(double netSum)
{
	if (netSum > 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int SimulatePerceptron(int inputSize, const int input[][2], const double weight[][2], int inputRow)
{
	double netSum = 0;
	for (int i = 0; i < inputSize; i++)
	{
		netSum += input[inputRow][i] * weight[inputRow][i];
	}
	return Activation(netSum);
}

void Training(int output, double weight[][2], const int input[][2], int inputSize, double learningRate,
			  int target[])
{
	double J = 5;
	int result = -3;
	double quitCondition = pow(10.0,-5);
	int innerCounter = 0;
	int outerCounter = 0;

	while (J>quitCondition)
	{
		for (int i = 0; i < 4; i++) // for each sample
		{
			result = SimulatePerceptron(inputSize, input, weight, i); // simulate the perceptron
			J = 0.5*((target[i] - result)*(target[i] - result));
			if (result != target[i]) // If the result is invalid
			{
				for (int j = 0; j < inputSize; j++) // for all inputs j on that row
				{
					double delta = target[i] - result;
					weight[i][j] += learningRate * delta * input[i][j];
				}
			}
			innerCounter++;
		}
		outerCounter++;
		std::cout << "Training took " << innerCounter*outerCounter << " iterations" << '\n';
	}
}

int main()
{
	int input[4][2] =    {{0, 1},
							{1, 0},
							{0, 0},
							{1, 1}};
	int target[] = {0,0,0,1}; // must match input
	double weight[4][2];
	int output = 0;
	int inputSize = 2;
	double learningRate = 0.01;

	RandomWeight(0.0, 1.0, weight); // initialise the weights

	Training(output, weight, input, inputSize, learningRate, target); // train all inputs

	output = SimulatePerceptron(inputSize, input, weight, 0);
	cout << "Output should be: " << target[0] << " and is: " << output << '\n';
	output = SimulatePerceptron(inputSize, input, weight, 1);
	cout << "Output should be: " << target[1] << " and is: " << output << '\n';
	output = SimulatePerceptron(inputSize, input, weight, 2);
	cout << "Output should be: " << target[2] << " and is: " << output << '\n';
	output = SimulatePerceptron(inputSize, input, weight, 3);
	cout << "Output should be: " << target[3] << " and is: " << output;

	cin.get();

	return 0; // exit
}
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <Windows.h>
#include <time.h>
#include <math.h>

using namespace std;

#pragma comment(lib, "Winmm.lib")

// Random number with Gaussian Distribution
inline static void RandomWeight(double minimumValue, double maximumValue, double weight[],
								int numberOfInputs)
{
	//srand(timeGetTime());
	for (int i = 0; i < numberOfInputs; i++)
	{
		double random = (double)rand()/(RAND_MAX+1.0);
		weight[i] = minimumValue + (maximumValue-minimumValue)*random;
	}
}

inline static double Activation(double netSum)
{
	return 1.0 / (1.0 + exp(-netSum));
}


double SimulatePerceptron(int inputSize, const double input[], const double weight[], int inputRow)
{
	double netSum = 0;
	netSum += input[inputRow] * weight[inputRow];
	return Activation(netSum);
}

/*
output = output of the first simulation
weight = the weights of sample, e.g. weights of [0]
input = all of the inputs
inputsize = number of items per row, e.g. 1
target = all the targets of all the inputs
numberOfInputs = all of the inputs, e.g. 3500

*/
inline void Training(double output, double weight[], const double input[], int inputSize, double learningRate,
			  double target[], int numberOfInputs)
{
	double J = 5;
	double result;
	double quitCondition = pow(10.0,-1);
	int innerCounter = 0;
	int outerCounter = 0;

	while (J>quitCondition)
	{
		for (int i = 0; i < numberOfInputs-inputSize; i++) // for each sample
		{
			result = SimulatePerceptron(inputSize, input, weight, i); // simulate the perceptron
			J = 0.5*((target[i] - result)*(target[i] - result)); // Error function
			//cout << J << '\n';
			
			double delta = target[i] - result;
			weight[i] += learningRate * delta * input[i];

			i++; // Move to the next sample
			innerCounter++; // Counter for the number of iterations taken
		}
		outerCounter++;
	}
	std::cout << "Training took " << innerCounter*outerCounter << " iterations" << "\n";
}

template<typename T>     
T from_string(const string& MyString)  
{  
	stringstream SStream(MyString);  
	T Num = 0;  
	SStream >> Num;  
	return Num;  
} 

inline void LoadInputData(double input[], double target[], short numberOfInputs,
						  int numberOfTargets) // Load the input data
{
	string dataFromFile[3501]; // number of lines to read in, read them all in
	fstream loadFile;
	loadFile.open("input.txt", ios::in);
	double temp[3501];
	int counter = 1;
	if (loadFile.is_open())
	{
		for (int i = 0; i < numberOfInputs; i++) // Load the whole text file into a temp variable
		{
			loadFile>>dataFromFile[i];
			temp[i] = from_string<double>(dataFromFile[i]);
		}
		loadFile.close(); // Don't need the file open anymore so close it

		// Now setup the inputs and targets
		for (int i = 0; i < numberOfInputs - 1; i++) // numberOfInputs - 1 because of inputs per row (1)
		{
			input[i] = temp[i];
			target[i] = temp[i+1]; // e.g. target[0] = input[1]
		}
	}
	// TODO:
	// Add error handling code incase it can't open the file
}
    
template <typename T>
std::string to_string(const T& t) // const T& t
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

inline void WriteFile(double target[])
{
	string dataToFile[3500]; // number of lines to write out, 3499 targets
	fstream writeFile;
	writeFile.open("target.txt", ios::out);
	if (writeFile.is_open()) // opened it successfully now write to it
	{
		for (int i = 0; i < 3500; i++)
		{
			if (i!=3499) // for formatting, don't want to write a new line after the last input
			{
				writeFile << to_string(target[i])+"\n";
			}
			else
			{
				writeFile << to_string(target[i]);
			}
		}
		writeFile.close();
	}
	// TODO:
	// Add error handling code incase it can't open the file
}

inline void WriteFileAfterTraining(double const target[])
{
	string dataToFile[3497]; // number of lines to write out, 3499 targets
	fstream writeFile;
	writeFile.open("targetsAfterTraining.txt", ios::out);
	if (writeFile.is_open()) // opened it successfully now write to it
	{
		for (int i = 0; i < 3497; i++)
		{
			if (i!=3496) // for formatting, don't want to write a new line after the last input
			{
				writeFile << to_string(target[i])+"\n";
			}
			else
			{
				writeFile << to_string(target[i]);
			}
		}
		writeFile.close();
	}
	// TODO:
	// Add error handling code incase it can't open the file
}

int main()
{
	const int numberOfInputs = 3501;
	const int inputSize = 1; // number of inputs per row
	const int numberOfTargets = numberOfInputs - inputSize; // numberOfTargets is numberOfInputs - 
										// number of inputs per row

	double input[numberOfInputs]; // [ROW][COL] - Don't train the 3501 line because 3501 does not have a target
							// but input from line 3499 and 3500 have a target (target been 3501)
	double target[numberOfTargets];
	double weight[numberOfInputs];
	double output;
	double learningRate = 0.01;

	// Initialise the input and target data
	LoadInputData(input, target, 3501, 3501);
	WriteFile(target);

	RandomWeight(0.0, 1.0, weight, numberOfInputs); // initialise the weights
	output = SimulatePerceptron(inputSize, input, weight, 0);
	Training(output, weight, input, inputSize, learningRate, target, numberOfInputs); // train all inputs

	WriteFileAfterTraining(target);

	cout << "Training Complete" << "\n";

	output = SimulatePerceptron(inputSize, input, weight, 3);
	cout << "Output of sample should be: " << target[3] << " and is: " << output << "\n"
		<< "Accuracy is: " << abs(output - target[3]) << "\n" << "\n";

	output = SimulatePerceptron(inputSize, input, weight, 4);
	cout << "Output of sample should be: " << target[4] << " and is: " << output << "\n"
		<< "Accuracy is: " << abs(output - target[4]) << "\n" << "\n";

	output = SimulatePerceptron(inputSize, input, weight, 1749);
	cout << "Output of sample should be: " << target[1749] << " and is: " << output << "\n"
		<< "Accuracy is: " << abs(output - target[1749]) << "\n" << "\n";

	output = SimulatePerceptron(inputSize, input, weight, 3499);
	cout << "Output of sample should be: " << target[3499] << " and is: " << output << "\n"
		<< "Accuracy is: " << abs(output - target[3499]);

	cin.get();

	return 0; // exit
}
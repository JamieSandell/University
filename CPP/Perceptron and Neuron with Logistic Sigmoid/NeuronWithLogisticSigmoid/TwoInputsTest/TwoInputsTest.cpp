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

const static int inputSize = 2; // number of inputs per row

// Random number with Gaussian Distribution
inline static void RandomWeight(double minimumValue, double maximumValue, double weight[][2],
								int numberOfInputs)
{
	//srand(timeGetTime());
	for (int i = 0; i < numberOfInputs; i++)
	{
		for (int j = 0; j < inputSize; j++)
		{
			double random = (double)rand()/(RAND_MAX+1.0);
			weight[i][j] = minimumValue + (maximumValue-minimumValue)*random;
		}
	}
}

inline static double Activation(double netSum)
{
	return 1.0 / (1.0 + exp(-netSum));
}


double SimulatePerceptron(int inputSize, const double input[][2], const double weight[][2], int inputRow)
{
	double netSum = 0;
	for (int i = 0; i < inputSize; i++)
	{
		netSum += input[inputRow][i] * weight[inputRow][i];
	}
	return Activation(netSum);
}

/*
output = output of the first simulation
weight = the weights of sample, e.g. weights of [0][0]
input = all of the inputs
inputsize = number of items per row, e.g. 2
target = all the targets of all the inputs
numberOfInputs = all of the inputs, e.g. 3501

*/
inline void Training(double output, double weight[][inputSize], const double input[][2], int inputSize, double learningRate,
			  double target[], int numberOfInputs)
{
	double J = 5;
	double result;
	double quitCondition = pow(10.0,-5);
	int count = 0;
	int innerLoop = 0;
	int outerLoop = 0;

	while (J>quitCondition)
	{
		for (int i = 0; i < numberOfInputs-inputSize; i++) // for each sample
		{
			result = SimulatePerceptron(inputSize, input, weight, i); // simulate the perceptron
			J = 0.5*((target[i] - result)*(target[i] - result)); // Error function
			
			for (int j = 0; j < inputSize; j++) // for all inputs  (all the inputs on that row)
			{
				double delta = target[i] - result;
				weight[i][j] += learningRate * delta * input[i][j]; //[Row][Col], update
				// weights
			}

			i++; // Move to the next sample
			innerLoop++; // Counter for the number of iterations taken
		}
		outerLoop++;
	}
	std::cout << "Training took " << outerLoop*innerLoop << " iterations" << '\n';
}

template<typename T>     
T from_string(const string& MyString)  
{  
	stringstream SStream(MyString);  
	T Num = 0;  
	SStream >> Num;  
	return Num;  
} 

inline void LoadInputData(double input[][2], double target[], short numberOfInputs,
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
		for (int i = 0; i < numberOfInputs - 2; i++) // numberOfInputs - 2 because of the algorithm
														// below
		{
			input[i][0] = temp[i]; // i row, first column
			input[i][1] = temp[i+1]; // i row, 2nd column
			target[i] = temp[i+2]; // e.g. target[0] = input[1][0]
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
	string dataToFile[3499]; // number of lines to write out, 3499 targets
	fstream writeFile;
	writeFile.open("target.txt", ios::out);
	if (writeFile.is_open()) // opened it successfully now write to it
	{
		for (int i = 0; i < 3499; i++)
		{
			if (i!=3498) // for formatting, don't want to write a new line after the last input
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
	const int numberOfTargets = numberOfInputs - inputSize;

	double input[numberOfInputs][2]; // [ROW][COL] - Don't train the 3501 line because 3501 does not have a target
							// but input from line 3499 and 3500 have a target (target been 3501)
	double target[numberOfTargets]; // the first two entries are not targets but the 3rd one onwards are
							// 'sliding window', so total lines = 3501 read in, but 3501 - 2 = 3499
							// ==  actual number of targets
	double weight[numberOfInputs][inputSize]; // TODO: This needs looking at, because when the input is been carried over
							// the weight isn't carried over with the input, the weight needs to be
								// 'attached' to the input
	double output;
	double learningRate = 0.01;

	// Initialise the input and target data
	LoadInputData(input, target, 3501, 3501);
	WriteFile(target);

	RandomWeight(0.0, 1.0, weight, numberOfInputs); // initialise the weights
	output = SimulatePerceptron(inputSize, input, weight, 0);
	Training(output, weight, input, inputSize, learningRate, target, numberOfInputs); // train all inputs

	output = SimulatePerceptron(inputSize, input, weight, 0);
	output = SimulatePerceptron(inputSize, input, weight, 1);
	output = SimulatePerceptron(inputSize, input, weight, 1749);
	output = SimulatePerceptron(inputSize, input, weight, 3498); // 3498 = 3499 in the input file,
																	// and is the last one to have
																	// a target

	cout << "Training Complete" << "\n";

	output = SimulatePerceptron(inputSize, input, weight, 0);
	cout << "Output of sample should be: " << target[2] << " and is: " << output << "\n"
		<< "Accuracy is: " << abs(output - target[2]) << "\n" << "\n";

	output = SimulatePerceptron(inputSize, input, weight, 1);
	cout << "Output of sample should be: " << target[3] << " and is: " << output << "\n"
		<< "Accuracy is: " << abs(output - target[3]) << "\n" << "\n";

	output = SimulatePerceptron(inputSize, input, weight, 1749);
	cout << "Output of sample should be: " << target[1751] << " and is: " << output << "\n"
		<< "Accuracy is: " << abs(output - target[1751]) << "\n" << "\n";

	output = SimulatePerceptron(inputSize, input, weight, 3498); // 3498 = 3499 in the input file,
	// and is the last one to have
	// a target
	cout << "Output of sample should be: " << target[3498] << " and is: " << output << "\n"
		<< "Accuracy is: " << abs(output - target[3498]);

	cin.get();

	return 0; // exit
}
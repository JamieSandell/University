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


double SimulatePerceptron(int inputSize, const double input[][3], const double weight[], int inputRow)
{
	double netSum = 0;
	for (int i = 0; i < inputSize; i++)
	{
		netSum += input[inputRow][i] * weight[inputRow+i];
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
inline void Training(double output, double weight[], const double input[][3], int inputSize, double learningRate,
			  double target[], int numberOfInputs)
{
	double J = 5;
	double result;
	double quitCondition = pow(10.0,-5);
	int count = 0;
	int innerCounter = 0;
	int outerCounter = 0;

	while (J>quitCondition)
	{
		for (int i = 0; i < numberOfInputs-inputSize; i++) // for each sample
		{
			result = SimulatePerceptron(inputSize, input, weight, i); // simulate the perceptron
			J = 0.5*((target[i] - result)*(target[i] - result)); // Error function
			//cout << J << '\n';
			
			for (int j = 0; j < inputSize; j++) // for all inputs j
			{
				double delta = target[i] - result;
				weight[i+j] += learningRate * delta * input[i][j]; //[Row][Col], update
				// weights
			}

			i++; // Move to the next sample
			innerCounter++; // Counter for the number of iterations taken
		}
		outerCounter++;
	}
	std::cout << "Training took " << innerCounter*outerCounter << " iterations";
}

template<typename T>     
T from_string(const string& MyString)  
{  
	stringstream SStream(MyString);  
	T Num = 0;  
	SStream >> Num;  
	return Num;  
} 

inline void LoadInputData(double input[][3], double target[], short numberOfInputs,
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
		for (int i = 0; i < numberOfInputs - 3; i++) // numberOfInputs - 3 because of the algorithm
														// below
		{
			input[i][0] = temp[i]; // i row, first column
			input[i][1] = temp[i+1]; // i row, 2nd column
			input[i][2] = temp[i+2]; // i row, 3rd column
			target[i] = temp[i+3]; // target[0] = input[3][0]
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
	string dataToFile[3498]; // number of lines to write out, 3499 targets
	fstream writeFile;
	writeFile.open("target.txt", ios::out);
	if (writeFile.is_open()) // opened it successfully now write to it
	{
		for (int i = 0; i < 3498; i++)
		{
			if (i!=3497) // for formatting, don't want to write a new line after the last input
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
	const int inputSize = 3; // number of inputs per row
	const int numberOfTargets = numberOfInputs - inputSize; // numberOfTargets is numberOfInputs - 
										// number of inputs per row

	double input[numberOfInputs][3]; // [ROW][COL] - Don't train the 3501 line because 3501 does not have a target
							// but input from line 3499 and 3500 have a target (target been 3501)
	double target[numberOfTargets]; // the first two entries are not targets but the 3rd one onwards are
							// 'sliding window', so total lines = 3501 read in, but 3501 - 2 = 3499
							// ==  actual number of targets
	double weight[numberOfInputs]; // TODO: This needs looking at, because when the input is been carried over
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

	WriteFileAfterTraining(target);

	cout << "Training Complete" << "\n";

	output = SimulatePerceptron(inputSize, input, weight, 1);
	cout << "Output of sample should be: " << target[1] << " and is: " << output << "\n"
		<< "Accuracy is: " << abs(output - target[1]) << "\n" << "\n";

	output = SimulatePerceptron(inputSize, input, weight, 2);
	cout << "Output of sample should be: " << target[2] << " and is: " << output << "\n"
		<< "Accuracy is: " << abs(output - target[2]) << "\n" << "\n";

	output = SimulatePerceptron(inputSize, input, weight, 1747);
	cout << "Output of sample should be: " << target[1747] << " and is: " << output << "\n"
		<< "Accuracy is: " << abs(output - target[1747]) << "\n" << "\n";

	output = SimulatePerceptron(inputSize, input, weight, 3497);
	cout << "Output of sample should be: " << target[3497] << " and is: " << output << "\n"
		<< "Accuracy is: " << abs(output - target[3497]);

	cin.get();

	return 0; // exit
}
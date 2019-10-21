#include <iostream>
#include "Q6.h"

int recurrence(int a, int b, int k, int u0, int u1)
{
	//The value of u0 - set on a variable to allow for easier using
	int value = u0;
	//This is the variable that will store the data 
	int answer;
	//This is a storage - just to allow a simple bubble sort
	int uStore;

	//Here is a loop - to allow the recurrence to run
	for (int i = 0; i <= k; i++)
	{
		//This if statment will run as long as i does not = 0
		if (i != 0)
		{
			//This is the sum but slightly adjusted "u0 =pUn + q
			answer = a * u1 + b * value;
			//This is to sort and give the correct answer for the output
			uStore = value;
			value = answer;
		}
	}
	return value;
}


void LFSR(int k, vector<int> &u)
{
	//This is the current place in the vector
	int uCurrent;
	//This is for increasing the location
	int uAdded;
	//The answer
	int answer;
	if (k > 4)
	{
		for (int i = 0; i <= k; i++)
		{
			//Sets the current location
			uCurrent = u[i];
			//Here adds the postions to allow for the continuation and displaying
			uAdded = u[i + 2];
			//This does the division by two - and should give the output that is for that section
			answer = (uCurrent + uAdded) % 2;
			//Pushes the answer back to the vector
			u.push_back(answer);
		}
	}
}
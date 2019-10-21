#include <iostream>
#include "Q6.h"

using namespace std;

int main()
{
	//Declaring all my variables
	int show;
	int a = 6;
	int b = 1;
	int k = 0;
	//This just defines what the recurence is
	show = recurrence(a, b, k, 3, 5);


	//This will go through and show out my answer for part a
	cout << "Question 6: " << endl << "Part A = ";
	cout << show << endl;
	cout << endl;

	cout << "Part A-2 = " << endl;

	//Re-setting the Values as to suit the current question
	a = 16;
	b = 11;
	k = 5;
	//This sets the recurence
	show = recurrence(a, b, k, 1, 2);
	cout << show << endl << endl;

	//Defines my vector and the name for it
	vector<int> outPut;

	//sets K
	k = 50;

	//This adds the first 5 terms to my vector
	outPut.push_back(0);
	outPut.push_back(1);
	outPut.push_back(1);
	outPut.push_back(0);
	outPut.push_back(1);

	//Calls the LFSR function
	LFSR(k, outPut);

	cout << "Question 6 - Part B" << endl;
	//This is a for loop - to output each place in the vector after it has been calculated
	for (int i = 0; i < k; i++)
	{
		cout << outPut[i] << " ";
		if (i == 30)
		{
			cout << endl;
		}
	}
	cout << endl;
	//Just outputs how many times the code repeats itself
	system("pause");
}
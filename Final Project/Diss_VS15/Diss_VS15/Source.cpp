//Random number generator given by Ian Wilson (dissertation supervisor)
//Said during meeting was allowed. Sent over by supervisor

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <Windows.h>
#include "RandomNumber.h"

using namespace std;
enum state { Happyc, Sadc, Hungryc, Tiredc, Passivec, Asleepc, Fullc, Thirstc, Boredc, Trickc };
state usedState = Passivec;
state prevState = Passivec;
int waterLevel = 100;
int foodLevel = 100;
int learnCount = 0;
int fileCount = 0;
int filelines = 0;
int infile = 0;
int trickLearningH = 0;
int trickLearningHA = 0;
class StateContext;
RandomNumber rnd;


//This class is used to create the different states and for them to be used
//Inside this class, the states are created and a pointer is set to call between states
class State
{
protected:
	StateContext* CurrentContext;
public:
	State(StateContext* Context)
	{
		CurrentContext = Context;
	}
	virtual ~State(void) {}
	virtual void transition(void) {}
};

//Class is used to check between the states and allows for state transitions to be completed
class StateContext
{
protected:
	int stateIndex = 0;
	vector<State*> availableStates;
	vector<int> statePatameters;

public:
	State * CurrentState = nullptr;
	virtual ~StateContext(void);
	virtual void setState(state newState);
	virtual int getStateIndex(void);
	//virtual int setStateParam(statePatameter SP, int value);
	//virtual int getStateParam(stateParameter SP);
};

//Checks for all the states inside the project
StateContext::~StateContext(void)
{
	for (int i = 0; i < this->availableStates.size(); i++) delete this->availableStates[i];
	this->availableStates.clear();
	this->statePatameters.clear();
}

void StateContext::setState(state newState)
{
	this->CurrentState = availableStates[newState];
	this->stateIndex = newState;
	this->CurrentState->transition();
}

int StateContext::getStateIndex(void)
{
	return this->stateIndex;
}

//void StateContext::setStateParam(stateParameter SP, int value)
//{
//	this->statePatameters[SP] = value;
//}
//
//void StateContext::getStateParam(stateParameter SP)
//{
//	return this->statePatameters[SP];
//}

class Transition
{
public:
	virtual int chanceOfChange(int) { return 0; };
	virtual bool Wandering(void) { return true; };
	virtual bool Playing(void) { return true; };
	virtual bool UnHappy(void) { return true; };
	virtual bool Eating(void) { return true; };
	virtual bool full(void) { return true; };
	virtual bool tired(void) { return true; };
	virtual bool Sleeping(void) { return true; };
	virtual bool Drinking(void) { return true; };
	virtual bool Boredom(void) { return true; };
	virtual bool DoTrick(void) { return true; };
};

//class animalAI
//{
//protected:
//	string behaviour;
//public:
//	virtual string behaviour(void);
//};
//
//string animalAI::behaviour(void)
//{
//	return this->behaviour;
//}
//
//class Mood : public animalAI
//{
//
//};

//This is the main class for the AI. It is what all the other states for the AI will inherit from.
class AnimalState : public State, public Transition
{
public:
	AnimalState(StateContext* Context) : State(Context) {}
};

//First AI state
class Passive : public AnimalState
{
public:
	Passive(StateContext* Context) : AnimalState(Context) {}

	virtual bool Wandering(void);
};

//State will have changes for; thirst, hunger, no change, bored, tired, happy, sad
//Will need random number generator
//Water and food will not use the number generator
//State will need to change, using the pointers and the set states
//Didn't work originally with the main - added variable that changes also for states
bool Passive::Wandering(void)
{

	rnd.initialiseSeed();
	int probChange = rnd.random(0, 11);
	cout << "The animal is wandering" << endl;
	Sleep(3000);
	if (waterLevel <= 25)
	{
		cout << "The animal is thirsty" << endl;
		this->CurrentContext->setState(Thirstc);
		usedState = Thirstc;
	}
	else if (foodLevel <= 30)
	{
		cout << "The animal is hungry" << endl;
		this->CurrentContext->setState(Hungryc);
		usedState = Hungryc;

	}
	else if (probChange >= 1 && probChange <= 4)
	{
		cout << "The animal is still wandering" << endl;
		//Need to figure out staying in the same state
	}
	else if (probChange >= 5 && probChange <= 7)
	{
		cout << "The animal perks up" << endl;
		this->CurrentContext->setState(Happyc);
		usedState = Happyc;
	}
	else if (probChange == 8)
	{
		cout << "The animal is getting tired" << endl;
		this->CurrentContext->setState(Tiredc);
		usedState = Tiredc;
	}
	else if (probChange == 9)
	{
		cout << "The animal looks a little down" << endl;
		this->CurrentContext->setState(Sadc);
		usedState = Sadc;
	}
	else if (probChange >= 10 && probChange <= 11)
	{
		cout << "The animal is bored" << endl;
		this->CurrentContext->setState(Boredc);
		usedState = Boredc;
	}
	return true;
}

class Happy : public AnimalState
{
public:
	Happy(StateContext* Context) : AnimalState(Context) {}

	virtual bool Playing(void);
};

//State for happy will need random number
//State changes - no change, tricks (added later) tired, hungry (none food based)
bool Happy::Playing(void)
{
	rnd.initialiseSeed();
	int probChange = rnd.random(0, 10);
	cout << "The animal is playing" << endl;
	Sleep(3000);
	if (probChange >= 1 && probChange <= 2)
	{
		cout << "The animal continues to play" << endl;
		//Need to figure out staying in the same state
	}
	else if (probChange >= 3 && probChange <= 5)
	{
		cout << "The animal wants to try tricks" << endl;
		this->CurrentContext->setState(Trickc);
		usedState = Trickc;
		prevState = Happyc;
	}
	else if (probChange >= 6 && probChange >= 8)
	{
		cout << "The animal becomes tired" << endl;
		this->CurrentContext->setState(Tiredc);
		usedState = Tiredc;
	}
	else if (probChange >= 9 && probChange <= 10)
	{
		cout << "The animal is hungry" << endl;
		this->CurrentContext->setState(Hungryc);
		usedState = Hungryc;
	}
	return true;
}


class Sad : public AnimalState
{
public:
	Sad(StateContext* Context) : AnimalState(Context) {}

	virtual bool UnHappy(void);
};
//State for sad
//Random number needed
//No change, Passive, hungry (using random)
bool Sad::UnHappy(void)
{
	rnd.initialiseSeed();
	int probChange = rnd.random(0, 10);
	cout << "The animal is sad" << endl;
	Sleep(3000);
	if (probChange >= 1 && probChange <= 7)
	{
		cout << "The animal does not cheer up" << endl;
		//Need to figure out staying in the same state
	}
	else if (probChange >= 8 && probChange <= 9)
	{
		cout << "The animal relaxes" << endl;
		this->CurrentContext->setState(Passivec);
		usedState = Passivec;
	}
	else if (probChange == 10)
	{
		cout << "The animal becomes hungry" << endl;
		this->CurrentContext->setState(Hungryc);
		usedState = Hungryc;
	}
	return true;
}

class Hungry : public AnimalState
{
public:
	Hungry(StateContext* Context) : AnimalState(Context) {}

	virtual bool Eating(void);
};
//Eating state
//random needed
//Setters for the food level
//changes from states will need more than just numbers
//Can change based on the last state (stop long loops) for both full and tired
//can change based on the food level - for tired
//can use both to change - for full
//default cahnge
bool Hungry::Eating(void)
{
	rnd.initialiseSeed();
	int probChange = rnd.random(0, 10);
	cout << "The animal is eating" << endl;
	if (foodLevel <= 100)
	{
		foodLevel = 100;
	}
	else if (foodLevel >= 90)
	{
		foodLevel += 20;
	}
	Sleep(3000);
	if (probChange >= 1 && probChange <= 6 && foodLevel <= 100 && prevState != Asleepc)
	{
		cout << "The animal is now full" << endl;
		foodLevel = 100;
		this->CurrentContext->setState(Fullc);
		usedState = Fullc;
		prevState = Hungryc;
	}
	else if (probChange >= 7 && probChange <= 8 && prevState != Asleepc)
	{
		cout << "The animal becomes tired" << endl;
		this->CurrentContext->setState(Tiredc);
		usedState = Tiredc;
		prevState = Hungryc;
	}
	else if (probChange >= 1 && probChange <= 10)
	{
		cout << "The animal relaxes" << endl;
		this->CurrentContext->setState(Passivec);
		usedState = Passivec;
		prevState = Hungryc;
	}
	return true;
}

class Full : public AnimalState
{
public:
	Full(StateContext* Context) : AnimalState(Context) {}

	virtual bool full(void);
};

//Simple state. only one tranisiton
bool Full::full(void)
{

	cout << "The animal is full, and is now becoming tired" << endl;
	Sleep(3000);
	this->CurrentContext->setState(Tiredc);
	usedState = Tiredc;
	return 0;
}

class Tired : public AnimalState
{
public:
	Tired(StateContext* Context) : AnimalState(Context) {}

	virtual bool tired(void);
};

//simple state. only one transition
bool Tired::tired(void)
{
	cout << "The animal is falling asleep" << endl;
	Sleep(3000);
	this->CurrentContext->setState(Asleepc);
	usedState = Asleepc;
	return 0;
}

class Asleep : public AnimalState
{
public:
	Asleep(StateContext* Context) : AnimalState(Context) {}

	virtual bool Sleeping(void);

};
//state for sleeping
//random number needed
//all changes based on random
//hungry, tired, passive, bored - changes 
bool Asleep::Sleeping(void)
{
	rnd.initialiseSeed();
	int probChange = rnd.random(0, 10);
	cout << "The animal is currently sleeping" << endl;
	Sleep(3000);
	if (probChange >= 1 && probChange <= 5)
	{
		cout << "The animal is awake and now. The animal is now Hungry" << endl;
		this->CurrentContext->setState(Hungryc);
		usedState = Hungryc;
		prevState = Asleepc;
	}
	else if (probChange >= 6 && probChange <= 7)
	{
		cout << "The animal is awake and now. The animal is still tired" << endl;
		this->CurrentContext->setState(Tiredc);
		usedState = Tiredc;
		prevState = Asleepc;
	}
	else if (probChange >= 8 && probChange <= 9)
	{
		cout << "The animal is awake and now. The animal relaxes" << endl;
		this->CurrentContext->setState(Passivec);
		usedState = Passivec;
	}
	else if (probChange == 10)
	{
		cout << "The animal is awake. However the animal is bored" << endl;
		this->CurrentContext->setState(Boredc);
		usedState = Boredc;
	}
	return true;

}
//State for drinking
//one change
//adjusting for the levels of water
class Thirsty : public AnimalState
{
public:
	Thirsty(StateContext* Context) : AnimalState(Context) {}

	virtual bool Drinking(void);
};
bool Thirsty::Drinking(void)
{
	cout << "The animal has druken" << endl;
	Sleep(3000);
	this->CurrentContext->setState(Passivec);
	if (waterLevel <= 15)
	{
		waterLevel = 100;
	}
	else
	{
		waterLevel += 20;
	}
	usedState = Passivec;
	return true;
}
class Bored : public AnimalState
{
public:
	Bored(StateContext* Context) : AnimalState(Context) {}

	virtual bool Boredom(void);
};
// bored state
//needs random number
//no change, hungry, tired, passive - changes.
bool Bored::Boredom(void)
{
	rnd.initialiseSeed();
	int probChange = rnd.random(0, 10);
	cout << "The animal is bored" << endl;
	Sleep(3000);
	if (probChange <= 1 && probChange <= 6)
	{
		cout << "The animal is still bored" << endl;
	}
	else if (probChange <= 7 && probChange <= 8)
	{
		cout << "The animal is hungry from boredom" << endl;
		this->CurrentContext->setState(Hungryc);
		usedState = Hungryc;
	}
	else if (probChange == 9)
	{
		cout << "The animal is going to try and sleep" << endl;
		this->CurrentContext->setState(Tiredc);
		usedState = Tiredc;
	}
	else if (probChange == 10)
	{
		cout << "The animal is going to walk around" << endl;
		this->CurrentContext->setState(Passivec);
		usedState = Passivec;
	}
	return true;
}

class Tricks : public AnimalState
{
public:
	Tricks(StateContext* Context) : AnimalState(Context) {}

	virtual bool DoTrick(void);

};
//trick state
//random number needed
//uses machine learning
bool Tricks::DoTrick(void)
{
	rnd.initialiseSeed();
	int trickLearning = rnd.random(1, 30);

	//Local variables needed for this part only
	string trickLearnt;
	string trickAttempt;
	string learning;
	string learnt;

	//cout << trickLearning << endl;
	
	//creates the text file for use here
	ofstream animalTricks("Animal_Tricks.txt", ios::app);
	ofstream animalTricksLearnt("Animal_Tricks_Learnt.txt", ios::app);

	//Section used for outputting a trick that is learned
	//will check the amount of lines in the open file
	//compares the list of lines in the open file to a random number
	//outputs the word on the same line as random number in a pre-set string
	//tells the user what trick thats learnt is being output
	//will close the file after
	//goes back to the passive state
	if (prevState != Trickc && trickLearning <= 10)
	{
		cout << "The animal is going to do a trick for you" << endl;
		Sleep(3000);
		if (animalTricksLearnt.is_open())
		{
			ifstream trickLearnt("Animal_Tricks_Learnt.txt");
			while (getline(trickLearnt, learnt))
			{
				filelines++;
				
 			}
			trickLearnt.close();
			int trickLine = rnd.random(1, filelines);
			ifstream trickLearnt2("Animal_Tricks_Learnt.txt");
			while (getline(trickLearnt2, learnt))
			{
				infile++;
				if (infile == trickLine)
				{
					cout << "The animal does a " << learnt << endl;
					filelines = 0;
					infile = 0;
					trickLearnt2.close();
					Sleep(3000);
				}
			}


			this->CurrentContext->setState(Passivec);
			usedState = Passivec;
			return true;
		}
	}
	//section for teaching new tricks
	//will require machine learning
	//uses case based reasoning
	//asks for an input from user for the trick being taught
	//checks the line on each file
	//works out half the random number taken from start
	//adds a count that works out how many time the trick being taught is inside the file
	//at half the random number - outputs a line to let the user know that stuff is happening and the animal is trying
	//when the amount of numbers inside the file is the same as the random number
	//adds the word to a file based for the learnt tricks whihc can be accessed in the before section
	//closes the file and changes state to passive
	//will require lots of validation and checks to make sure file lines dont get re-read 
	//validation for words inside file and locations
	if (animalTricks.is_open())
	{
		cout << "The animal wants to learn a trick" << endl;
		Sleep(3000);
		cout << "What trick are you going to teach" << endl;
		cout << "Enter trick" << endl;

		cin >> trickAttempt;

		//animalTricks << "TEST WRITING" << "\n" << endl;
		animalTricks << "\n" << trickAttempt;
		animalTricks.close();
		if (prevState != Trickc)
		{
			learnCount = trickLearning;
		}
		//cout << learnCount << endl;
		ifstream loopFile("Animal_Tricks.txt");
		fileCount = 0;
		while (getline(loopFile, learning))
		{
			
			//cout << learning << endl;
			//File count increases if there are other words in the file already. it will not increase correctly
			//Need to move the filecount to a new area so it only increases once per word
			//may need validation
			if (learning == trickAttempt)
			{
				fileCount++;
				//Validation used for making sure the number is divisble
				trickLearningH = learnCount % 2;	 
				if (trickLearningH == 1)
				{
					learnCount += 1;
					trickLearningH = 0;
				}
				trickLearningHA = (learnCount / 2);			
				//Checking the file, this allows for the correct lines to be used and made sure it does not repeat.
				if (fileCount == trickLearningHA && loopFile.eof())	
				{
					cout << "The animal attemps:" << trickAttempt << ".\t However does not manage it." << endl;
				}
				if (fileCount == learnCount)						
				{
					cout << "The animal learns how to do a " << trickAttempt << endl;
					ofstream tricksLearntAdd("Animal_Tricks_Learnt.txt", ios::app);
					//animalTricksLearnt.flush();
					//Setting the states for the transition
					this->CurrentContext->setState(Passivec);
					usedState = Passivec;
					//Adds the learnt word to a new file 
					animalTricksLearnt << trickAttempt << "\n";
					animalTricksLearnt.close();
					learnCount = 0;
					animalTricks.close();
					prevState = Trickc;
					return true;
				}

			}
		}
		cout << "Trick was not learned, try again" << endl;
	}
	animalTricks.close();
	prevState = Trickc;
	return true;
}
class animalAi : public StateContext, public Transition
{
private:
	AnimalState* AICurrentState = nullptr;
public:
	animalAi(void);
	//~animalAi(void);
	virtual bool Wandering(void);
	virtual bool Playing(void);
	virtual bool UnHappy(void);
	virtual bool Eating(void);
	virtual bool full(void);
	virtual bool tired(void);
	virtual bool Sleeping(void);
	virtual bool Drinking(void);
	virtual bool Boredom(void);
	virtual bool DoTrick(void);

	//virtual void setStateParam(stateParameter SP, int value);
	//virtual int getStateParam(stateParameter SP);
};
//enum state { Happy, Sad, Hungry, Tired, Passive, Asleep, Full };
animalAi::animalAi(void)
{
	this->availableStates.push_back(new Happy(this));
	this->availableStates.push_back(new Sad(this));
	this->availableStates.push_back(new Hungry(this));
	this->availableStates.push_back(new Tired(this));
	this->availableStates.push_back(new Passive(this));
	this->availableStates.push_back(new Asleep(this));
	this->availableStates.push_back(new Full(this));
	this->availableStates.push_back(new Thirsty(this));
	this->availableStates.push_back(new Bored(this));
	this->availableStates.push_back(new Tricks(this));

}

//Used to change the states when the new state is called
//allows access into the states for the functions being called  
bool animalAi::Wandering(void)
{
	AICurrentState = (AnimalState*) this->CurrentState;
	return this->AICurrentState->Wandering();
}

bool animalAi::Playing(void)
{
	AICurrentState = (AnimalState*)this->CurrentState;
	return this->AICurrentState->Playing();
}

bool animalAi::UnHappy(void)
{
	AICurrentState = (AnimalState*)this->CurrentState;
	return this->AICurrentState->UnHappy();
}
bool animalAi::Eating(void)
{
	AICurrentState = (AnimalState*)this->CurrentState;
	return this->AICurrentState->Eating();
}
bool animalAi::full(void)
{
	AICurrentState = (AnimalState*)this->CurrentState;
	return this->AICurrentState->full();
}
bool animalAi::tired(void)
{
	AICurrentState = (AnimalState*)this->CurrentState;
	return this->AICurrentState->tired();
}
bool animalAi::Sleeping(void)
{
	AICurrentState = (AnimalState*)this->CurrentState;
	return this->AICurrentState->Sleeping();
}
bool animalAi::Drinking(void)
{
	AICurrentState = (AnimalState*)this->CurrentState;
	return this->AICurrentState->Drinking();
}
bool animalAi::Boredom(void)
{
	AICurrentState = (AnimalState*)this->CurrentState;
	return this->AICurrentState->Boredom();
}
bool animalAi::DoTrick(void)
{
	AICurrentState = (AnimalState*)this->CurrentState;
	return this->AICurrentState->DoTrick();
}
int main()
{
	animalAi creature;
	creature.setState(Passivec);
	//Never ending loop
	//clear screen just for smartness - don't want constant words displaying
	//lowers food and thirsy levels
	//if foor or water are too low then the creature will break any state and change to these states
	//changes the state of the AI at run time by using a switch
	//Switch runs the state using the variale set
	//each case activates the function inside state
	for (;;)
	{
		Sleep(5000);
		system("CLS");
		foodLevel -= 1;
		waterLevel -= 2;
		if (waterLevel <= 0)
		{
			waterLevel = 0;
			creature.setState(Thirstc);
			usedState = Thirstc;
		}
		if (foodLevel <= 0)
		{
			foodLevel = 0;
			creature.setState(Hungryc);
			usedState = Hungryc;
		}
		cout << "foodLevel = " << foodLevel << endl;
		cout << "waterLevel = " << waterLevel << endl;
		switch (usedState)
		{
		case Happyc:
			creature.Playing();
			break;
		case Sadc:
			creature.UnHappy();
			break;
		case Hungryc:
			creature.Eating();
			break;
		case Tiredc:
			creature.tired();
			break;
		case Passivec:
			creature.Wandering();
			break;
		case Asleepc:
			creature.Sleeping();
			break;
		case Fullc:
			creature.full();
			break;
		case Thirstc:
			creature.Drinking();
			break;
		case Boredc:
			creature.Boredom();
			break;
		case Trickc:
			creature.DoTrick();
			break;
		default:
			break;
		}
	}
	system("pause");
}
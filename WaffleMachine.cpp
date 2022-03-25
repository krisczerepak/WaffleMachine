// SimpleStateMachine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <map>

using std::cout;
using std::string;
using std::endl;

class WaffleState;
class WaffleMachineInit;

class WaffleMachine {
public:
	/*WaffleMachine() {
		currentState = &WaffleMachineInit::getInstance();
	} */
	WaffleMachine();
	void toggle();
	void setState(WaffleState& newState);
	/*void setState(WaffleState& newState) {
		//(*currentState).exit(this);
		currentState->exit(this);
	} */
private:
	WaffleState* currentState;
};

class WaffleState {
public:
	virtual void enter(WaffleMachine* WaffleMachine) = 0;
	virtual void toggle(WaffleMachine* WaffleMachine) = 0;
	virtual void exit(WaffleMachine* WaffleMachine) = 0;
};

class WaffleMachineInit :public WaffleState {
public:
	void enter(WaffleMachine* WaffleMachine) {
		cout << "Init State Entered" << endl;
	}
	void toggle(WaffleMachine* WaffleMachine);
	void exit(WaffleMachine* WaffleMachine) {
		cout << "Init State Exited" << endl;
	}
	static WaffleState& getInstance() {
		static WaffleMachineInit singleton;
		return singleton;
	}
private:
	WaffleMachineInit() {}
	WaffleMachineInit(const WaffleMachineInit& other);
};

class WaffleMachineRDY :public WaffleState {
public:
	void enter(WaffleMachine* WaffleMachine) {
		cout << "Rdy State Entered" << endl;
	} //Empty Definition
	void toggle(WaffleMachine* WaffleMachine) {
		(*WaffleMachine).setState(WaffleMachineInit::getInstance()); //Toggle RDY to Init
	}
	void exit(WaffleMachine* WaffleMachine) {
		cout << "Rdy State Exited" << endl;
	} //Empty Definition
	static WaffleState& getInstance() {
		static WaffleMachineRDY singleton;
		return singleton;
	}
private:
	WaffleMachineRDY() {}
	WaffleMachineRDY(const WaffleMachineRDY& other);
};

WaffleMachine::WaffleMachine() {
	currentState = &WaffleMachineInit::getInstance();
}
void WaffleMachine::toggle() {
	//currentState->toggle(this); //Equivalent to below
	(*currentState).toggle(this);
}
void WaffleMachineInit::toggle(WaffleMachine* WaffleMachine) {
	(*WaffleMachine).setState(WaffleMachineRDY::getInstance());
}
void WaffleMachine::setState(WaffleState& newState) {
	(*currentState).exit(this);
	currentState = &newState;
	(*currentState).enter(this);
}

int main()
{
	string DennysOrder = "HRML listing";
	WaffleMachine DennysGrandSlam;
	DennysGrandSlam.toggle();
	DennysGrandSlam.toggle();
	DennysGrandSlam.toggle();
    std::cout << "Hello World!\n";
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#include <iostream>
#include "TransitionCounter.h"

using namespace std;

int main() {
	// buses
	bus clk, rst, J, start, end, transition_count(8);

	// wire datapath and controller
	TransitionCounter* tcount = new TransitionCounter(rst, clk, start, end, J, transition_count);

	// test case 1
	// =========================================================================================================================
	cout << "Test case 1 begins...\n";
	cout << "start = 0; end = 0; J changes 0->1. Expected output = 0x00.\n";
	// reset
	tcount->init();
	start = "0"; end = "0";
	J = "0"; clk = "P";
	tcount->evl();
	J = "1";
	tcount->evl();
	cout << "Transition count: " << transition_count << endl << endl;

	// test case 2
	// =========================================================================================================================
	cout << "Test case 2 begins...\n";
	cout << "pulse on start; end = 0; J changes 0->1, 1->0. Expected output = 0x02.\n";
	// reset
	tcount->init();
	// pulse on start
	start = "0"; end = "0"; J = "0"; rst = "0"; clk = "P";
	tcount->evl();
	start = "1";
	tcount->evl();
	start = "0";
	tcount->evl();
	// transitions on J
	J = "1";
	tcount->evl();
	J = "0";
	tcount->evl();
	cout << "Transition count: " << transition_count << endl << endl;

	// test case 3
	// =========================================================================================================================
	cout << "Test case 3 begins...\n";
	cout << "pulse on start; end = 0; J changes 0->1, 1->0; pulse on end; J changes 0->1, 1->0. Expected output = 0x02.\n";
	// reset
	tcount->init();
	// pulse on start
	start = "0"; end = "0";  J = "0"; rst = "0"; clk = "P";
	tcount->evl();
	start = "1";
	tcount->evl();
	start = "0";
	tcount->evl();
	// transitions on J
	J = "1";
	tcount->evl();
	J = "0";
	tcount->evl();
	// pulse on end
	end = "1";
	tcount->evl();
	end = "0";
	tcount->evl();
	// transitions on J
	J = "1";
	tcount->evl();
	J = "0";
	tcount->evl();
	cout << "Transition count: " << transition_count << endl << endl;
	// reset
	tcount->init();

	// test case 4
	// =========================================================================================================================
	cout << "Test case 4 begins...\n";
	cout << "pulse on start; end = 0; J changes 0->1, 1->0 - overall 256 times. Expected output = 0xFF on 255, 0x00 on 256.\n";
	// reset
	tcount->init();
	// pulse on start
	start = "0"; end = "0";  J = "0"; rst = "0"; clk = "P";
	tcount->evl();
	start = "1";
	tcount->evl();
	start = "0";
	tcount->evl();
	// transitions on J
	int count = 0;
	while (count != 127) {
		J = "1";
		tcount->evl();
		J = "0";
		tcount->evl();
		count++;
	}
	J = "1";
	tcount->evl();
	cout << "Transition count, J changed 255 times: " << transition_count << endl;
	J = "0";
	tcount->evl();
	cout << "Transition count, J changed 256 times: " << transition_count << endl << endl;

	return 0;
}

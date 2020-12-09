#include "polymorphismLogicClassesUtilities.h"

void inpBit(string wireName, Wire& valtim) {
	char value;
	int time;
	cout << "Enter value followed by @ time for " << wireName << ": ";
	cin >> value; cin >> time;
	valtim.put(value, time);
}

void inpBit(string wireName, Wire& valtim, int time) {
	char value;
	cout << "For @ time " << time << ", enter logic value for " << wireName << ": ";
	cin >> value; 
	valtim.put(value, time);
}

void outBit(string wireName, Wire valtim) {
	char value;
	int time;
	valtim.get(value, time);
	cout << wireName << ": " << value << " @ " << time << "\n";
}

void inpBit(string wireName, WireV& valtim) {
	string value;
	int time;
	cout << "Enter value followed by @ time for " << wireName << ": ";
	cin >> value; cin >> time;
	valtim.put(value, time);
}

void outBit(string wireName, WireV valtim) {
	string value;
	int time;
	valtim.get(value, time);
	cout << wireName << ": " << value << " @ " << time << "\n";
}

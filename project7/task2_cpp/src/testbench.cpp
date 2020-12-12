#include <iostream>
#include "ALU.h"

using namespace std;

int main() {
	// buses
	bus A(8), B(8), F(2), W(8), c(1), g(1);

	// instantiate and wire the unit under test
	ALU *uut = new ALU(A, B, F, W, c, g);

	// test case 1
	// ==========================================
	cout << "Test case 1.\n";
	A = "00000000";
	B = "00000000";

	cout << "A = " << A << ", B = " << B << "." << endl;
	// sum
	F = "00";
	uut->evl();
	cout << "------------------------------" << endl;
	cout << "F=00 (W=A+B):" << endl;
	cout << "W = " << W << endl;
	cout << "c = " << c << endl;
	cout << "g = " << g << endl << endl;
	// max
	F = "01";
	uut->evl();
	cout << "F=01 (W=Max(A,B)):" << endl;
	cout << "W = " << W << endl;
	cout << "c = " << c << endl;
	cout << "g = " << g << endl << endl;
	// zero
	F = "10";
	uut->evl();
	cout << "F=10 (W=0):" << endl;
	cout << "W = " << W << endl;
	cout << "c = " << c << endl;
	cout << "g = " << g << endl << endl;
	// or
	F = "11";
	uut->evl();
	cout << "F=11 (W=A|B):" << endl;
	cout << "W = " << W << endl;
	cout << "c = " << c << endl;
	cout << "g = " << g << endl << endl;

	// test case 2
	// ==========================================
	cout << "Test case 2.\n";
	A = "11111111";
	B = "11111111";

	cout << "A = " << A << ", B = " << B << "." << endl;
	// sum
	F = "00";
	uut->evl();
	cout << "------------------------------" << endl;
	cout << "F=00 (W=A+B):" << endl;
	cout << "W = " << W << endl;
	cout << "c = " << c << endl;
	cout << "g = " << g << endl << endl;
	// max
	F = "01";
	uut->evl();
	cout << "F=01 (W=Max(A,B)):" << endl;
	cout << "W = " << W << endl;
	cout << "c = " << c << endl;
	cout << "g = " << g << endl << endl;
	// zero
	F = "10";
	uut->evl();
	cout << "F=10 (W=0):" << endl;
	cout << "W = " << W << endl;
	cout << "c = " << c << endl;
	cout << "g = " << g << endl << endl;
	// or
	F = "11";
	uut->evl();
	cout << "F=11 (W=A|B):" << endl;
	cout << "W = " << W << endl;
	cout << "c = " << c << endl;
	cout << "g = " << g << endl << endl;

	// test case 3
		// ==========================================
	cout << "Test case 3.\n";
	A = "11110000";
	B = "00001111";

	cout << "A = " << A << ", B = " << B << "." << endl;
	// sum
	F = "00";
	uut->evl();
	cout << "------------------------------" << endl;
	cout << "F=00 (W=A+B):" << endl;
	cout << "W = " << W << endl;
	cout << "c = " << c << endl;
	cout << "g = " << g << endl << endl;
	// max
	F = "01";
	uut->evl();
	cout << "F=01 (W=Max(A,B)):" << endl;
	cout << "W = " << W << endl;
	cout << "c = " << c << endl;
	cout << "g = " << g << endl << endl;
	// zero
	F = "10";
	uut->evl();
	cout << "F=10 (W=0):" << endl;
	cout << "W = " << W << endl;
	cout << "c = " << c << endl;
	cout << "g = " << g << endl << endl;
	// or
	F = "11";
	uut->evl();
	cout << "F=11 (W=A|B):" << endl;
	cout << "W = " << W << endl;
	cout << "c = " << c << endl;
	cout << "g = " << g << endl << endl;


	// test case 4
		// ==========================================
	cout << "Test case 4.\n";
	A = "01010101";
	B = "10101010";

	cout << "A = " << A << ", B = " << B << "." << endl;
	// sum
	F = "00";
	uut->evl();
	cout << "------------------------------" << endl;
	cout << "F=00 (W=A+B):" << endl;
	cout << "W = " << W << endl;
	cout << "c = " << c << endl;
	cout << "g = " << g << endl << endl;
	// max
	F = "01";
	uut->evl();
	cout << "F=01 (W=Max(A,B)):" << endl;
	cout << "W = " << W << endl;
	cout << "c = " << c << endl;
	cout << "g = " << g << endl << endl;
	// zero
	F = "10";
	uut->evl();
	cout << "F=10 (W=0):" << endl;
	cout << "W = " << W << endl;
	cout << "c = " << c << endl;
	cout << "g = " << g << endl << endl;
	// or
	F = "11";
	uut->evl();
	cout << "F=11 (W=A|B):" << endl;
	cout << "W = " << W << endl;
	cout << "c = " << c << endl;
	cout << "g = " << g << endl << endl;

	return 0;
}

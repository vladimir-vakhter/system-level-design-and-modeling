#include "CalculatorTB.h"

#define TIME_TEST		// measure the wall-clock time spent by the simulation

#ifdef TIME_TEST
#include<time.h>
#include <fstream>
#include<string>
#include <iostream>
#include <iomanip>
const std::string path = "time.txt";
#endif // TIME_TEST

int sc_main(int argc, char **argv)
{
	#ifdef TIME_TEST
	clock_t start, end;
	/* clock_t clock(void) returns the number of clock ticks
	   elapsed since the program was launched.To get the number
	   of seconds used by the CPU, you will need to divide by
	   CLOCKS_PER_SEC.where CLOCKS_PER_SEC is 1000000 on typical
	   32 bit system.  */
	start = clock();
	#endif // TIME_TEST
	
	CalculatorTB TB1("testbench");

	sc_trace_file* vcd_file;	// trace signals

	vcd_file = sc_create_vcd_trace_file ("calculator_test");
		sc_trace(vcd_file, TB1.clk,				"clock");
		sc_trace(vcd_file, TB1.rst,				"reset");
		sc_trace(vcd_file, TB1.XBus,			"XBus");
		sc_trace(vcd_file, TB1.go,				"go");
		sc_trace(vcd_file, TB1.RBus,			"RBus");
		sc_trace(vcd_file, TB1.ready,			"ready");

	sc_start(12000, SC_NS);
	
	#ifdef TIME_TEST
	ofstream output(path);
	end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	output << "Time taken by program is : " << std::fixed
		<< time_taken << std::setprecision(10);
	output << " sec " << endl;
	#endif // TIME_TEST
	
	return 0;
}

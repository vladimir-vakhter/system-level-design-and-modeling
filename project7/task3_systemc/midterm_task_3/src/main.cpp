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
		#ifdef DEBUG
		// controller
		sc_trace(vcd_file, TB1.incC,			"incC");
		sc_trace(vcd_file, TB1.in0C,			"in0C");
		sc_trace(vcd_file, TB1.coC,				"coC");
		sc_trace(vcd_file, TB1.cntout,			"cntout");
		sc_trace(vcd_file, TB1.ldx,				"ldx");
		sc_trace(vcd_file, TB1.ldT,				"ldT");
		sc_trace(vcd_file, TB1.in1T,			"in1T");
		sc_trace(vcd_file, TB1.ldR,				"ldR");
		sc_trace(vcd_file, TB1.in1R,			"in1R");
		// datapath
		sc_trace(vcd_file, TB1.enT,				"enT");
		sc_trace(vcd_file, TB1.enR,				"enR");
		sc_trace(vcd_file, TB1.T_reg_out,		"T_reg_out");
		sc_trace(vcd_file, TB1.mult_out_16msb,	"mult_out_16msb");
		sc_trace(vcd_file, TB1.X_reg_in,		"X_reg_in");
		sc_trace(vcd_file, TB1.X_reg_out,		"X_reg_out");
		sc_trace(vcd_file, TB1.T_reg_in,		"T_reg_in");
		sc_trace(vcd_file, TB1.add_in1,			"add_in1");
		sc_trace(vcd_file, TB1.add_out,			"add_out");
		sc_trace(vcd_file, TB1.R_reg_in,		"R_reg_in");
		sc_trace(vcd_file, TB1.mult_out,		"mult_out");
		#endif // DEBUG

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

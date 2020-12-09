#include "AvgCalcTB.h"

int sc_main(int argc, char **argv)
{
	AvgCalcTB TB1("testbench");

	sc_trace_file* vcd_file;	// trace signals

	vcd_file = sc_create_vcd_trace_file ("average_calculator_test");
		sc_trace(vcd_file, TB1.clk,			"clock");
		sc_trace(vcd_file, TB1.rst,			"reset");
		sc_trace(vcd_file, TB1.start,		"start");
		sc_trace(vcd_file, TB1.data,		"data");
		sc_trace(vcd_file, TB1.avg,			"average");
		sc_trace(vcd_file, TB1.rdy,			"ready");
		#ifdef DEBUG
		sc_trace(vcd_file, TB1.ce,			"ce");
		sc_trace(vcd_file, TB1.counter_out, "co");
		sc_trace(vcd_file, TB1.addout,		"adder_out");
		sc_trace(vcd_file, TB1.en,			"en");
		sc_trace(vcd_file, TB1.zer,			"zer");
		sc_trace(vcd_file, TB1.regout,		"result_reg_out");
		#endif // DEBUG
	
	sc_start(12000, SC_NS);
	return 0;
}

#include "AvgCalcTB.h"

void AvgCalcTB::clocking()
{
	int i;
	clk = SC_LOGIC_1;
	for (i = 0; i <= 55; i++)
	{
		clk = SC_LOGIC_0;
		wait(50, SC_NS);
		clk = SC_LOGIC_1;
		wait(50, SC_NS);
	}
}

void AvgCalcTB::resetting()
{
	rst = SC_LOGIC_0;
	wait(5, SC_NS);
	rst = SC_LOGIC_1;
	wait(5, SC_NS);
	rst = SC_LOGIC_0;
}

void AvgCalcTB::inputting()
{
	// inactivate the data bus
	data = "00000000";
	
	// test case 1: avg = 0x00
	wait(10, SC_NS);
	start = SC_LOGIC_0;
	wait(90, SC_NS);
	start = SC_LOGIC_1;
	wait(105, SC_NS);
	start = SC_LOGIC_0;
	wait(145, SC_NS);

	data = "00000000";
	wait(900, SC_NS);
	data = "00000000";

	// test case 2: avg = 0xFF
	wait(260, SC_NS);
	start = SC_LOGIC_0;
	wait(90, SC_NS);
	start = SC_LOGIC_1;
	wait(105, SC_NS);
	start = SC_LOGIC_0;
	wait(145, SC_NS);

	data = "11111111";
	wait(100, SC_NS);
	data = "11111111";
	wait(100, SC_NS);
	data = "11111111";
	wait(100, SC_NS);
	data = "11111111";
	wait(100, SC_NS);
	data = "11111111";
	wait(100, SC_NS);
	data = "11111111";
	wait(100, SC_NS);
	data = "11111111";
	wait(100, SC_NS);
	data = "11111111";
	wait(100, SC_NS);
	data = "00000000";

	// test case 3: avg = 00111110 (0x3E)
	wait(260, SC_NS);
	start = SC_LOGIC_0;
	wait(90, SC_NS);
	start = SC_LOGIC_1;
	wait(105, SC_NS);
	start = SC_LOGIC_0;
	wait(145, SC_NS);

	data = "00000001";
	wait(100, SC_NS);
	data = "00000011";
	wait(100, SC_NS);
	data = "00000111";
	wait(100, SC_NS);
	data = "00001111";
	wait(100, SC_NS);
	data = "00011111";
	wait(100, SC_NS);
	data = "00111111";
	wait(100, SC_NS);
	data = "01111111";
	wait(100, SC_NS);
	data = "11111111";
	wait(100, SC_NS);
	data = "00000000";

	// test case 4: avg = 11100000 (0xE0)
	wait(260, SC_NS);
	start = SC_LOGIC_0;
	wait(90, SC_NS);
	start = SC_LOGIC_1;
	wait(105, SC_NS);
	start = SC_LOGIC_0;
	wait(145, SC_NS);

	data = "10000000";
	wait(100, SC_NS);
	data = "11000000";
	wait(100, SC_NS);
	data = "11100000";
	wait(100, SC_NS);
	data = "11110000";
	wait(100, SC_NS);
	data = "11111000";
	wait(100, SC_NS);
	data = "11111100";
	wait(100, SC_NS);
	data = "11111110";
	wait(100, SC_NS);
	data = "11111111";
	wait(100, SC_NS);
	data = "00000000";
	wait(60, SC_NS);
}

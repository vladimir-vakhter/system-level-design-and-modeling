#include "CalculatorTB.h"

void CalculatorTB::clocking()
{
	int i;
	clk = SC_LOGIC_1;
	for (i = 0; i <= 300; i++)
	{
		clk = SC_LOGIC_0;
		wait(50, SC_NS);
		clk = SC_LOGIC_1;
		wait(50, SC_NS);
	}
}

void CalculatorTB::resetting()
{
	rst = SC_LOGIC_0;
	wait(5, SC_NS);
	rst = SC_LOGIC_1;
	wait(5, SC_NS);
	rst = SC_LOGIC_0;
}

// the input range is 0 =< Xbus <= 0.5
void CalculatorTB::inputting()
{
	// test case 1 (low border condition): XBus = 0, expected Rbus = 1
	XBus = 0;
	
	wait(10, SC_NS);
	go = SC_LOGIC_0;
	wait(90, SC_NS);
	go = SC_LOGIC_1;
	wait(105, SC_NS);
	go = SC_LOGIC_0;
	wait(3745, SC_NS);

	// test case 2 (high border condition): XBus = 0.5, expected Rbus = around 2
	XBus = 0.5;
	
	wait(260, SC_NS);
	go = SC_LOGIC_0;
	wait(90, SC_NS);
	go = SC_LOGIC_1;
	wait(105, SC_NS);
	go = SC_LOGIC_0;
	wait(3745, SC_NS);

	// test case 3: XBus = 0.25, expected Rbus = around 1.33
	XBus = 0.25;
	
	wait(260, SC_NS);
	go = SC_LOGIC_0;
	wait(90, SC_NS);
	go = SC_LOGIC_1;
	wait(105, SC_NS);
	go = SC_LOGIC_0;
	wait(3745, SC_NS);

	// test case 4: XBus = 0.125, expected Rbus = around 1.14
	XBus = 0.125;

	wait(10, SC_NS); //wait(260, SC_NS);
	go = SC_LOGIC_0;
	wait(90, SC_NS);
	go = SC_LOGIC_1;
	wait(105, SC_NS);
	go = SC_LOGIC_0;
	wait(3745, SC_NS);
}
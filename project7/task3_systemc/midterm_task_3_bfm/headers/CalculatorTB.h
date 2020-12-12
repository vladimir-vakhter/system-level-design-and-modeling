#pragma once
#include "CalculatorBFM.h"

SC_MODULE(CalculatorTB)
{
	sc_signal<float>			XBus, RBus;
	sc_signal<sc_logic>			clk, rst, go, ready;

	CalculatorBFM<32, 12> *UUT;		

	SC_CTOR(CalculatorTB)
	{
		UUT = new CalculatorBFM<32, 12>("calculatorBFMInstance");		
			UUT->clk(clk);
			UUT->rst(rst);
			UUT->XBus(XBus);		
			UUT->go(go);		
			UUT->ready(ready);		
			UUT->RBus(RBus);

		// stimuli (no sensitivity) - event loops
		SC_THREAD(clocking);
		SC_THREAD(resetting);
		SC_THREAD(inputting);
	}
	void clocking();
	void resetting();
	void inputting();
};

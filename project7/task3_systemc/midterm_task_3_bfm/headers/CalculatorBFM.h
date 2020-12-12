#pragma once
#include <systemc.h>

template <int NumClk, int N>	// NumClk - number of clocks, N - number of iterations
SC_MODULE(CalculatorBFM)
{
	// ports
	sc_in<float>			XBus;	
	sc_in<sc_logic>			clk;
	sc_in<sc_logic>			rst;
	sc_in<sc_logic>			go;					
	sc_out<float>			RBus;
	sc_out<sc_logic>		ready;				
					
	sc_signal<float>		XBus_reg;

	SC_CTOR(CalculatorBFM)
	{
		SC_THREAD(operation);
			sensitive << clk << rst;
	}
	void operation();
};

template <int NumClk, int N>
void CalculatorBFM<NumClk, N>::operation()
{
	while (true) {
		float term = 1;
		float res  = 1;
		
		if (rst == '1') {
			ready = SC_LOGIC_1;
			RBus = 0;
		} 
		
		else if ((clk->event()) && (clk == '1')) {
			if (go == '1') 
			{
				ready = SC_LOGIC_0;
				wait(clk->posedge_event());
				RBus = 1;

				XBus_reg = XBus->read();
				wait(clk->posedge_event());

				for (int i = 1; i < N; i++) {
					term = term * XBus_reg.read();
					res = res + term;
					wait(clk->posedge_event());
					RBus = res;
				}

				for (int i = 0; i < NumClk-N; i++) {
					wait(clk->posedge_event());
				}

				ready = SC_LOGIC_1;
				//RBus = res;
			}
		}
		wait();
	}
}

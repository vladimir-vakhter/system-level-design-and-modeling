#pragma once
#include <systemc.h>

template <int NumClk>
SC_MODULE(AvgCalcBFM) {
	// ports
	sc_in<sc_lv<8>>		data;
	sc_in<sc_logic>		rst, clk, start;
	
	sc_out<sc_logic>	rdy;
	sc_out<sc_lv<8>>	avg;

	// constructor
	SC_CTOR(AvgCalcBFM)
	{
		SC_THREAD(operation);
			sensitive << clk << rst;
	}
	void operation();
};

template <int NumClk>
void AvgCalcBFM<NumClk>::operation()
{
	while (true) {
		sc_lv<11> sum = "00000000000";
		
		if (rst == '1') {
			rdy = SC_LOGIC_0;
			avg = "00000000";
		} else if ((clk->event()) && (clk == '1')) {
			if (start == '1') {
				rdy = SC_LOGIC_0;
				wait(clk->posedge_event());
				avg = "00000000";

				for (int i = 0; i < NumClk; i++) {
					wait(clk->posedge_event());
					avg = sum.range(10, 3);
					sum = sum.to_uint() + data->read().to_uint();
				}

				wait(clk->posedge_event());
				rdy = SC_LOGIC_1;
				avg = sum.range(10, 3);
			}
		}
		wait();
	}
}

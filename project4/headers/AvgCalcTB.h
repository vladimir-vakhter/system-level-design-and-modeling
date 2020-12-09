#pragma once
#include "AvgCalculator.h"
#include "AvgCalculatorBFM.h"

//#define DEBUG
//#define BFM

SC_MODULE(AvgCalcTB)
{
	sc_signal<sc_lv<8>> data, avg;
	sc_signal<sc_logic>	rst, clk, start, rdy;
	#ifdef DEBUG
	sc_signal<sc_lv<3>> counter_out;
	sc_signal<sc_logic> en, zer, ce;
	sc_signal<sc_lv<11>> regout, addout;
	#endif // DEBUG

	#ifdef BFM
	AvgCalcBFM<8>* UUT;
	#else
	AvgCalc* UUT;
	#endif // BFM

	SC_CTOR(AvgCalcTB)
	{
		#ifdef BFM
		UUT = new AvgCalcBFM<8>("AvgCalc_instance");
		#else
		UUT = new AvgCalc("AvgCalc_instance");
		#endif // BFM
			UUT->data(data);
			UUT->rst(rst);
			UUT->clk(clk);
			UUT->start(start);
			UUT->avg(avg);
			UUT->rdy(rdy);
			#ifdef DEBUG
			UUT->co(counter_out);
			UUT->en(en);
			UUT->zer(zer);
			UUT->ce(ce);
			UUT->regout(regout);
			UUT->addout(addout);
			#endif // DEBUG
		// stimuli (no sensitivity) - event loops
		SC_THREAD(clocking);
		SC_THREAD(resetting);
		SC_THREAD(inputting);
	}
	void clocking();
	void resetting();
	void inputting();
};

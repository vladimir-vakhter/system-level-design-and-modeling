#pragma once
#include <iostream>
#include <iomanip>
#include "Calculator.h"
#include "CalculatorBFM.h"

//#define DEBUG

SC_MODULE(CalculatorTB)
{
	sc_signal<sc_lv<18>>		XBus;				// 18-bit fixed-point number (2 integer bits - 16 fractional bits), 0 =< x <= 0.5
	sc_signal<sc_logic>			rst, clk;
	sc_signal<sc_logic>			go;					// after a positive pulse on go, XBus is received and calculation begins
	sc_signal<sc_logic>			ready;				// goes high when the calculation is complete (after 16 iterations)
	sc_signal<sc_lv<18>>		RBus;				// result	


	#ifdef DEBUG
	// controller
	sc_signal<sc_logic>			incC, in0C, coC, ldx, ldT, in1T, ldR, in1R;
	// datapath
	sc_signal<sc_logic>			enT, enR;
	sc_signal<sc_lv<16>>		T_reg_out, mult_out_16msb, X_reg_in, X_reg_out, T_reg_in;
	sc_signal<sc_lv<18>>		add_in1, add_out, R_reg_in;
	sc_signal<sc_lv<32>>		mult_out;
	sc_signal<sc_lv<4>>			cntout;
	#endif // DEBUG

	Calculator* UUT;

	SC_CTOR(CalculatorTB)
	{
		UUT = new Calculator("calculatorInstance");
			UUT->clk(clk);
			UUT->rst(rst);
			UUT->XBus(XBus);		
			UUT->go(go);		
			UUT->ready(ready);		
			UUT->RBus(RBus);
			#ifdef DEBUG
			// counter
			UUT->cntout(cntout);
			// controller
			UUT->incC(incC);				
			UUT->in0C(in0C);
			UUT->coC(coC);
			UUT->ldx(ldx);
			UUT->ldT(ldT);
			UUT->in1T(in1T);
			UUT->ldR(ldR);
			UUT->in1R(in1R);
			//datapath
			UUT->enT(enT);
			UUT->enR(enR);
			UUT->T_reg_out(T_reg_out);
			UUT->mult_out_16msb(mult_out_16msb);
			UUT->X_reg_in(X_reg_in);
			UUT->X_reg_out(X_reg_out);
			UUT->T_reg_in(T_reg_in);
			UUT->add_in1(add_in1);
			UUT->add_out(add_out);
			UUT->R_reg_in(R_reg_in);
			UUT->mult_out(mult_out);
			#endif

		// stimuli (no sensitivity) - event loops
		SC_THREAD(clocking);
		SC_THREAD(resetting);
		SC_THREAD(inputting);
	}
	void clocking();
	void resetting();
	void inputting();
};

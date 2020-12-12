#pragma once
#include <systemc.h>
#include "Controller.h"
#include "Datapath.h"

//#define DEBUG

// 4-bit uCounterRaELCo: Up-counter w/ asynch Reset, clock Enable, parallel Load, Carry
SC_MODULE(uCounterRaELCo_4bit)
{
	// ports
	sc_in<sc_logic>		rst, clk, cen, pld;		// reset (async), clock, clock enable, parallel load
	sc_in<sc_logic>		ci;						// carry in
	sc_out<sc_logic>	co;						// carry out (counter reached its maximum)
	sc_in<sc_lv<4>>		parin;					// parallel in (4 bits)
	sc_out<sc_lv<4>>	cntout;					// count out (4 bits)

	SC_CTOR(uCounterRaELCo_4bit)
	{
		SC_METHOD(counting);
		sensitive << rst << clk;
		SC_METHOD(carrying);
		sensitive << ci << cntout;
	}
	void counting() {
		if (rst == '1')
		{
			cntout = "0000";
		}
		else if (clk->event() && (clk == '1'))
		{
			if (pld == '1') cntout = parin;
			else if (cen == '1' && ci == '1') cntout = cntout->read().to_uint() + 1;
		}
	}

	void carrying() {
		if ((ci == '1') && (cntout.read().to_uint() == 15)) co = SC_LOGIC_1;
		else co = SC_LOGIC_0;
	}
};

// a processing element for approximate calculation of 1/(1-x) 
SC_MODULE(Calculator) {
	// ports
	sc_in<sc_lv<18>>		XBus;				// 18-bit fixed-point number (2 integer bits - 16 fractional bits), 0 =< x <= 0.5
	sc_in<sc_logic>			rst, clk;
	sc_in<sc_logic>			go;					// after a positive pulse on go, XBus is received and calculation begins
	sc_out<sc_logic>		ready;				// goes high when the calculation is complete (after 16 iterations)
	sc_out<sc_lv<18>>		RBus;				// result
	
	// internal signals
	#ifdef DEBUG
	sc_out<sc_logic>		incC, in0C, coC, ldx, ldT, in1T, ldR, in1R;
	sc_out<sc_logic>		enT, enR;
	sc_out<sc_lv<16>>		T_reg_out, mult_out_16msb, X_reg_in, X_reg_out, T_reg_in;
	sc_out<sc_lv<18>>		add_in1, add_out, R_reg_in;
	sc_out<sc_lv<32>>		mult_out;
	sc_out<sc_lv<4>>		cntout;
	#else
	sc_signal<sc_logic>		incC, in0C, coC, ldx, ldT, in1T, ldR, in1R;
	sc_signal<sc_lv<4>>		cntout;
	#endif // DEBUG

	sc_signal<sc_logic>		ci;
	sc_signal<sc_lv<4>>		parin;		

	// submodules
	Controller*				controller;
	Datapath*				datapath;
	uCounterRaELCo_4bit*	terms_counter;

	// constructor
	SC_CTOR(Calculator)
	{
		// signals which values do not change
		parin.write("0000");
		ci.write(SC_LOGIC_1);

		controller = new Controller("controller");
			controller->clk(clk);
			controller->rst(rst);
			controller->go(go);
			controller->coC(coC);
			controller->in0C(in0C);
			controller->incC(incC);
			controller->ldx(ldx);
			controller->ldT(ldT);
			controller->in1T(in1T);
			controller->ldR(ldR);
			controller->in1R(in1R);
			controller->ready(ready);

		datapath = new Datapath("datapath");
			datapath->clk(clk);
			datapath->rst(rst);
			datapath->XBus(XBus);
			datapath->ldx(ldx);
			datapath->ldT(ldT);
			datapath->in1T(in1T);
			datapath->ldR(ldR);
			datapath->in1R(in1R);
			datapath->RBus(RBus);
			#ifdef DEBUG
			datapath->enT(enT);
			datapath->enR(enR);
			datapath->T_reg_out(T_reg_out);
			datapath->mult_out_16msb(mult_out_16msb);
			datapath->X_reg_in(X_reg_in);
			datapath->X_reg_out(X_reg_out);
			datapath->T_reg_in(T_reg_in);
			datapath->add_in1(add_in1);
			datapath->add_out(add_out);
			datapath->R_reg_in(R_reg_in);
			datapath->mult_out(mult_out);
			#endif // DEBUG

		terms_counter = new uCounterRaELCo_4bit("terms_counter");
			terms_counter->clk(clk);
			terms_counter->rst(rst);
			terms_counter->cen(incC);
			terms_counter->pld(in0C);
			terms_counter->ci(ci);
			terms_counter->co(coC);			
			terms_counter->parin(parin);
			terms_counter->cntout(cntout);
	}
};

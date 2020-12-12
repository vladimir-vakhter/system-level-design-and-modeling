#pragma once
#include <systemc.h>
#include "Adder.h"
#include "Register.h"
#include "Mult.h"

//#define DEBUG

SC_MODULE(Datapath)
{
	// ports
	sc_in<sc_lv<18>>		XBus;							// input data
	sc_in<sc_logic>			clk, rst;
	sc_in<sc_logic>			ldx, ldT, in1T, ldR, in1R;		// control signals
	sc_out<sc_lv<18>>		RBus;							// result

	// local signals
	sc_signal<sc_logic>		zerX, zerT, zerR;
	
	#ifdef DEBUG
	sc_out<sc_logic>		enT, enR;
	sc_out<sc_lv<16>>		T_reg_out, mult_out_16msb, X_reg_in, X_reg_out, T_reg_in;
	sc_out<sc_lv<18>>		add_in1, add_out, R_reg_in;
	sc_out<sc_lv<32>>		mult_out;
	#else
	sc_signal<sc_logic>		enT, enR;
	sc_signal<sc_lv<16>>	T_reg_out, mult_out_16msb, X_reg_in, X_reg_out, T_reg_in;
	sc_signal<sc_lv<18>>	add_in1, add_out, R_reg_in;
	sc_signal<sc_lv<32>>	mult_out;
	#endif // DEBUG

	// submodules
	dRegister<16>*			X_register;						// X-bus
	Mult<16>*				mult;
	dRegister<16>*			T_register;						// term
	Adder<18>*				adder;
	dRegister<18>*			R_register;						// result

	// constructor
	SC_CTOR(Datapath)
	{
		X_register = new dRegister<16>("X_register");
			X_register->clk(clk);
			X_register->rst(rst);
			X_register->cen(ldx);							
			zerX.write(SC_LOGIC_0);							// reset to 0 - unused, pull-down
			X_register->zer(zerX);							
			X_register->regin(X_reg_in);
			X_register->regout(X_reg_out);

		mult = new Mult<16>("multiplier");
			mult->in1(X_reg_out);
			mult->in2(T_reg_out);
			mult->out(mult_out);
		
		T_register = new dRegister<16>("T_register");
			T_register->clk(clk);
			T_register->rst(rst);
			T_register->cen(enT);
			zerT.write(SC_LOGIC_0);							// reset to 0 - unused, pull-down
			T_register->zer(zerT);				
			T_register->regin(T_reg_in);
			T_register->regout(T_reg_out);
		
		adder = new Adder<18>("adder");
			adder->in1(add_in1);
			adder->in2(RBus);
			adder->out(add_out);

		R_register = new dRegister<18>("R_register");
			R_register->clk(clk);
			R_register->rst(rst);
			R_register->cen(enR);
			zerR.write(SC_LOGIC_0);						// reset to 0 - unused, pull-down
			R_register->zer(zerR);	
			R_register->regin(R_reg_in);
			R_register->regout(RBus);

		// combinational part
		SC_METHOD(evl_combinational);
			sensitive << XBus << mult_out << ldT << in1T
					  << T_reg_out << ldR << add_out << in1R;
	}

	void evl_combinational() 
	{
		// X-register input
		X_reg_in = XBus->read().range(15, 0);
		
		// T-register input and control (enable)
		mult_out_16msb = (mult_out.read().range(31, 16));
		if (ldT->read() == '1') {
			T_reg_in = mult_out_16msb;
		}
		else if (in1T->read() == '1') {
			T_reg_in = "1111111111111111";				// max (the closest to fixed-point 18-bit '1', where the integer part is 2 bits)	
		}		
		enT = (ldT->read() | in1T->read());

		// Adder input 1
		add_in1 = (sc_lv<2>("00"), T_reg_out.read());

		// R-register input and control (enable)
		if (ldR->read() == '1') {
			R_reg_in = add_out.read();
		}
		else if (in1R->read() == '1') {
			R_reg_in = "010000000000000000";			// 18-bit fixed-point '1', where the integer part is 2 bits
		}
		enR = (ldR->read() | in1R->read());
	}
};

#pragma once
#include <systemc.h>
#include "Adder.h"
#include "Register.h"

//#define DEBUG

SC_MODULE(Datapath)
{
	// input signals
	sc_in<sc_logic> rst, clk, en, zer; 
	sc_in<sc_lv<8>> data;
	sc_out<sc_lv<8>> avg;

	// local signals
	sc_signal<sc_lv<11>> addDataInput;

	#ifdef DEBUG
	sc_out<sc_lv<11>> regout, addout;
	#else
	sc_signal<sc_lv<11>> regout, addout;
	#endif // DEBUG

	// submodules
	Adder<11>*		adder;
	dRegister<11>*	result_reg;

	// constructor
	SC_CTOR(Datapath)
	{
		adder = new Adder<11>("adder");
			adder->in1(regout);
			adder->in2(addDataInput);
			adder->out(addout);

		result_reg	= new dRegister<11>("reg_11bit");
			result_reg->clk(clk);
			result_reg->rst(rst);
			result_reg->cen(en);
			result_reg->zer(zer);
			result_reg->regin(addout);
			result_reg->regout(regout);

		// combinational part
		SC_METHOD(evl_comb_states);
			sensitive << data << regout;
	}

	void evl_comb_states() {
		addDataInput = (sc_lv<3>("000"), data->read());
		avg = regout.read().range(10,3);
	}
};

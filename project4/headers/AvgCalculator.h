#pragma once
#include <systemc.h>

#include "Controller.h"
#include "Datapath.h"

//#define DEBUG

// 3-bit up-counter
SC_MODULE(uCounterRaEL_3bit)
{
	sc_in<sc_logic> rst, clk, cen, pld;
	sc_in<sc_lv<3>> parin;
	sc_out<sc_lv<3>> cntout;

	SC_CTOR(uCounterRaEL_3bit)
	{
		SC_METHOD(counting);
		sensitive << rst << clk;
	}
	void counting()
	{
		if (rst == '1')
		{
			cntout = 0;
		}
		else if (clk->event() && (clk == '1'))
		{
			if (pld == '1') cntout = parin;
			else if (cen == '1') cntout = cntout->read().to_uint() + 1;
		}
	}
};

SC_MODULE(AvgCalc) {
	// ports
	sc_in<sc_lv<8>>		data;
	sc_in<sc_logic>		rst, clk, start;
	sc_out<sc_logic>	rdy;
	sc_out<sc_lv<8>>	avg;

	#ifdef DEBUG
	sc_out<sc_lv<3>>	co;
	sc_out<sc_logic>	en, zer, ce;
	sc_out<sc_lv<11>>	regout, addout;
	#else
	sc_signal<sc_lv<3>> co;
	sc_signal<sc_logic> en, zer, ce;
	#endif // DEBUG	
					
	// internal signals
	sc_signal<sc_logic> pld;
	sc_signal<sc_lv<3>> parin;

	// submodules
	Controller*			controller;
	Datapath*			datapath;
	uCounterRaEL_3bit*	data_counter;

	// constructor
	SC_CTOR(AvgCalc) 
	{
		// signals which values do not change
		pld.write(SC_LOGIC_0);
		parin.write("000");

		controller = new Controller("controller");
			controller->clk(clk);
			controller->rst(rst);
			controller->start(start);
			controller->co(co);
			controller->en(en);
			controller->ce(ce);
			controller->zer(zer);
			controller->rdy(rdy);

		datapath = new Datapath("datapath");
			datapath->clk(clk);
			datapath->rst(rst);
			datapath->data(data);
			datapath->en(en);
			datapath->zer(zer);
			datapath->avg(avg);
			#ifdef DEBUG
			datapath->regout(regout);
			datapath->addout(addout);
			#endif // DEBUG

		data_counter = new uCounterRaEL_3bit("data_counter");
			data_counter->rst(rst);
			data_counter->clk(clk);
			data_counter->cen(ce);
			data_counter->pld(pld);
			data_counter->parin(parin);
			data_counter->cntout(co);
	}
};

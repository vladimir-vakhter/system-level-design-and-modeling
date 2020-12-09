#pragma once
#include <systemc.h>

SC_MODULE(Controller)
{
	// ports
	sc_in<sc_logic>		rst, clk, start;
	sc_in<sc_lv<3>>		co;
	sc_out<sc_logic>	en, ce, zer, rdy;
	
	// present/next state of Huffman finite state machine (FSM)
	enum states {st1_initialize, st2_wait_on_start, st3_calculate, st4_calc_complete, st5_average_is_valid};
	sc_signal<states> p_state, n_state;					
	
	// constructor
	SC_CTOR(Controller)
	{
		// initialize the FSM
		p_state.write(st1_initialize);
		n_state.write(st1_initialize);
		
		// combinational part of Huffman model
		SC_METHOD(evl_comb_states);
			sensitive << start << co << p_state;
		SC_METHOD(evl_comp_outputs);
			sensitive << p_state;
		// sequential part of Huffman model
		SC_THREAD(evl_sequential);
			sensitive << clk << rst;
	}
	void evl_comb_states();
	void evl_comp_outputs();
	void evl_sequential();
};

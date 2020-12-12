#pragma once
#include <systemc.h>

//#define DEBUG

SC_MODULE(Controller)
{
	// external inputs
	sc_in<sc_logic>	rst, clk;
	sc_in<sc_logic> go;						// start calculations
		
	// external outputs
	sc_out<sc_logic> ready;					// result is ready

	// internal inputs
	sc_in<sc_logic>	coC;
		
	// internal outputs
	sc_out<sc_logic> in0C, incC;			// in0C - parallel load of 0x00 (init counter), incC - count enable
	sc_out<sc_logic> ldx;					// ldx - load X
	sc_out<sc_logic> ldT, in1T;				// ldT - load term, in1T - init term
	sc_out<sc_logic> ldR, in1R;				// ldR - load result, in1R - init result

	// present/next state of Huffman finite state machine (FSM)
	enum states {IDLE, LOAD, TERM, RES};
	sc_signal<states> p_state, n_state;

	// constructor
	SC_CTOR(Controller)
	{
		// initialize the FSM
		p_state.write(IDLE);
		n_state.write(IDLE);
		
		// combinational part of Huffman model
		SC_METHOD(evl_comb_states);
			sensitive << go << coC << p_state;
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

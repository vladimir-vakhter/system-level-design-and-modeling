#include <systemc.h>

template <int T> SC_MODULE (Mult) {
	sc_in <sc_lv<T>>		in1, in2;
	sc_out <sc_lv<2*T>>		out; 

	SC_CTOR (Mult)
	{
		SC_METHOD (multiplying); 
			sensitive << in1 << in2; 
	}

	void multiplying() 
	{
		sc_lv <T*2> vout;
		vout = (sc_uint<T>)in1 * (sc_uint<T>)in2;
		out = vout;
	}
};

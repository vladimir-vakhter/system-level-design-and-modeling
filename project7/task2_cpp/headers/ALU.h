#pragma once
#include "classVectorPrimitives.h"

class ALU
{
public:
	ALU(bus &A, bus	&B, bus &F, bus	&W, bus &c, bus &g);
	~ALU();
	void evl();

private:
	// external buses
	bus *A, *B;		// 8-bit inputs
	bus *F;			// 2-bit opcode: 00 - W=(A+B), 01 - W=max(A,B), 10 - W=0, 11 - W=A|B
	bus *W;			// 8-bit output
	bus *c;			// carry-out for arithmetic operations
	bus *g;			// greater: A>B

	// internal buses
	bus *ci;		// carry-in of the adder
	bus *sum;		// output of the adder
	bus *a_eq_b;	// output '=' of the comparator
	bus *a_less_b;	// ouptut '<' of the comparator
	bus *or_out;	// result of A|B
	bus *max;		// output of MUX1
	bus *zero;		// input 10 of MUX2
	bus *res_in1;	// result input 1
	bus *res_in2;	// result input 2
	bus *sel1;		// select mux2, mux3
	bus *sel2;		// select mux4

	// components
	Adder		*adder;
	Comparator	*comparator;
	Mux			*mux1;
	Mux			*mux2;
	Mux			*mux3;
	Mux			*mux4;
};

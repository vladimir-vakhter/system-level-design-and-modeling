#pragma once
#include "ALU.h"

ALU::ALU
(bus& A, bus& B, bus& F, bus& W, bus& c, bus& g) :
A(&A), B(&B), F(&F), W(&W), c(&c), g(&g)
{
	// initialize internal buses
	ci			= new bus("0");
	sum			= new bus("00000000");
	a_eq_b		= new bus("0");
	a_less_b	= new bus("0");
	or_out		= new bus("00000000");
	max			= new bus("00000000");
	zero		= new bus("00000000");
	res_in1		= new bus("00000000");
	res_in2		= new bus("00000000");
	sel1		= new bus("0");
	sel2		= new bus("0");

	// wire components
	adder		= new Adder(A, B, *ci, c, *sum);
	comparator	= new Comparator(A, B, *a_less_b, *a_eq_b, g);
	mux1		= new Mux(A, B, *a_less_b, *max);
	mux2		= new Mux(*sum, *max, *sel1, *res_in1);
	mux3		= new Mux(*zero, *or_out, *sel1, *res_in2);
	mux4		= new Mux(*res_in1, *res_in2, *sel2, W);
}

void ALU::evl()
{
	// addition
	adder->evl();
	// comparison
	comparator->evl();
	mux1->evl();
	// OR
	*or_out = *A|*B;
	// intemediate results
	*sel1 = F->at(0);
	mux2->evl();
	mux3->evl();
	// final result
	*sel2 = F->at(1);
	mux4->evl();
}

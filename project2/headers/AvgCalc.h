#pragma once
#include "polymorphismLogicClassesPrimitives.h"
//#define DEBUG

class AvgCalc
{
public:
	AvgCalc(Wire& start, Wire& clk, WireV& data, WireV& avg, Wire& rdy);
	~AvgCalc();
	void evl();

	// external wires
	Wire	*start, *clk;									// inputs
	WireV	*data;
	
	Wire	*rdy;											// outputs
	WireV	*avg;

	// internal components
	FullAdder	*fa0, *fa1, *fa2, *fa3, *fa4, *fa5,			// full-adders
				*fa6, *fa7, *fa8, *fa9, *faA;

	Flipflop	*dff0, *dff1, *dff2, *dff3, *dff4, *dff5,	// flip-flops
				*dff6, *dff7, *dff8, *dff9, *dffA;

	// internal wires
	Wire *a0L, *a1L, *a2L, *a3L, *a4L, *a5L, *a6L, *a7L, *a8L, *a9L, *aAL;						 // connect Q-outputs of FFs with the A-inputs of FAs
	Wire *sum0L, *sum1L, *sum2L, *sum3L, *sum4L, *sum5L, *sum6L, *sum7L, *sum8L, *sum9L, *sumAL; // connect Sum outputs of FAs with D inputs of FFs
	Wire *ci0L, *co0L, *co1L, *co2L, *co3L, *co4L, *co5L, *co6L, *co7L, *co8L, *co9L, *coAL;	 // connect carry-in and carry-out pins of FAs
	Wire *data0L, *data1L, *data2L, *data3L, *data4L, *data5L, *data6L, *data7L;				 // connect input 8-bit data with the B-inputs of FAs
	Wire *b8L, *b9L, *bAL;																		 // connected to the B-inputs of the most significant FAs

private:
	int		counter;			// internal counter of input bytes
	
	string	data_content;		// the content of input 8-bit data
	int		data_event_time;	// the time of the occurence of input 8-bit data 
	
	string	avg_content;		// the content of average
	int		avg_event_time;		// the time when average is issued to the output
};


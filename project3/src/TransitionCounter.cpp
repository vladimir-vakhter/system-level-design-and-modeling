#pragma once;
#include "TransitionCounter.h"

TransitionCounter::TransitionCounter
(bus& rst, bus& clk, bus& start, bus& end, bus& J, bus& transition_count) :
rst(&rst), clk(&clk), start(&start), end(&end), J(&J), transition_count(&transition_count)
{
	count_en = new bus("X");

	CU = new Controller(rst, clk, start, end, *count_en);
	DP = new Datapath(rst, clk, J, *count_en, transition_count);
}

void TransitionCounter::evl() {
	CU->evl();
	DP->evl();
}
void TransitionCounter::init()
{
	// reset
	*rst = "1";
	evl();
	*rst = "0";
}

#pragma once
#include "Controller.h"
#include "Datapath.h"

class TransitionCounter
{
public:
	TransitionCounter(bus& rst, bus& clk, bus& start, bus& end, bus& J, bus& transition_count);
	~TransitionCounter();
	void evl();
	void init();

private:
	// external buses
	bus *clk, *rst, *start, *end, *J, *transition_count;

	// local buses
	bus *count_en;

	// instances
	Controller	*CU;
	Datapath	*DP;
};

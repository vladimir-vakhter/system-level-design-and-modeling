#pragma once
#include "classVectorPrimitives.h"

class Datapath
{
public:
	Datapath(bus &rst, bus& clk, bus &J, bus& en2, bus &transition_count);
	~Datapath();
	void evl();

private:
	// external buses
	bus *clk, *rst, *J, *en2, *transition_count;

	// internal buses
	bus *q1, *q2, *en1, *en;
	bus *load, *data;

	// components
	dRegisterRa		*regPosedge;
	dRegisterRa		*regNegedge;
	upCounterRaE	*transitionCounter;
};

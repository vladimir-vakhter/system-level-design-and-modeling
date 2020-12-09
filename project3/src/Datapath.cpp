#pragma once
#include "Datapath.h"

Datapath::Datapath
(bus& rst, bus& clk, bus& J, bus& en2, bus& transition_count) :
clk(&clk), rst(&rst), J(&J), en2(&en2), transition_count(&transition_count)
{
	// initialize internal buses
	load = new bus("0");
	data = new bus("00000000");
	q1	 = new bus("0");
	q2	 = new bus("0");
	en1  = new bus(1);
	en	 = new bus(1);

	*en1 = *q1 ^ *q2;
	*en  = *en1 & *(this->en2);

	// wire components
	regPosedge = new dRegisterRa(J, clk, rst, *q1);
	regNegedge = new dRegisterRa(*q1, clk, rst, *q2);

	transitionCounter = new upCounterRaE(*data, clk, rst, *load, *en, transition_count);
}

void Datapath::evl()
{
	regNegedge->evl();
	regPosedge->evl();
	*en1 = *q1 ^ *q2;
	*en = *en1 & *en2;
	transitionCounter->evl();
}

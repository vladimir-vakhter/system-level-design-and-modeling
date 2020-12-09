#pragma once;
#include "Controller.h"

Controller::Controller
(bus& rst, bus& clk, bus& start, bus& end, bus& count_en) :
rst(&rst), clk(&clk), start(&start), end(&end), count_en(&count_en)
{
	Pstate = 0;
	Nstate = 0;

	// assign output
	this->count_en->fill('0');
}

void Controller::evl()
{
	// next state logic
	switch (Pstate) {
	case 0:	// start
		if (start->at(0) == "1") Nstate = 1;
		else Nstate = 0;
		break;
	case 1:	// wait_start
		if (start->at(0) == "0") Nstate = 2;
		else Nstate = 1;
		break;
	case 2:	// count
		if (end->at(0) == "1") Nstate = 3;
		else Nstate = 2;
		break;
	case 3: // end
		if (end->at(0) == "0") Nstate = 0;
		else Nstate = 3;
		break;
	}
	
	// output logic
	if (Pstate == 2 || Pstate == 3) count_en->fill('1');
	else count_en->fill('0');

	// transition between states
	if (rst->at(0) == "1") Pstate = 0;					// async reset
	else if (clk->at(0) == "P") Pstate = Nstate;
}

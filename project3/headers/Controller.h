#include "classVectorPrimitives.h"

class Controller
{
public:
	Controller(bus &rst, bus &clk, bus &start, bus &end, bus &count_en);
	~Controller();
	void evl();
	
	// external buses
	bus *rst, *clk, *start, *end, *count_en;

private:
	int Pstate, Nstate;
};

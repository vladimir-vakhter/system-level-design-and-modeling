#pragma once
#include "initiatorsTargets.h"

SC_MODULE(sharedSwitch_tb2) {

	sharedSwitch<sc_lv<8>, 4, 4>* switchA;

	initiator<0, 3>* INI0;
	initiator<1, 3>* INI1;
	initiator<2, 4>* INI2;
	initiator<3, 3>* INI3;

	target<0, 7>* TAR0;
	target<1, 4>* TAR1;
	target<2, 6>* TAR2;
	target<3, 5>* TAR3;

	SC_CTOR(sharedSwitch_tb2) {
		switchA = new sharedSwitch<sc_lv<8>, 4, 4>;

		INI0 = new initiator<0, 3>("Initiator0");
		INI0->out(*switchA);
		INI1 = new initiator<1, 3>("Initiator1");
		INI1->out(*switchA);
		INI2 = new initiator<2, 4>("Initiator2");
		INI2->out(*switchA);
		INI3 = new initiator<3, 3>("Initiator3");
		INI3->out(*switchA);

		TAR0 = new target<0, 7>("Target0");
		TAR0->in(*switchA);
		TAR1 = new target<1, 4>("Target1");
		TAR1->in(*switchA);
		TAR2 = new target<2, 6>("Target2");
		TAR2->in(*switchA);
		TAR3 = new target<3, 5>("Target3");
		TAR3->in(*switchA);
	}
};

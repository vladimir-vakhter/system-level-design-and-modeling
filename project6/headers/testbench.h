#pragma once
#include "initiator.h"
#include "interconnect.h"
#include "target.h"

SC_MODULE (Testbench) {
	Initiator		*initiator[2];
	Interconnect	*interconnect;
	Target			*target;

	SC_CTOR(Testbench)
		{
			// initiator 0
			initiator[0] = new Initiator("initiator_1");
			initiator[0]->setNumber(0);
			// initiator 1
			initiator[1] = new Initiator("initiator_2");
			initiator[1]->setNumber(1);
			// interconnect
			interconnect = new Interconnect("interconnect");
			// target
			target = new Target("target");
			// bind ports
			initiator[0]->initiator_socket.bind(interconnect->target_socket_1);
			initiator[1]->initiator_socket.bind(interconnect->target_socket_2);
			interconnect->initiator_socket.bind(target->memSideSocket );
	}
};

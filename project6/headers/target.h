#pragma once
#include <systemc.h>
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"
#include "tlm_utils/simple_initiator_socket.h"

SC_MODULE (Target) {
	tlm_utils::simple_target_socket<Target> memSideSocket;

	static const int SIZE=256;

	SC_CTOR(Target) : memSideSocket("memorySideSocket")
	{
			// target implements the blocking transport method
			memSideSocket.register_b_transport(this, &Target::b_transport);

			for (int i = 0; i < SIZE; i++) {
				memArray[i] = (sc_lv<8>) (i % 256 + 192);
			}
	}
public:
	virtual void b_transport( tlm::tlm_generic_payload&, sc_time&);		// blocking transport method
	sc_lv<8> memArray[SIZE];											// memory array
};

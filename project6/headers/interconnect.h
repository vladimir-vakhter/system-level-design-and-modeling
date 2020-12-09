#pragma once
#include <systemc.h>
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"
#include "tlm_utils/simple_initiator_socket.h"

SC_MODULE(Interconnect) {
	tlm_utils::simple_target_socket<Interconnect>		target_socket_1;		// connect initiator 1
	tlm_utils::simple_target_socket<Interconnect>		target_socket_2;		// connect initiator 2
	tlm_utils::simple_initiator_socket<Interconnect>	initiator_socket;		// connect target

	SC_CTOR(Interconnect) : initiator_socket("initiator_socket"), target_socket_1("target_socket_1"),
							target_socket_2("target_socket_2"), blockWriteReadTransaction(0)
	{
		// register callback for incoming b_transport interface method call
		target_socket_1.register_b_transport(this, &Interconnect::b_transport);
		target_socket_2.register_b_transport(this, &Interconnect::b_transport);

		// initialize the genetric payload transaction
		blockWriteReadTransaction = new tlm::tlm_generic_payload;
	}
	// the genetric payload transaction
	tlm::tlm_generic_payload* blockWriteReadTransaction;

public:
	virtual void b_transport(tlm::tlm_generic_payload&, sc_time&);		// TLM-2 blocking transport method
private:
	sc_mutex targetBusy;												// controls access to the target
};

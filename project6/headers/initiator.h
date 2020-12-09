#pragma once
#include <systemc.h>
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"
#include "tlm_utils/simple_initiator_socket.h"

class Initiator : public sc_module {
public:
	tlm_utils::simple_initiator_socket<Initiator> initiator_socket;
	
	SC_CTOR(Initiator) : initiator_socket("Writer-Socket"), blockWriteReadTransaction(0), initiator_number(0)
	{
		// initialize the genetric payload transaction
		blockWriteReadTransaction = new tlm::tlm_generic_payload;
		// generate data
		for (int i = 0; i < 4; i++) *(data+i) = i+192;
		// start a thread that generates a stream of generic payload transactions
		SC_THREAD(memWritingReading);
	}
	
	inline void setNumber(int num) { initiator_number = num; }
	void memWritingReading();									// stream of generic payload transactions
	tlm::tlm_generic_payload	*blockWriteReadTransaction;		// generic payload transaction
	sc_lv<8>					data[5];						// data buffer
protected:
	int initiator_number;										// the number of initiator
};

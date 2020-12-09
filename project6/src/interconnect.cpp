#include "interconnect.h"

void Interconnect::b_transport(tlm::tlm_generic_payload& gotThis, sc_time& delay)
{
	// synchronize access to the target
	targetBusy.lock();
		// implement delays
		sc_time blockedTime = sc_time(9, SC_NS);
		sc_time pauseTime	= sc_time(12, SC_NS);

		// pass through the generic payload transaction to the target
		blockWriteReadTransaction = &gotThis;
		initiator_socket->b_transport(*blockWriteReadTransaction, blockedTime);

		// check response from target
		if (blockWriteReadTransaction->is_response_error())
			SC_REPORT_ERROR("TLM-2", "Error in memory handling of b_transport");

		// extract the command from generic payload transaction
		tlm::tlm_command cmd = gotThis.get_command();

		cout << "\nInterconnect:";
		cout << "\tat: " << sc_time_stamp() << ",\tpassed through " << (cmd ? "Write cmd\n" : "Read cmd\n");

		// indicate the successful completion of the transaction for the initiator
		gotThis.set_response_status(tlm::TLM_OK_RESPONSE);
		wait(delay);
	// unlock target
	targetBusy.unlock();
}

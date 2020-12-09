#include "target.h"

void Target::b_transport(tlm::tlm_generic_payload& transaction, sc_time& delay)
{
	// extract the attributes from generic payload transaction
	tlm::tlm_command cmd = transaction.get_command();
	uint64			 adr = transaction.get_address();
	unsigned char*   ptr = transaction.get_data_ptr();
	unsigned int     len = transaction.get_data_length();
	unsigned char*   byt = transaction.get_byte_enable_ptr();
	unsigned int     wid = transaction.get_streaming_width();

	// check that initiator set the attributes which are supported by target
 	if (adr >= uint64(SIZE) || byt != 0 || len > 5 || wid < len)
		SC_REPORT_ERROR("TLM-2.0: ","Inconsistant generic payload");

	// implement the read and write commands
	unsigned int i;
	if (cmd == tlm::TLM_READ_COMMAND) {
		for(i = 0; i < len; i++) { 
			*(ptr+i) = *((unsigned char*) (memArray+adr+i));
		}			
	}
	else if (cmd == tlm::TLM_WRITE_COMMAND) {
		for(i = 0; i < len; i++) {
			*((unsigned char*) (memArray+adr+i)) = *(ptr+i);
		}
	}
	
	// indicate the successful completion of the transaction
 	transaction.set_response_status(tlm::TLM_OK_RESPONSE);
	wait(delay);
}

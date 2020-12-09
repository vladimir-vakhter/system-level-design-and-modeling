#include "initiator.h"

void Initiator::memWritingReading(){		
	sc_time delay = sc_time(13, SC_NS);
	sc_time pause = sc_time(15, SC_NS);

	for (int i = 0; i < 111; i += 11) {
		tlm::tlm_command cmd = (tlm::tlm_command)(rand() % 2);	// read or write
		if (cmd == tlm::TLM_WRITE_COMMAND) {
			data[0] = (sc_lv<8>) (i+5);
			data[1] = (sc_lv<8>) (i+6);
			data[2] = (sc_lv<8>) (i+7);
			data[3] = (sc_lv<8>) (i+8);
			data[4] = (sc_lv<8>) (i+9);
		}
		
		// set attributes for generic payload transaction
		blockWriteReadTransaction->set_command( cmd );
		blockWriteReadTransaction->set_address( i );
		blockWriteReadTransaction->set_data_ptr( (unsigned char*) data );
		blockWriteReadTransaction->set_data_length( 5 );     
		blockWriteReadTransaction->set_streaming_width( 5 ); 
		blockWriteReadTransaction->set_byte_enable_ptr( 0 ); 
		blockWriteReadTransaction->set_dmi_allowed( false ); 
		blockWriteReadTransaction->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE );	// the response status may be set by the target

		// send transaction through the socket using blocking transport interface
		initiator_socket->b_transport( *blockWriteReadTransaction, delay ); 
		
		if (blockWriteReadTransaction->is_response_error())
			SC_REPORT_ERROR("TLM-2", "Error in memory handling of b_transport");

		cout << "Initiator " << initiator_number << ":";
		cout << "\tat: " << sc_time_stamp() << (cmd ? ",\tWrites" : ",\tReads") 
			 << ",\tIteration: " << i << "\tdata:";
		sc_lv<8> vv; 
		for(int j=0; j<5; j++) {
			vv = data[j]; 
			cout << vv << " ";
		}
		cout << '\n'; 
		wait(pause);
	}
}

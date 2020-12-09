#pragma once
#include "sharedSwitchChannel.h"

template <int N, int F>
SC_MODULE (initiator) {
	sc_port<put_if<sc_lv<8>>> out;

	SC_CTOR(initiator) {
		SC_THREAD (putting);
	}
	void putting();
};

template <int N, int F>
void initiator<N, F>::putting() {
	int toTarget;
	sc_lv<8> transmittedData;
	//ofstream fout("multiway_shared_switch_report.txt", ios::app);

	for (int i = (N * 16); i < (N * 16 + 15); i++)
	{
		wait(F, SC_NS);
		transmittedData = (sc_lv<8>) i;
		toTarget = rand() % 4; // Total 4 targets

		cout << "\nInitiator {" << N << "} intends to"
			 << " transmit (" << transmittedData << ") at: "
			 << sc_time_stamp() << " to: [" << toTarget << "]\n";

		out->put(N, toTarget, transmittedData);
		cout << "Initiator {" << N << "} completed transmitting (" 
			 << transmittedData << ") at: "
			 << sc_time_stamp() << " to: [" << toTarget << "]\n";
	}
}

template <int N, int F>
SC_MODULE(target) {
	sc_port<get_if<sc_lv<8>>> in;

	SC_CTOR(target) {
		SC_THREAD (getting);
    }
	void getting();
};

template <int N, int F>
void target<N, F>::getting() {
	sc_lv<8> receivedData[2];
	int dataInitiator[2];
	//ofstream fout("multiway_shared_switch_report.txt", ios::app);

	while (1)
	{
		dataInitiator[0] = -1;
		dataInitiator[1] = -1;
		
		wait(F, SC_NS); 

		cout << "Target [" << N << "] ready to" << " receive something at: "
			 << sc_time_stamp() << '\n';

		in->get(dataInitiator, N, receivedData);
		if (dataInitiator[0] != -1) {
			cout << "Target [" << N << "] received (" << receivedData[0] << ") at: "
				<< sc_time_stamp() << " from: {" << dataInitiator[0] << "}\n";

			if (dataInitiator[1] != -1) {
				cout << "Target [" << N << "] received (" << receivedData[1] << ") at: "
					<< sc_time_stamp() << " from: {" << dataInitiator[1] << "}\n";
			}
		}
		
	}
}

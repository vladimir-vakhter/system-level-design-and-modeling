#pragma once
#include "interfaces.h"

#define BUS_NUM 4	// number of buses

template <class T, int nI, int nT>
class sharedSwitch : public put_if<T>, public get_if<T>
{
	// initiators, transmitted data, targets
	int	initiators[BUS_NUM];
	T	txData[BUS_NUM];
	int targets[BUS_NUM];

	// events
	sc_event dataAvailable[nT];
	sc_event dataReceived[nI];

	// mutexes (buses)
	sc_mutex busBusy[BUS_NUM];

	public:
		sharedSwitch() : initiators{-1,-1,-1,-1}, targets{-1,-1,-1,-1} {};
		~sharedSwitch() {};

		void put(int initiator, int target, T data){
			bool transmitted = false;
			// look for an available bus
			while (!transmitted) {
				if (busBusy[0].trylock() != -1) {			// non-blocking			
					initiators[0] = initiator;
					targets[0] = target;
					txData[0] = data;
					dataAvailable[target].notify();
					wait(dataReceived[initiator]);
					transmitted = true;
					busBusy[0].unlock();
				} else if (busBusy[1].trylock() != -1) {	
					initiators[1] = initiator;
					targets[1] = target;
					txData[1] = data;
					dataAvailable[target].notify();
					wait(dataReceived[initiator]);
					transmitted = true;
					busBusy[1].unlock();
				} else if (busBusy[2].trylock() != -1) {	
					initiators[2] = initiator;
					targets[2] = target;
					txData[2] = data;
					dataAvailable[target].notify();
					wait(dataReceived[initiator]);
					transmitted = true;
					busBusy[2].unlock();
				} else if (busBusy[3].trylock() != -1) {	
					initiators[3] = initiator;
					targets[3] = target;
					txData[3] = data;
					dataAvailable[target].notify();
					wait(dataReceived[initiator]);
					transmitted = true;
					busBusy[3].unlock();
				}
			}
		}

		void get(int *initiator, int target, T *data)
		{
			int dataCounter = 0;

			// wait for data
			if ((targets[0] != target) && (targets[1] != target) &&
				(targets[2] != target) && (targets[3] != target)) {
				wait(dataAvailable[target]);
			}

			// process data from 2 initiators
			if (targets[0] == target) {
				initiator[0] = initiators[0];
				data[0] = txData[0];
				initiators[0] = -1;
				targets[0] = -1;
				dataReceived[initiator[0]].notify();
				dataCounter++;
			}

			if (targets[1] == target) {
				if (dataCounter == 0) {
					initiator[0] = initiators[1];
					data[0] = txData[1];
				} else {
					initiator[1] = initiators[1];
					data[1] = txData[1];
				}
				initiators[1] = -1;
				targets[1] = -1;
				if (dataCounter == 0) {
					dataReceived[initiator[0]].notify();
				} else {
					dataReceived[initiator[1]].notify();
				}
				dataCounter++;
			}

			if (dataCounter != 2) {
				if (targets[2] == target) {
					if (dataCounter == 0) {
						initiator[0] = initiators[2];
						data[0] = txData[2];
					} else {
						initiator[1] = initiators[2];
						data[1] = txData[2];
					}
					initiators[2] = -1;
					targets[2] = -1;
					if (dataCounter == 0) {
						dataReceived[initiator[0]].notify();
					} else {
						dataReceived[initiator[1]].notify();
					}
					dataCounter++;
				}
			}

			if (dataCounter != 2) {
				if (targets[3] == target) {
					if (dataCounter == 0) {
						initiator[0] = initiators[3];
						data[0] = txData[3];
					} else {
						initiator[1] = initiators[3];
						data[1] = txData[3];
					}
					initiators[3] = -1;
					targets[3] = -1;
					if (dataCounter == 0) {
						dataReceived[initiator[0]].notify();
					} else {
						dataReceived[initiator[1]].notify();
					}
					dataCounter++;
				}
			}
		}
};

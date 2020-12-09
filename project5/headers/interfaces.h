#pragma once
#include <systemc.h>

template <class T>
class put_if : virtual public sc_interface
{
	public:
		virtual void put(int initiator, int target, T data) = 0;
};

template <class T>
class get_if : virtual public sc_interface
{
   public:
	   virtual void get(int *initiator, int target, T *data) = 0;
};

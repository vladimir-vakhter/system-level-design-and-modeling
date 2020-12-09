#include "sharedSwitch_tb1.h"
#include "sharedSwitch_tb2.h"

//#define TB1
#define TB2

int sc_main (int argc , char *argv[]) {

	#ifdef TB1
	sharedSwitch_tb1 MultiWay("sharedSwitch_1");
	#endif // TB1

	#ifdef TB2
	sharedSwitch_tb2 MultiWay("sharedSwitch_2");
	#endif // TB2

   //sharedSwitch_tb MultiWay("sharedBusPutGet1");
   sc_start();
   return 0;
}

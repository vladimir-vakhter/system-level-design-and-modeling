#pragma once
#include "polymorphismLogicClassesFunctions.h"

class Wire {
protected:
	static int numberOfWires;
public:
	char value;						// the value
	int eventTime;					// the time when an event occurs on the wire
	int activityCount = 0;			// how many times the wire changed its value - for the power consumption calculation
	float controlability = 0.5;		// 
public:
	int wireIdentifier;	
	Wire(char c, int d) : value(c), eventTime(d) {
		wireIdentifier = numberOfWires;
		numberOfWires++;
	}
	Wire(){};
	void put(char a, int d) { value = a; eventTime = d; }
	void get(char& a, int& d) { a = value; d = eventTime; }
	int activity() { return activityCount; }
};

class Gates {
protected:
	Wire *i1, *i2, *o1;
	int gateDelay, lastEvent;		// last event - the time of last event
	char lastValue;

	void timingActivity2();
	void timingActivity1();
	static int numberOfGates;
public:
	int gateIdentifier;
	float outputControlability = 1.0; 
	Gates(Wire& a, Wire& w, int d) : 
		i1(&a), o1(&w), gateDelay(d) {
		gateIdentifier = numberOfGates;
		numberOfGates++;
	}
	Gates(Wire& a, Wire& b, Wire& w, int d) : 
		i1(&a), i2(&b), o1(&w), gateDelay(d) {
		gateIdentifier = numberOfGates;
		numberOfGates++;
	}
	Gates(){};
	~Gates(){};
	virtual void evl();
	virtual void prob(){};		// probability (controlability evaluation)
};

float getProb(Gates*);
float evl(Gates*);

class And: public Gates {
public:
	And(Wire& a, Wire& b, Wire& w, int d) : Gates(a, b, w, d) {}
	~And();
	void evl();
	void prob();
};

class Or: public Gates {
public:
	Or(Wire& a, Wire& b, Wire& w, int d) : Gates(a, b, w, d) {}
	~Or();
	void evl();
	void prob();
};

class Not: public Gates {
public:
	Not(Wire& a, Wire& w, int d) : Gates(a, w, d) {}
	~Not();
	void evl();
	void prob();
};

class Xor: public Gates {
public:
	Xor(Wire& a, Wire& b, Wire& w, int d) : Gates(a, b, w, d) {}
	~Xor();
	void evl();
	void prob();
};

class Flipflop {
protected:
	Wire *D, *clk, *rst, *cen, *Q;
	int clkQDelay;
	int rstQDelay;
	int lastEvent; // last time output changed
	char lastValue;
	bool containsReset = false;
	float clockControlability = 0.5;
	static int numberOfFlipflops; 
public:
	int flipflopIdentifier;
	float outputControlability = 1.0;
	Flipflop(Wire& d, Wire& c, Wire& q, int dC) :
		D(&d), clk(&c), Q(&q), clkQDelay(dC) {
		flipflopIdentifier = numberOfFlipflops;
		numberOfFlipflops++;
	};
	~Flipflop(){};
	virtual void evl() = 0;						// pure virtual
	virtual void prob() = 0;					// anybody who inherits is required to define these functions
	virtual void init(float, char) = 0;
};

class Dff : public Flipflop {
public:
	Dff(Wire& d, Wire& c, Wire& q, int dC) : Flipflop(d, c, q, dC) 
	{ containsReset = false; };
	~Dff(){};
	virtual void evl();
	virtual void prob();
	virtual void init(float, char);
};

class DffSR : public Dff {
public:
	DffSR(Wire& d, Wire& c, Wire& r, Wire& q, int dC, int dR) : Dff(d, c, q, dC) {
		containsReset = true;
		rst = &r;
		rstQDelay = dR;
	};
	~DffSR(){};
	virtual void prob();
};

class DffSRE : public DffSR {
public:
	DffSRE(Wire& d, Wire& c, Wire& r, Wire& e, 
		Wire& q, int dC, int dR) : DffSR(d, c, r, q, dC, dR) {
		cen = &e;
	};
	~DffSRE(){};
	virtual void evl();
};


// Structures based on above primitives begin here

class FullAdder {
	Wire *i1, *i2, *i3, *o1, *o2;	// a, b, ci, co, sum

	// Declare necessary gate instances
	Gates *xor1;
	Gates *xor2;
	Gates *and1;
	Gates *and2;
	Gates  *or1;
	
	// fulladder Local wires
	Wire aL, bL, ciL;
	Wire coL, sumL;
	Wire axbL, abL, abcL;

public:
	float o1Controlability, o2Controlability;
	
	FullAdder(Wire& a, Wire& b, Wire& ci, Wire& co, Wire& sum) :
			i1(&a), i2(&b), i3(&ci), o1(&co), o2(&sum),  
			aL('X', 0), bL('X', 0), ciL('X', 0),
			coL('X', 0), sumL('X', 0), 
			axbL('X', 0), abL('X', 0), abcL('X', 0) {

		// Associate ports of the gates with the Local FA wires
		xor1 = new Xor(aL, bL, axbL, 5); // 5 is gate delay
		xor2 = new Xor(axbL, ciL, sumL, 5);
		and1 = new And(aL, bL, abL, 3);
		and2 = new And(axbL, ciL, abcL, 3);
		or1 = new Or(abL, abcL, coL, 3);
		};
		~FullAdder(); 
		void evl();
		void prob();
};

class HalfAdder {
	Wire *i1, *i2, *o1, *o2;

	// Declare necessary gate instances
	Gates *xor1;
	Gates *and1;

	float o1Controlability, o2Controlability;

	// halfadder Local wires
	Wire aL, bL;
	Wire coL, sumL;

	public:
		HalfAdder(Wire& a, Wire& b, Wire& co, Wire& sum) :
			i1(&a), i2(&b), o1(&co), o2(&sum), 
			aL('X', 0), bL('X', 0), coL('X', 0), sumL('X', 0){
			
		// Associate ports of the gates with the Local HA wires
		xor1 = new Xor(aL, bL, sumL, 5);
		and1 = new And(aL, bL, coL, 3);

		};
		~HalfAdder(); 
		void evl();
		void prob();
};

// -----------------Vector Logic---------------- //

class WireV {
public:
	char* value;
	int n; //Bits
	int eventTime;
	int activityCount = 0;
public:
	WireV(string v, int d, int size);
	WireV(){};
	~WireV(){};
	void put(string a, int d);
	void get(string& a, int& d);
	int activity() { return activityCount; }
};

class AndV {
	WireV *i1, *i2, *o1;
	int gateDelay, lastEvent;
	char* lastValue;
public:
	AndV(WireV& a, WireV& b, WireV& w, int d) :
		i1(&a), i2(&b), o1(&w), gateDelay(d) {
		lastValue = new char[w.n+1];
	};
	~AndV(){};
	void evl();
};

class OrV {
	WireV *i1, *i2, *o1;
	int gateDelay, lastEvent;
	char* lastValue;
public:
	OrV(WireV& a, WireV& b, WireV& w, int d) :
		i1(&a), i2(&b), o1(&w), gateDelay(d) {
		lastValue = new char[w.n + 1];
	};
	~OrV(){};
	void evl();
};


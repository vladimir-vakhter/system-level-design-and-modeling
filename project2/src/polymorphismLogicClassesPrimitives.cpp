#include "polymorphismLogicClassesPrimitives.h"
#include "polymorphismLogicClassesFunctions.h"

#define MAX(a,b) ((a>b)?a:b)

int calculateEventTime(char lastValue, char newValue,
	int in1LastEvent, int in2LastEvent, int gateDelay, int lastEvent){

	if (lastValue == newValue) 
		return lastEvent;
	else 
		return gateDelay + MAX (in1LastEvent, in2LastEvent);
}

int calculateEventTime(char lastValue, char newValue,
	int in1LastEvent, int gateDelay, int lastEvent){

	if (lastValue == newValue) 
		return lastEvent;
	else 
		return gateDelay + in1LastEvent;
}

int Wire::numberOfWires = 1;

void Gates::evl() { // puts input 1 on output
	o1->value = i1->value;
	Gates::timingActivity1();
}
void Gates::timingActivity2() {

	o1->eventTime = calculateEventTime(lastValue, o1->value,
		i1->eventTime, i2->eventTime, gateDelay, lastEvent);

	o1->activityCount = i1->activityCount + i2->activityCount +
		((lastValue == o1->value) ? 0 : 1);

	lastEvent = o1->eventTime;
	lastValue = o1->value;
}
void Gates::timingActivity1() {

	o1->eventTime = calculateEventTime(lastValue, o1->value,
		i1->eventTime, gateDelay, lastEvent);

	o1->activityCount = i1->activityCount + ((lastValue == o1->value)?0:1);

	lastEvent = o1->eventTime;
	lastValue = o1->value;
}
int Gates::numberOfGates=1;

float getProb(Gates* GATE){
	return GATE->outputControlability;
}

float evl(Gates* GATE){		// combined evl(), pointer compatibility
	GATE->evl();
	return GATE->outputControlability;
}

void And::evl() {

	if ((i1->value == '0') || (i2->value == '0'))
		o1->value = '0';
	else if ((i1->value == '1') && (i2->value == '1'))
		o1->value = '1';
	else
		o1->value = 'X';

	Gates::timingActivity2();
}
void And::prob() {
	outputControlability = i1->controlability * i2->controlability;
	o1->controlability = outputControlability;
}

void Or::evl() {

	if ((i1->value == '1') || (i2->value == '1')) 
		o1->value = '1';
	else if ((i1->value=='0')&&(i2->value=='0')) 
		o1->value='0';
	else 
		o1->value='X';

	Gates::timingActivity2();
}
void Or::prob() {
	outputControlability = i1->controlability + i2->controlability -
		                 i1->controlability * i2->controlability;
	o1->controlability = outputControlability;
}

void Not::evl() {

	if (i1->value == '0')
		o1->value = '1';
	else if (i1->value == '1')
		o1->value = '0';
	else
		o1->value = 'X';

	Gates::timingActivity1();
}
void Not::prob() {

	outputControlability = i1->controlability;
	o1->controlability = outputControlability;
}

void Xor::evl () {

	if ((i1->value == 'X') || (i2->value == 'X') ||
		(i1->value == 'Z') || (i2->value == 'Z')) 
		o1->value = 'X';
	else if (i1->value==i2->value) 
		o1->value='0';
	else 
		o1->value='1';

	Gates::timingActivity2();
}
void Xor::prob() {
	outputControlability = i1->controlability + i2->controlability -
						   2 * i1->controlability * i2->controlability;
	o1->controlability = outputControlability;
}

int Flipflop::numberOfFlipflops = 1;

void Dff::evl() {
	char valueToLoad = '0';

	if (!containsReset) valueToLoad = D->value;
	else valueToLoad = (rst->value == '1') ? '0' : D->value;

	if (clk->value == 'P') {
		Q->value = valueToLoad;		// sync reset (on posedge of clk)
		Q->eventTime = calculateEventTime(lastValue, Q->value,
			clk->eventTime, clkQDelay, lastEvent);
	}

	Q->eventTime = calculateEventTime(lastValue, Q->value,
		clk->eventTime, clkQDelay, lastEvent);

	Q->activityCount = (D->activityCount + clk->activityCount) * 2 +
		((lastValue == Q->value) ? 0 : 3);

	lastEvent = Q->eventTime;
	lastValue = Q->value;
}
void Dff::prob(){
	outputControlability = D->controlability * clockControlability;
	Q->controlability = outputControlability;
}
void Dff::init(float clkCon, char iniOut) {
	clockControlability = clkCon; Q->value = iniOut; 
}

void DffSR::prob(){
	outputControlability = (D->controlability + rst->controlability - 
							D->controlability * rst->controlability ) * 
							clockControlability;
	Q->controlability = outputControlability;
}

void DffSRE::evl() {
	if (cen->value == '1') DffSR::evl();
}

// Structures based on above primitives begin here

void FullAdder::prob(){

	// Calculate probabilities in the proper order
	xor1->prob();
	and1->prob();
	and2->prob();
	or1->prob();
	xor2->prob();

	o1Controlability = getProb(or1);
	o2Controlability = getProb(xor2);
}
void FullAdder::evl () {

	// Via the FA pointers, read wire values that connect to
	// the FA from outside, and assign them to FA Local wires
	aL = *i1; bL = *i2; ciL = *i3;

	// Evaluate gates in the proper order
	xor1->evl();
	and1->evl();
	and2->evl();
	or1->evl();
	xor2->evl();
		
	// Take calculated local wire values and assign the values 
	// to the outside wires via pointers of FA
	*o1 = coL; *o2 = sumL;
}


void HalfAdder::prob(){

	// Calculate probabilities in the proper order
	xor1->prob();
	and1->prob();

	o1Controlability = getProb(and1);
	o2Controlability = getProb(xor1);
}
void HalfAdder::evl() {
	
	// Via the HA pointers, read wire values that connect to
	// the HA from outside, and assign them to HA Local wires
	aL = *i1; bL = *i2; 

	// Calculate probabilities in the proper order
	and1->prob();
	xor1->prob();

	// Evaluate gates in the proper order
	and1->evl();
	xor1->evl();

	// Take calculated local wire values and assign the values 
	// to the outside wires via pointers of FA
	*o1 = coL; *o2 = sumL;
}

// --------------------- Vector Logics -------------------- //

WireV::WireV(string v, int d, int size) : eventTime(d), n(size) {
	int i;
	value = new char[n + 1];
	v.resize(n, 'X');
	for (i = 0; i < n; i++){ *(i + value) = v.at(i); };
	*(n + value) = '\0';
}
void WireV::put(string a, int d){
	int i;
	eventTime = d;
	a.resize(n, '0');
	for (i = 0; i < n; i++){ *(i + value) = a.at(i);};
}
void WireV::get(string& a, int& d){
	int i;
	d = eventTime;
	a.resize(n, '0');
	for (i = 0; i < n; i++){ a.at(i) = *(i + value); };
}

void AndV::evl() {
	int i = 0;

	while (i1->value[i] != '\0'){
		if (((i1->value[i]) == '0') || ((i2->value[i]) == '0'))
			o1->value[i] = '0';
		else if ((i1->value[i] == '1') && (i2->value[i] == '1'))
			o1->value[i] = '1';
		else
			o1->value[i] = 'X';
		i++;
	};
}

void OrV::evl() {
	int i = 0;
	while (i1->value[i] != '\0'){
//		if (((i1->value[i]) == '1') || ((i2->value[i]) == '1'))
		if ((*(i1->value + i) == '1') || (*(i2->value + i) == '1'))
			o1->value[i] = '1';
		else if ((i1->value[i] == '0') && (i2->value[i] == '0'))
			o1->value[i] = '0';
		else
			o1->value[i] = 'X';
		i++;
	};
}


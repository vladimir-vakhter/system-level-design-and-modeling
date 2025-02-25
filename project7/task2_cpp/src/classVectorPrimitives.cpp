#pragma once
#include "classVectorPrimitives.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;
Mux::Mux (bus& a, bus& b, bus& sel, bus& w) : i1(&a), i2(&b), i3(&sel), o1(&w) 
{
	o1->fill('X');
}
void Mux::evl () {
	if (*i3 == "0")	*o1 = *i1; else *o1 = *i2;
}

Tri::Tri (bus& a, bus& tri, bus& w) : i1(&a), i2(&tri), o1(&w) 
{
	o1->fill('X');
}
void Tri::evl () {
	if (*i2 == "1")	*o1 = *i1; else o1->fill('Z'); 
}

Adder::Adder(bus& a, bus& b, bus& ci, bus& co, bus& sum) :
			 i1(&a), i2(&b), i3(&ci), o1(&sum), o2(&co) 
{
	o1->fill('X'); o2->fill('X');
}
void Adder::evl () {
	bus result(i1->length() + 1);
	result = *i1 + *i2 + *i3;
	int leftIndex = result.length() - 1;
	*o2 = result.at(leftIndex);
	*o1 = result.range(leftIndex-1, 0);
}

Comparator::Comparator(bus& a, bus& b, bus& lt, bus& eq, bus& gt) :
			i1(&a), i2(&b), o1(&lt), o2(&eq), o3(&gt) 
{
	o1->fill('X'); o2->fill('X'); o3->fill('X');
}
void Comparator::evl () {
	if (*i1<*i2) {
		o1->fill('1'); o2->fill('0'); o3->fill('0');
	}
	else if (*i1==*i2) {
		o1->fill('0'); o2->fill('1'); o3->fill('0');
	}
	else {
		o1->fill('0'); o2->fill('0'); o3->fill('1');
	}
}

void nBitFunctionalRegister::info(bus& D, bus& C, bus& Q, int& N, string& typ){
	D = *d;
	C = *c;
	Q = *q;
	N= this->size;
	typ.assign(rtype);
}
void nBitFunctionalRegister::init(string typ){
	rtype = typ;
}

dRegister::dRegister(bus& di, bus& clk, bus& qo) {
	d = &di; 
	c = &clk;
	q = &qo;
	size = q->length();
	q->fill('X');
}
void dRegister::evl(){
	if (c->at(0) == "P") *q = *d;
}

dRegisterE::dRegisterE (bus& di, bus& clk, bus& en, bus& qo)
                       : dRegister (di,clk,qo) {
	e = &en;
}
void dRegisterE::evl(){
	if (e->at(0) == "1") dRegister::evl();
}
	
dRegisterRa::dRegisterRa (bus& di, bus& clk, bus& rst, bus& qo)
                         : dRegister (di,clk,qo) {
	r = &rst;
}
void dRegisterRa::evl(){
	if (r->at(0) == "1") q->fill('0');
	else dRegister::evl();
}
	
dRegisterRaE::dRegisterRaE (bus& di, bus& clk, bus& rst, bus& en, 
                            bus& qo) : dRegisterRa (di,clk,rst,qo) {
	e = &en;
}
void dRegisterRaE::evl(){
	if (r->at(0) == "1") q->fill('0');
	else if (e->at(0)=="1") dRegister::evl();
}
	
dRegisterRs::dRegisterRs (bus& di, bus& clk, bus& rst, bus& qo)
	                     : dRegister (di,clk,qo) {
	this->r = &rst;
}
void dRegisterRs::evl(){
	if ((r->at(0) == "1") && (c->at(0) == "P"))
	{
		q->fill('0');
	}
	else dRegister::evl();
}

dRegisterRsE::dRegisterRsE(bus& di, bus& clk, bus& rst, bus& en,
	bus& qo) : dRegisterRs(di, clk, rst, qo) {
	e = &en;
}
void dRegisterRsE::evl() {
	if ((r->at(0) == "1") && (c->at(0) == "P"))
	{
		q->fill('0');
	}
	else if (e->at(0) == "1") dRegister::evl();
}

dRegisterRsEinit::dRegisterRsEinit(bus& di, bus& clk, bus& rst, bus& en, bus& init,
	bus& initdata, bus& qo) : dRegisterRsE(di, clk, rst, en, qo) {
	this->init = &init;
	this->initdata = &initdata;
}
void dRegisterRsEinit::evl() {
	if ((r->at(0) == "1") && (c->at(0) == "P"))
	{
		q->fill('0');
	}
	else if ((init->at(0) == "1") && (c->at(0) == "P")) *q = *initdata;
	else if (e->at(0) == "1") dRegister::evl();
}

upCounter::upCounter (bus& di, bus& clk, bus& ld, bus& qo) : l(&ld) { 
	d = &di; 
	c = &clk;
	q = &qo;
	size = d->length();
	q->fill('X');
	internalCount = new bus(size, '0');
}
void upCounter::evl(){
	if (c->at(0)=="P") {
		if (l->at(0) == "1") *internalCount = *d;
		else {
			*internalCount = *internalCount + "1";
		}
	}
	*q = *internalCount;
}

upCounterRa::upCounterRa(bus& di, bus& clk, bus& rst, bus& ld,
	bus& qo) : upCounter(di, clk, ld, qo), r(&rst) { 
}
void upCounterRa::evl(){
	if (r->at(0) == "1") {
		q->fill('0');
		internalCount->fill('0');
	}
	else upCounter::evl();
}

upCounterRsE::upCounterRsE(bus& di, bus& clk, bus& rst, bus& ld,
	bus&en, bus& qo) : upCounter(di, clk, ld, qo), r(&rst), e(&en) {
}
void upCounterRsE::evl(){
	if ((r->at(0) == "1") && (c->at(0) == "P"))
	{
		q->fill('0');
		internalCount->fill('0');
	}
	else if (e->at(0) == "1") upCounter::evl(); 
}

upCounterRaE::upCounterRaE(bus& di, bus& clk, bus& rst, bus& ld,
	bus&en, bus&qo) : upCounterRa(di, clk, rst, ld, qo), e(&en) {
}

void upCounterRaE::evl(){
	if (r->at(0) == "1")
	{
		q->fill('0');
		internalCount->fill('0');
	}
	else if (e->at(0) == "1") upCounter::evl();
}

Memory::Memory (bus& rst, bus& clk, bus& read, bus& write,
	            bus& Din, bus& AddrBus, bus& Dout) :
	rst(&rst), read(&read), write(&write), clk(&clk), Din(&Din),
	AddrBus(&AddrBus), Dout(&Dout)
{
	this->Dout->fill('X');
	int LEN = this->Dout->length();
	int ADS = this->AddrBus->length();
	N = int(pow(2.0, ADS));

	mem = new bus[N];
	for (int i=0; i < N; i++) {
		mem[i].resize(LEN, '0'); 
	}
}
Memory::Memory (bus& rst, bus& clk, bus& read, bus& write,
				bus& Din, bus& AddrBus, bus& Dout, int SIZE) :
	rst(&rst), read(&read), write(&write), clk(&clk), Din(&Din),
	AddrBus(&AddrBus), Dout(&Dout)
{
	this->Dout->fill('X');

	int LEN = this->Dout->length();
	N = SIZE;

	mem = new bus[N];
	for (int i = 0; i < N; i++) {
		mem[i].resize(LEN, '0');
	}
}
void Memory::init (const string& filename){
	ifstream finp(filename);
	for (int i = 0; i < N; i++) {
		finp >> mem[i]; 
		cout << mem[i] << "\n";
	}
}
void Memory::dump (const string& filename){
	ofstream fout(filename);
	fout << "listing follows:\n";
	cout << "listing follows:\n";
	for (int i = 0; i < N; i++) {
		fout << i << ": " << mem[i] << "\n"; 
		cout << i << ": " << mem[i] << "\n"; 
	}
}
void Memory::evl () {
	if (rst->at(0) == "1") {
		for (int i = 0; i < N; i++) mem[i].fill('0');
	}
	else if (read->at(0) == "1") {
		*Dout = mem[AddrBus->ival()];
//		cout << "Memory read: @" << AddrBus->ival() << ": " << *Dout << "\n";
	}
	else if (clk->at(0) == "P") {
		if (write->at(0) == "1") {
			mem[AddrBus->ival()] = *Din;
//			cout << "Memory write: @" << AddrBus->ival() << ": " << *Din << "\n";
		}
	}
}

//#include "extraClassPrimitives.cpp"

////////////////////////////////// Somayeh inserted/////////////////////////////
bus bval(int a, int size) {
	bus result(size);
	for (int i = 0; i < size; i++)
	{
		if (a % 2 == 1) result[i] = '1';
		else result[i] = '0';
		a = a / 2;
	}
	return result;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Somayeh inserted////////////////////////////////
double fval(bus v)
{
	int aSize = v.length();
	double ia = 0.0;
	for (int i = 0; i < aSize; i++) {
		if (v.at(i) == "1") ia = ia + double(pow((2.0), (-1 * (aSize - i))));
	}
	return ia;
}

//////////////////

Multiplier::Multiplier(bus& a, bus& b, bus& sum) :
	i1(&a), i2(&b), o1(&sum)
{
	o1->fill('X');
}
void Multiplier::evl() {
	long int IResult;
	bus result(i1->length() * 2);
	IResult = i1->ival() * i2->ival();
	result = bval(IResult, i1->length() * 2);
	int leftIndex = result.length();
	*o1 = result.range(leftIndex - 1, 0);
}

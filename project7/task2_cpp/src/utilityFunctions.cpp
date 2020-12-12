#pragma once
#include "utilityFunctions.h"

char And(char a, char b)
{
	if ((a == '0') || (b == '0')) return '0';
	else if ((a == '1') && (b == '1')) return '1';
	else return 'X';
}

char Or(char a, char b)
{
	if ((a == '1') || (b == '1')) return '1';
	else if ((a == '0') && (b == '0')) return '0';
	else return 'X';
}

char Not(char a)
{
	if (a == '1') return '0';
	else if (a == '0') return '1';
	else return 'X';
}

char Tri(char a, char c)
{
	if (c == '1') return a;
	else return 'Z';
}

char Resolve(char a, char b)
{
	if (a == 'Z' || a == b) return b;
	else if (b == 'Z') return a;
	else return 'X';
}

char Xor(char a, char b)
{
	if ((a == 'X') || (b == 'X') || (a == 'Z') || (b == 'Z')) return 'X';
	else if (a == b) return '0';
	else return '1';
}

void FullAdder(char a, char b, char ci, char & co, char & sum)
{
	char axb, ab, abc;

	axb	= Xor(a, b);
	ab	= And(a, b);
	abc = And(axb, ci);
	co	= Or(ab, abc);
	sum = Xor(axb, ci);
}

//============================================================================
// Name        : main.cpp
// Author      : HRUSTIC Emir
// Version     :
// Copyright   :
// Description : Fast Fourier Transform in C++, Ansi-style
//============================================================================

#include <iostream>
#include <complex>
using namespace std;

const double PI = 3.141592653589793238463;
const float  PI_F = 3.14159265358979f;

int main() {

	complex<double> racineUnite(cos(2*PI/3),sin(2*PI/3));

	cout << "Racine unite :" << pow(racineUnite,3) << endl; // prints
	return 0;
}

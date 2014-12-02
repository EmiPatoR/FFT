//============================================================================
// Name        : main.cpp
// Author      : HRUSTIC Emir
// Version     :
// Copyright   :
// Description : Fast Fourier Transform in C++, Ansi-style
//============================================================================

#include <iostream>
#include <complex>

#include "Polynomial.h"
#include "FFT.h"

using namespace std;


int main(int argc, char* argv[]) {

	const int N = 4;

	const double coefs_A[N] = {1,2,3,4};
	const double coefs_B[N] = {1,1,1,1};

	Polynomial pA = Polynomial(coefs_A,N);
	Polynomial pB = Polynomial(coefs_B,N);

	FFT f = FFT(&pA,&pB);


	cout << "Racine unite :" << f.getPA()->getCoefs(3) << endl; // prints
	return 0;
}

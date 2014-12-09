//============================================================================
// Name        : main.cpp
// Author      : HRUSTIC Emir
// Version     :
// Copyright   :
// Description : Fast Fourier Transform in C++, Ansi-style
//============================================================================


#include <iostream>
#include <string>
#include <complex>

#include "Polynomial.h"
#include "FFT.h"

using namespace std;


int main(int argc, char* argv[]) {

	const int N = 4; // /!\ N doit etre une puissance de 2 ! (N = 2^x)

	// Definition des coefs de A et B
	const std::complex<double> coefs_A[N] = {
			std::complex<double>(1,0),
			std::complex<double>(2,0),
			std::complex<double>(3,0),
			std::complex<double>(4,0)
	};

	const std::complex<double> coefs_B[N] = {
			std::complex<double>(1,0),
			std::complex<double>(1,0),
			std::complex<double>(1,0),
			std::complex<double>(1,0)
	};

	// Definition des polynomes A et B
	Polynomial<std::complex<double> > pA(coefs_A,N,"A");
	Polynomial<std::complex<double> > pB(coefs_B,N,"B");

	cout << " _________________________________________________________________" << endl <<
	        "/                                                                 |" << endl <<
	        "|                                                                 |" << endl <<
		  	"|                  TP : Fast Fourier Transform (FFT)              |" << endl <<
		  	"|                                                                 |" << endl <<
		  	"|                                                                 |" << endl <<
		  	"|   Author : HRUSTIC Emir                                 M2 - IF |" << endl <<
		  	"|_________________________________________________________________/" << endl
		  	<<endl << endl;



	cout << "Polynome : " << pA << endl; // A
	cout << "Polynome : " << pB << endl; // B
	cout << "Polynome : " << pA*pB << endl; // C = (A*B) Convolution de A et B avec FFT
	return 0;
}

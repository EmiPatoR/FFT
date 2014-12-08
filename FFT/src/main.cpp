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

	const int N = 8; // /!\ N doit etre une puissance de 2 ! (N = 2^x)

	// Definition des coefs de A et B
	const double coefs_A[N] = {1,2,3,4,0,0,0,0};
	const double coefs_B[N] = {1,1,1,1,0,0,0,0};

	// Definition des points-valeurs de A,B,C,D
	std::vector<std::complex<double> > evalA(N);
	std::vector<std::complex<double> > evalB(N);
	std::vector<std::complex<double> > evalC(N);

	// Definition des polynomes A et B
	Polynomial<double> pA(coefs_A,N,"A");
	Polynomial<double> pB(coefs_B,N,"B");


	//Initialisation du FFT
	FFT f(N);

	cout << "Polynome : " << pA << endl; // A
	cout << "Polynome : " << pB << endl; // A
	cout << "Polynome : " << pB + pA << endl;

	double x = 1.0;
	cout << "Eval de Horner A en " << x << " : " <<
			pA.Eval_Horner(x,0) << endl; // A

	//Calcul du FFT
	evalA = f.rec_FFT(&pA);
	evalB = f.rec_FFT(&pB);

	cout << "A = ";
	for(int i=0;i<N;i++){
		cout << evalA[i] << " ";
	}
	cout << endl;

	cout << "V = ";
	for(int i=0;i<N;i++){
		cout << evalB[i] << " ";
	}
	cout << endl;

	for(unsigned int i=0;i<evalA.size();i++)
		evalC[i] = evalA[i]*evalB[i];

	cout << "C = ";
	for(int i=0;i<N;i++){
		cout << evalC[i] << " ";
	}
	cout << endl;

	Polynomial<double> pC(N,"C");
	f.inverse_FFT(evalC,&pC);
	cout << "Polynome : " << pC << endl; // C

	return 0;
}

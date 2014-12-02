/*
 * FFT.h
 *
 *  Created on: Dec 2, 2014
 *      Author: Emip
 */

#ifndef FFT_H_
#define FFT_H_

#include <iostream>
#include <complex>
#include "Polynomial.h"

const double PI = 3.141592653589793238463;
const float  PI_F = 3.14159265358979f;

class FFT {

private:
	std::complex <double> m_unity_root[4];
	Polynomial* m_pA;
	Polynomial* m_pB;
	Polynomial* m_pC;
	Polynomial* m_pD;

public:
	//Constructors
	FFT();
	FFT(Polynomial* A, Polynomial* B);

	//Destructors
	virtual ~FFT();

	//Getters
	std::complex<double> getUnityRoot(int num){
		if(num < 4){
			return this->m_unity_root[num];
		}
		else{
			std::cerr << "Erreur indice trop grand ! (retour de la valeur 0)\n" << std::endl;
			return this->m_unity_root[0];
		}
	}
	Polynomial* getPA(){return this->m_pA;}
	Polynomial* getPB(){return this->m_pB;}
	Polynomial* getPC(){return this->m_pC;}
	Polynomial* getPD(){return this->m_pD;}
};

#endif /* FFT_H_ */

/*
 * FFT.cpp
 *
 *  Created on: Dec 2, 2014
 *      Author: Emip
 */

#include <complex>

#include "FFT.h"

FFT::FFT() {
	for(int i=0;i<4;i++)
		m_unity_root[i] = std::complex<double>(0.0,0.0);

	m_pA = NULL;
	m_pB = NULL;
	m_pC = NULL;
	m_pD = NULL;
}

FFT::FFT(Polynomial* A, Polynomial* B) {
	// TODO Auto-generated constructor stub
	if(A->getLength() != 0)
		m_unity_root[0] = std::complex<double>(cos(2*PI/A->getLength()),sin(2*PI/A->getLength()));
	if(B->getLength() != 0)
		m_unity_root[1] = std::complex<double>(cos(2*PI/B->getLength()),sin(2*PI/B->getLength()));
	m_pA = A;
	m_pB = B;
	m_pC = NULL;
	m_pD = NULL;
}

FFT::~FFT() {
	// TODO Auto-generated destructor stub
}


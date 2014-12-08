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
#include <vector>
#include "Polynomial.h"

const double PI = 3.141592653589793238463;
const float  PI_F = 3.14159265358979f;


class FFT {

private:
	std::complex<double>* m_unity_root;

public:
	//Constructors
	FFT();
	FFT(int);
	virtual ~FFT();
	template <class T>
	std::vector<std::complex<double> > rec_FFT(Polynomial<T>* P);
	template <class T>
	void inverse_FFT(const std::vector<std::complex<double> > C, Polynomial<T>* pC);
	std::complex<double> getUnityRoot(int num);
};


FFT::FFT(){m_unity_root = NULL;}


FFT::FFT(int polyLength){
	m_unity_root = new std::complex<double>[polyLength];
	for(int i=0;i<polyLength;i++){
		m_unity_root[i] = pow(std::complex<double>(cos(2*PI/polyLength),sin(2*PI/polyLength)),i);
	}
}


FFT::~FFT(){
	// TODO Auto-generated destructor stub
	if(m_unity_root != NULL){
		delete[] m_unity_root;
	}
}

//Methods
template <class T>
std::vector<std::complex<double> > FFT::rec_FFT(Polynomial<T>* P){
	int n = P->getLength();
	std::vector<std::complex<double> > V(n);
	if(n==1){
		std::vector<std::complex<double> > ret(0);
		ret.push_back(P->getCoefs(0));
		return ret;
	}
	std::complex<double> w_n(cos(2*PI/n),sin(2*PI/n));
	std::complex<double> w(1,0);
	Polynomial<T> *Pp = new Polynomial<T>(n/2,P->getNom() + "p");
	Polynomial<T> *Pi = new Polynomial<T>(n/2,P->getNom() + "i");
	for(int i=0;i<n;i+=2){
		Pp->setCoefs(i/2,P->getCoefs(i));
		Pi->setCoefs(i/2,P->getCoefs(i+1));
	}
	std::vector<std::complex<double> > y0 = rec_FFT(Pp);
	std::vector<std::complex<double> > y1 = rec_FFT(Pi);

	for(int i=0;i<n/2;i++){
		V[i] = y0[i] + w*y1[i];
		V[i+(n/2)] = y0[i] - w*y1[i];
		w = w_n*w;
	}

	delete Pp;
	delete Pi;

	return V;
}

template <class T>
void FFT::inverse_FFT(const std::vector<std::complex<double> > C, Polynomial<T>* pC){
	Polynomial<std::complex<double> >* pD = new Polynomial<std::complex<double> >(C.data(),C.size(),"C");
	std::vector<std::complex<double> > eval_D = rec_FFT(pD);
	for(int i=0;i<pD->getLength();i++){
		if(i==0){
			if( (eval_D[i].real() / (double)pD->getLength()) > 0.0000001)
				pC->setCoefs(i,eval_D[i].real() / (double)pD->getLength());
		}
		else{
			if( (eval_D[i].real() / (double)pD->getLength()) > 0.0000001)
				pC->setCoefs(C.size()-i,eval_D[i].real() / (double)pD->getLength());
		}
	}
	delete pD;
}

template <>
void FFT::inverse_FFT(const std::vector<std::complex<double> > C, Polynomial<std::complex<double> >* pC){
	Polynomial<std::complex<double> >* pD = new Polynomial<std::complex<double> >(C.data(),C.size(),"C");
	std::vector<std::complex<double> > eval_D = rec_FFT(pD);
	for(int i=0;i<pD->getLength();i++){
		if(i==0){
				pC->setCoefs(i,eval_D[i] / (double)pD->getLength());
		}
		else{
				pC->setCoefs(C.size()-i,eval_D[i] / (double)pD->getLength());
		}
	}
	delete pD;
}

//Getters
std::complex<double> FFT::getUnityRoot(int num){
	if(num < 4){
		return this->m_unity_root[num];
	}
	else{
		std::cerr << "Erreur indice trop grand ! (retour de la valeur 0)\n" << std::endl;
		return this->m_unity_root[0];
	}
}

#endif /* FFT_H_ */

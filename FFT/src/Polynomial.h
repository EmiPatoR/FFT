/*
 * Polynomial.h
 *
 *  Created on: Dec 2, 2014
 *      Author: emip
 */

#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

#include <string>
#include <complex>
#include <iostream>
#include <vector>

template <class T>
class Polynomial {

private:

	T* m_coefs;
	int m_length;
	std::string m_nom;
	int m_degree;

public:
	Polynomial();
	Polynomial(const T* coefs,const int length,const std::string nom);
	Polynomial(const int length,const std::string nom);
	Polynomial(const Polynomial<T>& p);
	virtual ~Polynomial();
	Polynomial<T>& operator+=(const Polynomial<T> &p);
	Polynomial<T>& operator*=(const Polynomial<T> &p);
	Polynomial<T>& operator*=(const T v);
	const Polynomial<T> operator+(const Polynomial<T> &other) const;
	const Polynomial<T> operator*(const Polynomial<T> &other) const;
	const Polynomial<T> operator*(const T other) const;
	void show(std::ostream &flux) const;
	T Eval_Horner(T x,int i);
	static int computeDegree(const Polynomial<T>& P);

	//Getters
	T getCoefs(int num);
	int getLength();
	int getDegree();
	std::string getNom();
	//Setters
	void setCoefs(int num,T val);

	//friends
	friend std::ostream& operator<<( std::ostream &flux, Polynomial<T> const& p ){
		p.show(flux);
		return flux;
	}

};

#include "FFT.h"

template <class T>
Polynomial<T>::Polynomial() {
	// TODO Auto-generated constructor stub
	m_length = 0;
	m_coefs = NULL;
	m_nom = "A";
	m_degree = 0;
}

template <class T>
Polynomial<T>::Polynomial(const T* coefs,const int length,const std::string nom){
	m_length = length;
	m_coefs = new T[length]();
	for(int i=0;i<length;i++)
		m_coefs[i] = T(coefs[i]);
	m_nom = nom;
	m_degree = computeDegree(*this);
}

template <class T>
Polynomial<T>::Polynomial(const int length,const std::string nom){
	this->m_length = length;
	this->m_coefs = new T[length]();
	for(int i=0;i<length;i++)
		this->m_coefs[i] = T();
	this->m_nom = nom;
	m_degree = computeDegree(*this);
}

template <class T>
Polynomial<T>::Polynomial(const Polynomial<T>& p) {
	m_length = p.m_length;
	m_coefs = new T[m_length]();
	for(int i=0;i<m_length;i++)
		m_coefs[i] = T(p.m_coefs[i]);
	m_nom = p.m_nom;
	m_degree = computeDegree(*this);
}

template <class T>
Polynomial<T>& Polynomial<T>::operator+=(const Polynomial<T> &p) {
	if(this->m_length >= p.m_length){
		for(int i=0;i<this->m_length;i++){
			this->m_coefs[i] = this->m_coefs[i] + p.m_coefs[i];
		}
	}
	else{
		T* new_coefs = new T[p.m_length]();
		for(int i=0;i<p.m_length;i++){
			if(i <= (this->m_length - 1))
				new_coefs[i] = this->m_coefs[i] + p.m_coefs[i];
			else
				new_coefs[i] = p.m_coefs[i];
		}
		this->m_length = p.m_length;
		delete[] this->m_coefs;
		this->m_coefs = NULL;
		this->m_coefs = new_coefs;
	}
	this->m_nom = this->m_nom + "+" + p.m_nom;
	return *this;
}

template <class T>
Polynomial<T>& Polynomial<T>::operator*=(const Polynomial<T> &p) {

	int size = std::max(this->m_length,p.m_length);

	std::vector<std::complex<double> > evalA(2*size);
	std::vector<std::complex<double> > evalB(2*size);
	std::vector<std::complex<double> > evalC(2*size);
	Polynomial<T> pC(2*size,"C");
	Polynomial<T> *copie_pA = this;
	Polynomial<T> copie_pB = p;

	FFT f(size);

	T* new_coefs_A = new T[2*size]();
	T* new_coefs_B = new T[2*size]();

	for(int i=0;i<2*size;i++){

		if (i<copie_pA->m_length)
			new_coefs_A[i] = copie_pA->m_coefs[i];
		else
			new_coefs_A[i] = T();

		if (i<copie_pB.m_length)
			new_coefs_B[i] = copie_pB.m_coefs[i];
		else
			new_coefs_B[i] = T();

	}

	delete [] copie_pA->m_coefs;
	delete [] copie_pB.m_coefs;

	copie_pA->m_coefs = new_coefs_A;
	copie_pB.m_coefs = new_coefs_B;
	copie_pA->m_length = 2*size;
	copie_pB.m_length = 2*size;

	evalA = f.rec_FFT(copie_pA);
	evalB = f.rec_FFT(&copie_pB);

	for(unsigned int i=0;i<evalA.size();i++)
		evalC[i] = evalA[i]*evalB[i];

	f.inverse_FFT(evalC,copie_pA);

	this->m_degree = computeDegree(*this);
	this->m_nom = this->m_nom + "*" + p.m_nom;
	return *this;
}

template <class T>
Polynomial<T>& Polynomial<T>::operator*=(const T v) {
	for(int i=0;i<this->m_length;i++){
		this->m_coefs[i] = this->m_coefs[i] * v;
	}
	//this->m_nom = this->m_nom + "*" + v.;
	return *this;
}

template <class T>
const Polynomial<T> Polynomial<T>::operator+(const Polynomial<T> &other) const {
	return Polynomial<T>(*this) += other;
}

template <class T>
const Polynomial<T> Polynomial<T>::operator*(const Polynomial<T> &other) const {
	return Polynomial<T>(*this) *= other;
}

template <class T>
const Polynomial<T> Polynomial<T>::operator*(const T other) const {
	return Polynomial<T>(*this) *= other;
}

template <class T>
void Polynomial<T>::show(std::ostream &flux) const
{
	flux << m_nom << "(x) = ";
	for(int i=0;i<m_length;i++){
		if(i == 0){
			if(i != (m_length - 1))
				flux << m_coefs[i] << " + ";
			else
				flux << m_coefs[i];
		}
		else{
			if(i != (m_length - 1))
				flux << m_coefs[i] << "x^" << i << " + ";
			else
				flux << m_coefs[i] << "x^" << i;
		}
	}
}

template <class T>
T Polynomial<T>::Eval_Horner(T x,int i){
	if (i == this->getLength()-1){
		return this->getCoefs(i);
	}
	else{
		return (x*Eval_Horner(x,i+1) + this->getCoefs(i));
	}
}

template <class T>
int Polynomial<T>::computeDegree(const Polynomial<T>& P){
	int degree = 0;
	T val = T();
	for(int i=0;i<P.m_length;i++){
		if(P.m_coefs[i] != val)
			degree = i;
	}
	return degree;
}

template <class T>
Polynomial<T>::~Polynomial() {
	// TODO Auto-generated destructor stub
	if(m_coefs != NULL){
		delete[] m_coefs;
	}
}

template <class T>
T Polynomial<T>::getCoefs(int num){
	if(num < this->m_length){
		return this->m_coefs[num];
	}
	else{
		std::cerr << "Erreur indice_coefs trop grand !\n";
		return this->m_coefs[0];
	}
}

template <class T> int Polynomial<T>::getLength(){return this->m_length;}
template <class T> int Polynomial<T>::getDegree(){return this->m_degree;}
template <class T> std::string Polynomial<T>::getNom(){return this->m_nom;}

//Setters
template <class T>
void Polynomial<T>::setCoefs(int num,T val){
	if(num < this->m_length){
		this->m_coefs[num] = val;
	}
	else{
		std::cerr << "Erreur indice_coefs trop grand !\n";
	}
}

#endif /* POLYNOMIAL_H_ */

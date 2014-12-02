/*
 * Polynomial.cpp
 *
 *  Created on: Dec 2, 2014
 *      Author: emip
 */

#include <iostream>
#include "Polynomial.h"

Polynomial::Polynomial() {
	// TODO Auto-generated constructor stub
	m_length = 0;
	m_coefs = NULL;
}

Polynomial::Polynomial(const double* coefs,const int length){
	m_length = length;
	m_coefs = new double[length];
	for(int i=0;i<length;i++)
		m_coefs[i] = coefs[i];
}

Polynomial::Polynomial(const Polynomial& p) {
	m_length = p.m_length;
	m_coefs = new double[m_length];
	for(int i=0;i<m_length;i++)
		m_coefs[i] = p.m_coefs[i];
}

Polynomial & Polynomial::operator+=(const Polynomial &p) {
	if(this->m_length >= p.m_length){
		for(int i=0;i<p.m_length;i++){
			this->m_coefs[i] = this->m_coefs[i] + p.m_coefs[i];
		}
	}
	else{
		double* new_coefs = new double[p.m_length];
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
	return *this;
}

Polynomial::~Polynomial() {
	// TODO Auto-generated destructor stub
	if(m_coefs != NULL)
		delete[] m_coefs;
}


/*
 * Polynomial.h
 *
 *  Created on: Dec 2, 2014
 *      Author: emip
 */

#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

class Polynomial {

private:
	double* m_coefs;
	int m_length;

public:
	Polynomial();
	Polynomial(const double* coefs,const int length);
	Polynomial(const Polynomial& p);
	Polynomial &operator+=(const Polynomial &rhs);
	virtual ~Polynomial();

	int getLength(){return this->m_length;}
	double getCoefs(int num){
		if(num < this->m_length){
			return this->m_coefs[num];
		}
		else{
			std::cerr << "Erreur indice_coefs trop grand !\n";
			return this->m_coefs[0];
		}
	}


	//Setters
	void setCoefs(int num,double val){
		if(num < this->m_length){
			this->m_coefs[num] = val;
		}
		else{
			std::cerr << "Erreur indice_coefs trop grand !\n";
		}
	}

};

#endif /* POLYNOMIAL_H_ */

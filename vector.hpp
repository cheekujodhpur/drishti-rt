#ifndef __VECTOR_HPP_INCLUDED__
#define __VECTOR_HPP_INCLUDED__
#include<vector>

class vec{
	

public:
	std::vector<double> v = std::vector<double>(3);
	vec(){}
	vec(std::vector<double> v1) : v(v1) {}		//constructor

	double operator[](int a);    	

	std::vector<double> getVector();
	    
	void normalise();
	vec operator-();                //returns negative of vector
	vec operator-(const vec& v1);		//diff of 2 vectors
	vec operator+(const vec& v2);
	void operator=(const vec& v2);
	vec operator*(double t);
	//vec operator/(double t) const;
	double dot(const vec& v1);
	vec cross(const vec& v1);
};
#endif 
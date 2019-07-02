#ifndef __VECTOR_HPP_INCLUDED__
#define __VECTOR_HPP_INCLUDED__
#include<vector>

class vec{
	std::vector<double> v(3);

	public:

	vec(std::vector<double> v1);		//constructor

	double first();     //returns v[0]
	double second();    //returns v[1]
	double third();		//returns v[2]
	    
	normalise();
	vec operator-() const;                 //returns negative of vector
	vec operator-(const vec& v1) const;		//diff of 2 vectors
	vec operator+(const vec& v2) const;
	vec operator*(double t) const;
	vec operator/(double t) const;
	double dot(const vec& v1);
	vec cross(const vec& v1) const;




};
#endif 
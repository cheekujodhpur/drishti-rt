#include "vector.hpp"

vec:: vec()
{
	
}

double vec :: first()
{
	return v[0];
}

double vec :: second()
{
	return v[1];
}

double vec :: third()
{
	return v[2];
}

vec :: normalise()
{
	
}

vec vec::operator-() {
	
	std::vector<double> v2(3);
	for(int i=0;i<3;i++)
	{
		v2[i]= -1*v[i];
	}
	return vec(v2);
}

vec vec::operator-(const vec& v1){
	std::vector<double> v2(3);

	for(int i=0;i<3;i++)
	{
		v2[i] = v[i] - v1.v[i];
	}
	return vec(v2);
	
}

vec vec::operator+(const vec& v2)
{
	std::vector<double> v1(3);

	for(int i=0;i<3;i++)
	{
		v1[i] = v[i] + v2.v[i];
	}
	return vec(v2);
}

 vec::operator=(const vec& v2)
{
	for(int i=0;i<3;i++)
	{
		v[i] = v2.v[i];
	}
}

vec vec::operator*(double t)
{
	std::vector<double> v1(3);
	for(int i=0;i<3;i++)
	{
		v1[i] = t*v[i];
	}
	return vec(v1);
}

double vec::dot(const vec& v1)
{
	double ans = v[0]*v1.v[0] + v[1]*v1.v[1] + v[2]*v1.v[2];
	return ans;
}

vec vec::cross(const vec& v1)
{
	std::vector<double> v2(3);

	v2[2] = v[0]*v1.v[1] - v1.v[0]*v[1];
	v2[1] = v[2]*v1.v[0] - v1.v[2]*v[0];
	v2[0] = v[1]*v1.v[2] - v1.v[1]*v[2];

	return vec(v2);
}
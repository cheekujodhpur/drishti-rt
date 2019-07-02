#ifndef __LIGHTS_HPP_INCLUDED__
#define __LIGHTS_HPP_INCLUDED__

#include<vector>
#include "vector.hpp"
#include <string>

class light{
public:
	virtual std::string source_type()=0;
};

class pointlight: public light{
	vec position;
	std::vector<double> color = std::vector<double>(3);
	double ka;
public:
	void setPos(vec pos);
	void setKa(double ka0);
	void setColor(std::vector<double> color0);
	vec getPos();
	std::vector<double> getColor();
	std::string source_type();
};
#endif
#ifndef __LIGHTS_HPP_INCLUDED__
#define __LIGHTS_HPP_INCLUDED__

#include<vector>
#include <string>
//using namespace std;

class light{
public:
	virtual std::string source_type()=0;
};

class pointlight: public light{
	std::vector<double> position;
	std::vector<double> color = std::vector<double>(3);
	double ka;
public:
	void setPos(std::vector<double> pos);
	void setKa(double ka0);
	void setColor(std::vector<double> color0);
	std::vector<double> getPos();
	std::vector<double> getColor();
	std::string source_type();
};
#endif
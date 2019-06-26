#ifndef __LIGHTS_HPP_INCLUDED__
#define __LIGHTS_HPP_INCLUDED__

#include<vector>
//using namespace std;

class light{

};

class pointlight: public light{
	std::vector<double> position;
	std::vector<double> color = std::vector<double>(3);
	double ka;
public:
	void setPos(std::vector<double> pos);
	void setKa(double ka0);
	void setColor(std::vector<double> color0);
};
#endif
#ifndef __LIGHTS_HPP_INCLUDED__
#define __LIGHTS_HPP_INCLUDED__

#include<vector>
using namespace std;

class light{

};

class pointlight: public light{
	vector<double> position;
	vector<double> color = vector<double>(3);
	double ka;
public:
	void setPos(vector<double> pos);
	void setKa(double ka0);
	void setColor(vector<double> color0);
};
#endif
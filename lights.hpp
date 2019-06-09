#ifndef __LIGHTS_HPP_INCLUDED__
#define __LIGHTS_HPP_INCLUDED__

#include<vector>
using namespace std;

class lights{

};

class pointlight: lights{
	vector<double> position;
	double color[3];             //color color;
	double ka;
public:
	void setPos(vector<double> pos);
	void setKa(double ka0);
	void setColor(double color0[]);


};
#endif
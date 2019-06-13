#include "lights.hpp"

using namespace std;

void pointlight::setPos(vector<double> pos)
{
	position=pos;
}

void pointlight::setKa(double ka0)
{
	ka=ka0;
}

void pointlight::setColor(vector<double> color0)
{
	color = color0;
	
}
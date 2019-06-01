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

void pointlight::setColor(double color0[])
{
	for(int i=0;i<3;i++)
	{
		color[i]=color0[i];
	}
}
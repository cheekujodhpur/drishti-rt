#include "lights.hpp"


void pointlight::setPos(vec pos)
{
	position=pos;
}
void pointlight::setKa(double ka0)
{
	ka=ka0;
}
void pointlight::setColor(std::vector<double> color0)
{
	color = color0;
	
}
vec pointlight::getPos()
{
	return position;
}
std::vector<double> pointlight::getColor()
{
	return color;
}
std::string pointlight::source_type()
{
	return "pointlight";
}
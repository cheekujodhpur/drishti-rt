#include "lights.hpp"

//using namespace std;

void pointlight::setPos(std::vector<double> pos)
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
std::vector<double> pointlight::getPos()
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
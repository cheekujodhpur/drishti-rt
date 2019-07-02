#include "integrator.hpp"
//using namespace std;


int whitted::getDepth()
{
	return depth;
}
void whitted::setDepth(int dep)
{
	depth = dep;
}
std::string whitted::source_type()
{
	return "whitted";
}
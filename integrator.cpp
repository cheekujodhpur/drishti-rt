#include "integrator.hpp"
using namespace std;

char* integrator::getID()
{
	return ID;
}
void integrator::setID(const char* id)
{
	ID = id;
}

int whitted::getDepth()
{
	return depth;
}
void whitted::setDepth(int dep)
{
	depth = dep;
}
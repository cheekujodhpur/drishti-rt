#ifndef __INTEGRATOR_HPP_INCLUDED__
#define __INTEGRATOR_HPP_INCLUDED__

#include <vector>
using namespace std;

class integrator
{
protected:
	char* ID;
public:
	char* getID();
	void setID(const char* id);
};

class whitted: public integrator
{
protected:
	int depth;
public:
	int getDepth();
	void setDepth(int dep);
}

#endif 
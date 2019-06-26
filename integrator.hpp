#ifndef __INTEGRATOR_HPP_INCLUDED__
#define __INTEGRATOR_HPP_INCLUDED__

#include <vector>
#include <string>
//using namespace std;

class integrator
{
protected:
	std::string ID;
public:
	std::string getID();
	void setID(const char* id);
};

class whitted: public integrator
{
protected:
	int depth;
public:
	int getDepth();
	void setDepth(int dep);
};

#endif 
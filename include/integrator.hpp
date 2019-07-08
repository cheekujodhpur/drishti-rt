#ifndef __INTEGRATOR_HPP_INCLUDED__
#define __INTEGRATOR_HPP_INCLUDED__

#include <vector>
#include <string>

class integrator
{
public:
	virtual std::string integrator_type()=0;
};

class whitted: public integrator
{
protected:
	int depth;
public:
	int getDepth();
	void setDepth(int dep);
	std::string integrator_type();
};

#endif 
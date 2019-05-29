#include "materials.hpp"

using namespace std;

void simplemat::setId(const char *ID)//don't actually need this as of now
{
	id = ID;
}
void simplemat::setDiffuse(vector<double> diff)
{
	diffuse = diff;
}
void simplemat::setSpecular(vector<double> spec)
{
	specular = spec;
}
void simplemat::setReflect(vector<double> ref)
{
	reflect = ref;
}
void simplemat::setTransmit(vector<double> trans)
{
	transmit = trans;
}
void simplemat::setEta(double eta0)
{
	eta = eta0;
}
void simplemat::setN(double n0)
{
	n = n0;
}
void simplemat::setIsreflect(bool isref)
{
	isreflect = isref;
}
void simplemat::setIstransmit(bool istrans)
{
	istransmit = istrans;
}
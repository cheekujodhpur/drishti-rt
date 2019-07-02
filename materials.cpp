#include "materials.hpp"

//using namespace std;

//material class
void material::setID(const char *ID)//don't actually need this as of now
{
	id = ID;
}
std::string material::getID()
{
	return id;
}

//simplemat class
void simplemat::setDiffuse(std::vector<double> diff)
{
	diffuse = diff;
}
void simplemat::setSpecular(std::vector<double> spec)
{
	specular = spec;
}
void simplemat::setReflect(std::vector<double> ref)
{
	reflect = ref;
}
void simplemat::setTransmit(std::vector<double> trans)
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

std::vector<double> simplemat::getDiffuse()
{
	return diffuse;
}
std::vector<double> simplemat::getSpecular()
{
	return specular;
}
std::vector<double> simplemat::getReflect()
{
	return reflect;
}
std::vector<double> simplemat::getTransmit()
{
	return transmit;
}
bool simplemat::getIsReflect()
{
	return isreflect;
}
bool simplemat::getIsTransmit()
{
	return istransmit;
}
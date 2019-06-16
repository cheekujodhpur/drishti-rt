#ifndef __MATERIALS_HPP_INCLUDED__
#define __MATERIALS_HPP_INCLUDED__

#include <vector>
#include <string>

using namespace std;

class material{
protected:
	string id;

public:
	material(){}
	material(string s):id(s){}
};

class simplemat : public material{
	vector<double> diffuse = vector<double>(3);    
	vector<double> specular = vector<double>(3);
	vector<double> reflect = vector<double>(3);
	vector<double> transmit = vector<double>(3);
	double eta;
	double n;
	bool isreflect;
	bool istransmit;

public:
	simplemat(){}
	simplemat(string s):material(s){}//parameterized constructor
	void setId(const char *ID);//don't actually need this as of now
	void setDiffuse(vector<double> diff);
	void setSpecular(vector<double> spec);
	void setReflect(vector<double> ref);
	void setTransmit(vector<double> trans);
	void setEta(double eta0);
	void setN(double n0);
	void setIsreflect(bool isref);
	void setIstransmit(bool istrans);
};
#endif 
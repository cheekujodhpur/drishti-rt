#ifndef __MATERIALS_HPP_INCLUDED__
#define __MATERIALS_HPP_INCLUDED__

#include <vector>
#include <string>

//using namespace std;

class material{
protected:
	std::string id;

public:
	material(){}
	material(std::string s):id(s){}
	void setID(const char *ID);//don't actually need this as of now
	std::string getID();
};

class simplemat : public material{
	std::vector<double> diffuse = std::vector<double>(3);    
	std::vector<double> specular = std::vector<double>(3);
	std::vector<double> reflect = std::vector<double>(3);
	std::vector<double> transmit = std::vector<double>(3);
	double eta;
	double n;
	bool isreflect;
	bool istransmit;

public:
	simplemat(){}
	simplemat(std::string s):material(s){}//parameterized constructor
	void setDiffuse(std::vector<double> diff);
	void setSpecular(std::vector<double> spec);
	void setReflect(std::vector<double> ref);
	void setTransmit(std::vector<double> trans);
	void setEta(double eta0);
	void setN(double n0);
	void setIsreflect(bool isref);
	void setIstransmit(bool istrans);
	std::vector<double> getDiffuse();
	std::vector<double> getSpecular();
	std::vector<double> getReflect();
	std::vector<double> getTransmit();
	bool getIsReflect();
	bool getIsTransmit();
};
#endif 
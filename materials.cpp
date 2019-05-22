#include<iostream>
using namespace std;

class material{
protected:
	string id;

public:
	material(string s){
		id = s;
	}
}

class simplemat : public material{
	double diffuse[3];    //   color diffuse;
	double specular[3];   //   color specular;
	double reflect[3];    //    color reflect;
	double transmit[3];   //   color transmit;
	double eta;
	double n;
	bool isreflect;
	bool istransmit;

public:
	
	//parameterized constructor
	simplemat(double diff[],double spec[],double ref[],double trans[],double eta0,double n0,bool isref, bool istrans, string s):material(s){
		for(int i=0;i<3;i++){
			diffuse[i] = diff[i];
			specular[i] = spec[i];
			reflect[i] = ref[i];
			transmit[i] = trans[i];
		}
		eta = eta0;
		n = n0;
		isreflect = isref;
		istransmit = istrans;
	}
}
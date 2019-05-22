#include<iostream>
using namespace std;
class material{
	
	string simplemat;
	double diffuse[3];    //   color diffuse;
	double specular[3];   //   color specular;
	double reflect[3];    //    color reflect;
	double transmit[3];   //   color transmit;
	double eta;
	double n;
	bool isreflect;
	bool istransmit;
public:
	material material(string s)    //parameterised constructor
	{
		simplemat=s;
	}
}
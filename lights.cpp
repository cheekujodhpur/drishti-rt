#include<iostream>
using namespace std;
class lights{

}

class pointlight : lights{
	vector<double> position(3);
	double color[3];             //color color;
	double ka;

public:
	pointlight(vector<double> pos, double col[], double ka0){
		position = pos;
		ka = ka0;
		for(int i=0;i<3;i++)
			color[i] = col[i];
	}
}
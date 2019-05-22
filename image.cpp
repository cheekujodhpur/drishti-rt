#include<iostream>
using namespace std;
class image{

	double width;
	double height;
	double bgcolor[3];	//color bgcolor;

public:
	image(double w, double h, double bg){
		width = w;
		height = h;
		for(int i=0;i<3;i++)
			bgcolor[i] = bg[i];
	}
}
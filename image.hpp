#ifndef __IMAGE_HPP_INCLUDED__
#define __IMAGE_HPP_INCLUDED__
#include <vector>
using namespace std;
class image{

	double width;
	double height;
	vector<double> bgcolor = vector<double>(3);	//color bgcolor;

public:
	void setWidth(double w);
	void setHeight(double h);
	void setBgcolor(vector<double> bg);
};
#endif 
#ifndef __IMAGE_HPP_INCLUDED__
#define __IMAGE_HPP_INCLUDED__
#include <vector>

class image{

	double width;
	double height;
	std::vector<double> bgcolor = std::vector<double>(3);

public:
	image(){}
	~image(){}
	image(const image &i2) 
	{
		width = i2.width;
		height = i2.height;
		bgcolor = i2.bgcolor;
	}
	void setWidth(double w);
	void setHeight(double h);
	void setBgcolor(std::vector<double> bg);
	double getWidth();
	double getHeight();
	std::vector<double> getBgcolor();
};
#endif 
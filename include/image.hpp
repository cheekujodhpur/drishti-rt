#ifndef __IMAGE_HPP_INCLUDED__
#define __IMAGE_HPP_INCLUDED__
#include <vector>

class image{

	double width;
	double height;
	std::vector<double> bgcolor = std::vector<double>(3);

public:
	void setWidth(double w);
	void setHeight(double h);
	void setBgcolor(std::vector<double> bg);
	double getWidth();
	double getHeight();
	std::vector<double> getBgcolor();
};
#endif 
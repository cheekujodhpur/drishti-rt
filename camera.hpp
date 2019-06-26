#ifndef __CAMERA_HPP_INCLUDED__
#define __CAMERA_HPP_INCLUDED__

#include <vector>
//using namespace std;

class camera
{
	std::vector<double> lookat = std::vector<double>(3);
	std::vector<double> eye = std::vector<double>(3);
	std::vector<double> up = std::vector<double>(3);
	std::vector<double> third = std::vector<double>(3);
	double fov;	//angle fov;
	double far;
	double near;

public:
	// camera(vector<double> look, vector<double> eye0, vector<double> up0, double fov0, double far0, double near0);
	void setLookat(std::vector<double> look);
	void setThird();
	void setEye(std::vector<double> eye0);
	void setUp(std::vector<double> up0);
	void setFov(double fov0);
	void setNear(double near0);
	void setFar(double far0);
	std::vector<double> getLookat();
	std::vector<double> getUp();
	std::vector<double> getThird();
	std::vector<double> getEye();
};

#endif 
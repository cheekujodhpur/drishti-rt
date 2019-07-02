#ifndef __CAMERA_HPP_INCLUDED__
#define __CAMERA_HPP_INCLUDED__

#include <vector>
//using namespace std;

class camera
{
	std::vector<double> lookat = std::vector<double>(3);
	std::vector<double> eye = std::vector<double>(3);
	std::vector<double> up = std::vector<double>(3);
	std::vector<double> third ;
	double fov;	//angle fov (in degrees)
	double far;
	double near;

public:
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
	double getFov();
};

#endif 
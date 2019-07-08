#ifndef __CAMERA_HPP_INCLUDED__
#define __CAMERA_HPP_INCLUDED__

#include "vector.hpp"
//using namespace std;

class camera
{
	vec lookat;
	vec eye;
	vec up;
	vec third;
	double fov;	//angle fov (in degrees)
	double far;
	double near;

public:
	void setLookat(vec look);
	void setThird();
	void setEye(vec eye0);
	void setUp(vec up0);
	void setFov(double fov0);
	void setNear(double near0);
	void setFar(double far0);
	vec getLookat();
	vec getUp();
	vec getThird();
	vec getEye();
	double getFov();
};

#endif 
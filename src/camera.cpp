#include "camera.hpp"


void camera::setLookat(vec look)
{
	lookat = look;
}
void camera::setThird()
{
	third = up.cross(lookat);
	/*third.push_back(up[1]*lookat[2] - up[2]*lookat[1]);
	third.push_back(up[2]*lookat[0] - up[0]*lookat[2]);
	third.push_back(up[0]*lookat[1] - up[1]*lookat[0]);*/  
}
void camera::setEye(vec eye0)
{
	eye = eye0;
}
void camera::setUp(vec up0)
{
	up = up0;
}
void camera::setFov(double fov0)
{
	fov = fov0;
}
void camera::setNear(double near0)
{
	near = near0;
}
void camera::setFar(double far0)
{
	far = far0;
}
vec camera::getLookat()
{
	return lookat;
}
vec camera::getUp()
{
	return up;
}
vec camera::getThird()
{
	return third;
}
vec camera::getEye()
{
	return eye;
}
double camera::getFov()
{
	return fov;
}
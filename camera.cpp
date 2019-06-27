#include "camera.hpp"

//using namespace std;


/*camera(vector<double> look, vector<double> eye0, vector<double> up0, double fov0, double far0, double near0)
{
	lookat = look;
	eye = eye0;
	up = up0;
	fov = fov0;
	near = near0;
	far = far0;
}*/
void camera::setLookat(std::vector<double> look)
{
	lookat = look;
}
void camera::setThird()
{
	third.push_back(up[1]*lookat[2] - up[2]*lookat[1]);
	third.push_back(up[2]*lookat[0] - up[0]*lookat[2]);
	third.push_back(up[0]*lookat[1] - up[1]*lookat[0]);  
}
void camera::setEye(std::vector<double> eye0)
{
	eye = eye0;
}
void camera::setUp(std::vector<double> up0)
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
std::vector<double> camera::getLookat()
{
	return lookat;
}
std::vector<double> camera::getUp()
{
	return up;
}
std::vector<double> camera::getThird()
{
	return third;
}
std::vector<double> camera::getEye()
{
	return eye;
}
double camera::getFov()
{
	return fov;
}
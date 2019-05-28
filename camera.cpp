#include "camera.hpp"

#include<vector>
using namespace std;


/*camera(vector<double> look, vector<double> eye0, vector<double> up0, double fov0, double far0, double near0)
{
	lookat = look;
	eye = eye0;
	up = up0;
	fov = fov0;
	near = near0;
	far = far0;
}*/
void camera::setLookat(vector<double> look)
{
	lookat = look;
}
void camera::setEye(vector<double> eye0)
{
	eye = eye0;
}
void camera::setUp(vector<double> up0)
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
#include "camera.hpp"

#include<vector>
using namespace std;


/*camera(vector<float> look, vector<float> eye0, vector<float> up0, double fov0, double far0, double near0)
{
	lookat = look;
	eye = eye0;
	up = up0;
	fov = fov0;
	near = near0;
	far = far0;
}*/
setLookat(vector<double> look)
{
	lookat = look;
}
setEye(vector<float> eye0)
{
	eye = eye0;
}
setUp(vector<float> up0)
{
	up = up0;
}
setFov(double fov0)
{
	fov = fov0;
}
setNear(double near0)
{
	near = near0;
}
setFar(double far0)
{
	far = far0;
}
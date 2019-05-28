#ifndef __CAMERA_H_INCLUDED__
#define __CAMERA_H_INCLUDED__

#include<vector>
using namespace std;

class camera
{
	vector<double> lookat = vector<double>(3);
	vector<double> eye = vector<double>(3);
	vector<double> up = vector<double>(3);
	double fov;	//angle fov;
	double far;
	double near;

public:
	camera();
	// camera(vector<double> look, vector<double> eye0, vector<double> up0, double fov0, double far0, double near0);
	void setLookat(vector<double> look);
	void setEye(vector<double> eye0);
	void setUp(vector<double> up0);
	void setFov(double fov0);
	void setNear(double near0);
	void setFar(double far0);
};

#endif 
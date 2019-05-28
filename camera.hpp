#ifndef __CAMERA_H_INCLUDED__
#define __CAMERA_H_INCLUDED__

#include<vector>
using namespace std;

class camera
{
	vector<float> lookat(3);
	vector<float> eye(3);
	vector<float> up(3);
	double fov;	//angle fov;
	double far;
	double near;

public:
	camera();
	// camera(vector<float> look, vector<float> eye0, vector<float> up0, double fov0, double far0, double near0);
	setLookat(vector<double> look);
	setEye(vector<float> eye0);
	setUp(vector<float> up0);
	setFov(double fov0);
	setNear(double near0);
	setFar(double far0);
}
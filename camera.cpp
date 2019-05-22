#include<iostream>
using namespace std;
class camera{

	vector<float> lookat(3);
	vector<float> eye(3);
	vector<float> up(3);
	double fov;	//angle fov;
	double far;
	double near;

public:
	camera(vector<float> look, vector<float> eye0, vector<float> up0, double fov0, double far0, double near0){
		lookat = look;
		eye = eye0;
		up = up0;
		fov = fov0;
		far = far0;
		near = near0;
	}

}
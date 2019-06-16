#ifndef __SCENE_HPP_INCLUDED__
#define __SCENE_HPP_INCLUDED__

#include "camera.hpp"
#include "image.hpp"
#include "materials.hpp"
#include "objects.hpp"
#include "lights.hpp"
#include <vector>

using namespace std;

class scene{
	camera cam;
    image img;
    integrator intg;
    vector<material> materialslist;
    vector<object> objectslist;
    vector<light> lightslist;

public:
	void setCamera(camera cam0);
	void setImage(image img0);
	void setIntegrator(integrator intg0);
	void setMaterials(vector<material> materials);
	void setObjects(vector<object> objects);
	void setLights(vector<light> lights);
	camera getCamera();
	image getImage();
	integrator getIntegrator();
	vector<material> getMaterials();
	vector<object> getObjects();
	vector<light> getLights();
};

#endif
#ifndef __SCENE_HPP_INCLUDED__
#define __SCENE_HPP_INCLUDED__

#include "camera.hpp"
#include "image.hpp"
#include "materials.hpp"
#include "objects.hpp"
#include "lights.hpp"

class scene{
	camera cam;
    image img;
    vector<material> materialslist;
    vector<object> objectslist;
    vector<light> lightslist;

public:
	void setCamera();
	setImage();
	setMaterials();
	camera getCamera();
	image getImage();
	vector<material> getMaterials();
	vector<object> getObjects();
	vector<light> getLights();	
}

#endif
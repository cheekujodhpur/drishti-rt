#ifndef __SCENE_HPP_INCLUDED__
#define __SCENE_HPP_INCLUDED__

#include "camera.hpp"
#include "image.hpp"
#include "materials.hpp"
#include "objects.hpp"
#include "lights.hpp"
#include "ray.hpp"
#include "integrator.hpp"
#include <vector>
#include <memory>

using namespace std;

class scene{
	camera cam;
    image img;
    integrator intg;
    vector<material> materialslist;
    vector<shared_ptr<object>> objectslist;
    vector<light> lightslist;
    vector<vector<double> > rotation_mat;
    vector<vector<double> > translation_mat;
    vector<vector<double> > inv_rotation_mat;
    vector<vector<double> > inv_translation_mat;

public:
	void setCamera(camera cam0);
	void setImage(image img0);
	void setIntegrator(integrator intg0);
	void setMaterials(vector<material> materials);
	void setObjects(vector<shared_ptr<object>> objects);
	void setLights(vector<light> lights);
	camera getCamera();
	image getImage();
	integrator getIntegrator();
	vector<material> getMaterials();
	vector<shared_ptr<object>> getObjects();
	vector<light> getLights();
	void rotation_matrix_formation();
	void translation_matrix_formation();
	void inv_translation_matrix_formation();
	void inv_rotation_matrix_formation();
	vector<double> world_to_camera(vector<double> world_c);
	vector<double> camera_to_world(vector<double> camera_c);
	shared_ptr<object> intersect(ray Ray);
};

#endif
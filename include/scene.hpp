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
#include "vector.hpp"
#include <memory>

//using namespace std;

class scene{
	double ka;
	camera cam;
    image img;
    integrator* intg;
    std::vector<material* > materialslist;
    std::vector<std::shared_ptr<object> > objectslist;
    std::vector<light* > lightslist;
    std::vector<std::vector<double> > rotation_mat;
    std::vector<std::vector<double> > translation_mat;
    std::vector<std::vector<double> > inv_rotation_mat;
    std::vector<std::vector<double> > inv_translation_mat;
    double ***img_arr;
    static constexpr double eff_zero_shadow = 1e-15;
    static constexpr double bias = 1e-10;

public:
	scene(){}
	~scene()
	{
		/*if(img_arr!=NULL)
			delete img_arr;
		if(intg!=NULL)
			delete intg;
		for(unsigned int i=0;i<materialslist.size();i++)
			delete materialslist[i];
		for(unsigned int i=0;i<lightslist.size();i++)
			delete lightslist[i];*/
	}
	scene(const scene &s2) 
	{
		ka = s2.ka;
		cam = s2.cam;
		img = s2.img;
		intg = s2.intg;
		materialslist = s2.materialslist;
		objectslist = s2.objectslist;
		lightslist = s2.lightslist;
		rotation_mat = s2.rotation_mat;
		translation_mat = s2.translation_mat;
		inv_rotation_mat = s2.inv_rotation_mat;
		inv_translation_mat = s2.inv_translation_mat;
		img_arr = s2.img_arr;
	}
	void setAmbient(double ka0);
	void setCamera(camera cam0);
	void setImage(image img0);
	void setIntegrator(integrator* intg0);
	void setMaterials(std::vector<material* > materials);
	void setObjects(std::vector<std::shared_ptr<object> > objects);
	void setLights(std::vector<light* > lights);
	void init_img_arr();
	double getAmbient();
	camera getCamera();
	image getImage();
	integrator* getIntegrator();
	std::vector<material* > getMaterials();
	std::vector<std::shared_ptr<object> > getObjects();
	std::vector<light* > getLights();
	void rotation_matrix_formation();
	void translation_matrix_formation();
	void inv_translation_matrix_formation();
	void inv_rotation_matrix_formation();
	vec world_to_camera(vec world_c);
	vec camera_to_world(vec camera_c);
	std::shared_ptr<object> intersect(ray Ray);
	void write_to_ppm(char[]);
	std::vector<double> radiance(ray viewingRay, int depth, int max_depth, unsigned short xsubi[]);
	void render(char[],const int);
	std::unique_ptr<ray> generate_refract(ray Ray1,vec N, vec origin,double refract_index);
};

#endif

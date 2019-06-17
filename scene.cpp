#include "scene.hpp"

void scene::setCamera(camera cam0)
{
	cam = cam0;
}
void scene::setImage(image img0)
{
	img = img0;
}
void scene::setIntegrator(integrator intg0)
{
	intg = intg0;
}
void scene::setMaterials(vector<material> materials)
{
	materialslist = materials;
}
void scene::setObjects(vector<object> objects)
{
	objectslist = objects;
}
void scene::setLights(vector<light> lights)
{
	lightslist = lights;
}

camera scene::getCamera()
{
	return cam;
}
image scene::getImage()
{
	return img;
}
integrator scene::getIntegrator()
{
	return intg;
}
vector<material> scene::getMaterials()
{
	return materialslist;
}
vector<object> scene::getObjects()
{
	return objectslist;
}
vector<light> scene::getLights()
{
	return lightslist;
}

void scene::rotation_matrix_formation()
{
	vector<double> x = cam.lookat;
	vector<double> z = cam.up;
	vector<double> y = cam.third;//third is axis perp to lookat and up --> @shalabh: define it, it's not a member variable
	x.push_back(0);
	y.push_back(0);
	z.push_back(0);
	vector<double> fourth(3,0);  //supposed to be fourth row of matrix
	fourth.push_back(1);
	
	rotation-mat.push_back(x);
	rotation-mat.push_back(y);
	rotation-mat.push_back(z);
	rotation-mat.push_back(fourth);

}

void scene::translation_matrix_formation()
{
	vector<double> fourth = cam.eye;  //supposed to be fourth column of translation matrix
	vector<double> x;
	x.push_back(1);
	x.push_back(0);
	x.push_back(0);
	x.push_back(fourth[0]);

	y.push_back(0);
	y.push_back(1);
	y.push_back(0);
	y.push_back(fourth[1]);

	z.push_back(0);
	z.push_back(0);
	z.push_back(1);
	z.push_back(fourth[2]);

	vector<double> a(3,0)
	a.push_back(1);

	translation-mat.push_back(x);
	translation-mat.push_back(y);
	translation-mat.push_back(z);
	translation-mat.push_back(a);

}

vector<double> scene::world_to_camera(vector<double> world-c)
{
    vector<double> camera-c(world-c.size(),0);
    camera-c=mat_mult(mat_mult(rotation-mat,translation-mat),world-c);

    return camera-c;
}


vector<double> scene::camera_to_world(vector<double> camera-c)
{
    vector<double> world-c(camera-c.size(),0);
    world-c=mat_mult(mat_mult(inv(translation-mat),inv(rotation-mat)),camera-c);

    return world-c;
}
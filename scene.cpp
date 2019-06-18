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
	
	rotation_mat.push_back(x);
	rotation_mat.push_back(y);
	rotation_mat.push_back(z);
	rotation_mat.push_back(fourth);

}
void scene::inv_rotation_matrix_formation()
{
	vector<vector<double> > v = transpose(rotation_mat);
	inv_rotation_mat = v;
}

void scene::inv_translation_matrix_formation()
{
	vector<double> fourth = cam.eye;
	vector<double> x;
	vector<double> y;
	vector<double> z;
	x.push_back(1);
	x.push_back(0);
	x.push_back(0);
	x.push_back(-1*fourth[0]);

	y.push_back(0);
	y.push_back(1);
	y.push_back(0);
	y.push_back(-1*fourth[1]);

	z.push_back(0);
	z.push_back(0);
	z.push_back(1);
	z.push_back(-1*fourth[2]);


	vector<double> a(3,0)
	a.push_back(1);

	inv_translation_mat.push_back(x);
	inv_translation_mat.push_back(y);
	inv_translation_mat.push_back(z);
	inv_translation_mat.push_back(a);


}
void scene::translation_matrix_formation()
{
	vector<double> fourth = cam.eye;  //supposed to be fourth column of translation matrix
	vector<double> x;
	vector<double> y;
	vector<double> z;
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

	translation_mat.push_back(x);
	translation_mat.push_back(y);
	translation_mat.push_back(z);
	translation_mat.push_back(a);

}

vector<double> scene::world_to_camera(vector<double> world_c)
{
    vector<double> camera_c(world_c.size(),0);
    camera_c=mat_mult(mat_mult(rotation_mat,translation_mat),world_c);

    return camera_c;
}


vector<double> scene::camera_to_world(vector<double> camera_c)
{
    vector<double> world_c(camera_c.size(),0);
    world_c=mat_mult(mat_mult(inv_translation_mat,inv_rotation_mat),camera_c);

    return world_c;
}
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
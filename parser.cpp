#include <exception>
#include <stdexcept> // runtime_error
#include <cstdlib> // EXIT_FAILURE
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "inc/tinyxml/tinyxml.h"
#include "camera.hpp"
#include "image.hpp"
#include "materials.hpp"
#include "objects.hpp"
#include "lights.hpp"

using namespace std;



int write_to_ppm(int arr[w][h][3]){
    ofstream img ("picture.ppm");
    img << "P6" <<endl;
    img << w <<" "<< h <<endl;
    img << "255" <<endl;

    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
        {
            int r = arr[j][i][0];
            int g = arr[j][i][1];
            int b = arr[j][i][2];

            img << r <<" " << g <<" "<< b << endl;
        }
    }

    return 0;

}

vector<vector<double> > rotation-matrix-formation()
{
	vector<double> x = s.camera_object.lookat;
	vector<double> z = s.camera_object.up;
	vector<double> y = s.camera_object.third;//third is axis perp to lookat and up
	x.push_back(0);
	y.push_back(0);
	z.push_back(0);
	vector<double> fourth(3,0);  //supposed to be fourth row of matrix
	fourth.push_back(1);
	vector<vector<double> > v;
	v.push_back(x);
	v.push_back(y);
	v.push_back(z);
	v.push_back(fourth);

	return v;

}

vector<vector<double> > translation-matrix-formation()
{
	vector<double> fourth = s.camera_object.eye;  //supposed to be fourth column of translation matrix
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

	vector<vector<double> > v;
	v.push_back(x);
	v.push_back(y);
	v.push_back(z);
	v.push_back(a);

}

vector<vector<double> > rotation-mat = rotation-matrix-formation();
vector<vector<double> > translation-mat = translation-matrix-formation();

vector<double> world_to_camera(vector<double> world-c)
{
    vector<double> camera-c(world-c.size(),0);
    camera-c=mat-mult(mat-mult(rotation-mat,translation-mat),world-c);

    return camera-c;
}



vector<double> camera_to_world(vector<double> camera-c)
{
    vector<double> world-c(camera-c.size(),0);
    world-c=mat-mult(mat-mult(inv(translation-mat),inv(rotation-mat)),camera-c);

    return world-c;
}




// Extracts the content of an XML element that contains only text
const char* textValue(TiXmlElement* e)
{
    TiXmlNode* first=e->FirstChild();
    if(first!=0 && first==e->LastChild() && first->Type()==TiXmlNode::TINYXML_TEXT)
        return first->Value();
    else
        throw runtime_error(string("bad ") + e->Value( ) + " element");
}

vector<double> nodeToVector(TiXmlElement* Vect)
{
    string vect = textValue(Vect);
    stringstream ss(vect);
    double xval; ss>>xval;
    double yval; ss>>yval;
    double zval; ss>>zval;

    vector<double> result_vect;
    result_vect.push_back(xval);
    result_vect.push_back(yval);
    result_vect.push_back(zval);
}

double doubleVal(TiXmlElement* dval, const char* attrib)
{
    string temp_str = dval->Attribute(attrib);
    char* str = new char[temp_str.size()];
    strcpy(str, temp_str.c_str());

    stringstream ss(str);
    double result; ss>>result;
    
    delete str;
    return result;
}

camera nodeToCamera(TiXmlElement* Camera)
{
    camera result;
    TiXmlElement* element = Camera->FirstChildElement();
    if(element && strcmp(element->Value(),"lookat")==0)
        result.setLookat(nodeToVector(element));

    element=element->NextSiblingElement();
    if(element && strcmp(element->Value(),"eye")==0)
        result.setEye(nodeToVector(element));

    element=element->NextSiblingElement();
    if(element && strcmp(element->Value(),"up")==0)
        result.setUp(nodeToVector(element));
    
    element=element->NextSiblingElement();
    if(element && strcmp(element->Value(),"fov")==0)
        result.setFov(doubleVal(element,"angle"));

    element=element->NextSiblingElement();
    if(element && strcmp(element->Value(),"near")==0)
        result.setNear(doubleVal(element,"double"));
    
    element=element->NextSiblingElement();
    if(element && strcmp(element->Value(),"far")==0)
        result.setFar(doubleVal(element,"double"));

    return result;
}

image nodeToImage(TiXmlElement* Image)
{
	image result;
	TiXmlElement* element = Image->FirstChildElement();
	if(element && strcmp(element->Value(),"width")==0)
		result.setWidth(doubleVal(element,"width"));
	
    element=element->NextSiblingElement();
	if(element && strcmp(element->Value(),"height")==0)
		result.setHeight(doubleVal(element,"height"));
	
    element=element->NextSiblingElement();
	if(element && strcmp(element->Value(),"bgcolor")==0)
		result.setBgcolor(nodeToVector(element));
	
	return result;
}

material* nodeToMaterial(TiXmlElement* Material)
{
	material *result;

    const char *id;
    if((id = Material->Attribute("id")) && strcmp(Material->Value(),"simplemat")==0) //simplemat material
    {
        simplemat sim_mat(id); //creating a simplemat object
        
        TiXmlElement* element = Material->FirstChildElement();

        if(element && strcmp(element->Value(),"diffuse")==0)
            sim_mat.setDiffuse(nodeToVector(element));
        
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"specular")==0)
            sim_mat.setSpecular(nodeToVector(element));
        
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"reflect")==0)
            sim_mat.setReflect(nodeToVector(element));
        
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"transmit")==0)
            sim_mat.setTransmit(nodeToVector(element));
        
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"eta")==0)
            sim_mat.setEta(doubleVal(element,"eta"));
        
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"n")==0)
            sim_mat.setN(doubleVal(element,"n"));
        
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"isreflect")==0)
            sim_mat.setIsreflect(strcmp(element->Attribute("isreflect"),"true"));
        
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"istransmit")==0)
            sim_mat.setIstransmit(strcmp(element->Attribute("istransmit"),"true"));

        result = &sim_mat;
    }
    else
        throw runtime_error(string("bad ") + " element");

	return result;
}

object* nodeToObject(TiXmlElement* Object) //INCOMPLETE!
{
    object *result;

    const char* mat_name;
    if((mat_name = Object->Attribute("material")) && strcmp(Object->Value(),"sphere")==0) //sphere object
    {
        sphere sph_obj(id); //creating a simplemat object
        
        TiXmlElement* element = Object->FirstChildElement();

        /*if(element && strcmp(element->Value(),"diffuse")==0)
            sim_mat.setDiffuse(nodeToVector(element));
        
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"specular")==0)
            sim_mat.setSpecular(nodeToVector(element));*/
        
        result = &result;
    }
    else
        throw runtime_error(string("bad ") + " element");

    return result;
}

light* nodeToLight(TiXmlElement* Light)
{
	light *result;

	if(strcmp(Light->Value(),"pointlight")==0)
	{
		pointlight plight;
		TiXmlElement* element = Light->Value();

        if(element && strcmp(element->Value(),"position")==0)
            plight.setPos(nodeToVector(element));
        
        element=element->NextSiblingElement();

        if(element && strcmp(element->Value(),"color")==0)
            plight.setColor(nodeToVector(element));
        
        element=element->NextSiblingElement();

        if(element && strcmp(element->Value(),"ka")==0)
            plight.setKa(doubleVal(element,"ka"));
        
        result = &plight;

	}
	else
		throw runtime_error(string("bad ") + " element");

	return result;
}

int main(){
    TiXmlDocument doc("./scenes/sample-scene.xml");
    
    vector<camera> cameralist;
    vector<image> imagelist;
    vector<material> materialslist;
    vector<object> objectslist;
    vector<light> lightslist;

    if(!doc.LoadFile())
        throw runtime_error("bad parse");

    TiXmlElement* root=doc.RootElement();
    if(strcmp(root->Value(),"rt-scene")!=0)
        throw runtime_error(string("bad root: ")+ root->Value());
        
    for(TiXmlElement* a=root->FirstChildElement();a;a=a->NextSiblingElement())
    {
        if(strcmp(a->Value(),"camera")==0)
            cameralist.push_back(nodeToCamera(a));
        else if(strcmp(a->Value(),"image")==0)
            imagelist.push_back(nodeToImage(a));
        else if(strcmp(a->Value(),"materials")==0)
        {
        	for(TiXmlElement* b=a->FirstChildElement();b;b->NextSiblingElement())
        	{
        		materialslist.push_back(*(nodeToMaterial(b)));
        	}
           
        }
        else if(strcmp(a->Value(),"objects")==0)
        {    
        	for(TiXmlElement* b=a->FirstChildElement();b;b->NextSiblingElement())
        	{
        		objectslist.push_back(nodeToObject(b));
        	}
        }	

        else if(strcmp(a->Value(),"lights")==0)
        {
           for(TiXmlElement* b=a->FirstChildElement();b;b->NextSiblingElement())
        	{
        		lightslist.push_back(*(nodeToLight(b)));
        	}
        }	

        //need to edit this
        /*else if(strcmp(a->Value(),"integrator")==0)
            integratorlist.push_back(nodeToIntegrator(a));*/
    }
}
#include <exception>
#include <stdexcept> // std::runtime_error
#include <cstdlib> // EXIT_FAILURE
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm> //find()

// #include "inc/tinyxml/tinyxml.h"
// #include "inc/tinyxml/tinystr.h"
#include "tinyxml.h"
// #include "tinystr.h" //TinyXML
#include "scene.hpp"
#include "camera.hpp"
#include "image.hpp"
#include "materials.hpp"
#include "objects.hpp"
#include "lights.hpp"

void write_to_ppm(double ***arr,double w,double h)
{
    std::ofstream img ("image.ppm");
    img << "P3" <<std::endl;
    img << w <<" "<< h <<std::endl;
    img << "255" <<std::endl;

    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
        {
            int r = (int)255*arr[j][i][0];
            int g = (int)255*arr[j][i][1];
            int b = (int)255*arr[j][i][2];

            img << r <<" " << g <<" "<< b << "     ";
        }
        img<<std::endl;
    }

}


const char* textValue(TiXmlElement* e)
{
    TiXmlNode* first=e->FirstChild();
    if(first!=0 && first==e->LastChild() && first->Type()==TiXmlNode::TINYXML_TEXT)
        return first->Value();
    else
        throw std::runtime_error(std::string("bad ") + e->Value( ) + " element");
}

std::vector<double> nodeToVector(TiXmlElement* Vect, const char* attrib)
{
    std::string vect = Vect->Attribute(attrib);
    char* str = new char[vect.size()];
    strcpy(str, vect.c_str());

    std::stringstream ss(str);

    double xval; ss>>xval;
    double yval; ss>>yval;
    double zval; ss>>zval;

    std::vector<double> result_vect;
    result_vect.push_back(xval);
    result_vect.push_back(yval);
    result_vect.push_back(zval);
    return result_vect;
}

double doubleVal(TiXmlElement* dval, const char* attrib)
{
    std::string temp_str = dval->Attribute(attrib);
    char* str = new char[temp_str.size()];
    strcpy(str, temp_str.c_str());

    std::stringstream ss(str);
    double result; ss>>result;
    
    delete str;
    return result;
}

camera nodeToCamera(TiXmlElement* Camera)
{
    std::cout<<"*nodeToCamera() called*"<<std::endl;

    camera result;
    TiXmlElement* element = Camera->FirstChildElement();
    if(element && strcmp(element->Value(),"lookat")==0)
        result.setLookat(nodeToVector(element,"vector3"));

    element=element->NextSiblingElement();
    if(element && strcmp(element->Value(),"eye")==0)
        result.setEye(nodeToVector(element,"vector3"));

    element=element->NextSiblingElement();
    if(element && strcmp(element->Value(),"up")==0)
        result.setUp(nodeToVector(element,"vector3"));
    
    result.setThird();

    element=element->NextSiblingElement();
    if(element && strcmp(element->Value(),"fov")==0) //assume this to be in degrees
        result.setFov(doubleVal(element,"angle"));

    element=element->NextSiblingElement();
    if(element && strcmp(element->Value(),"near")==0)
        result.setNear(doubleVal(element,"double"));
    
    element=element->NextSiblingElement();
    if(element && strcmp(element->Value(),"far")==0)
        result.setFar(doubleVal(element,"double"));
    
    std::cout<<"*Camera Created*"<<std::endl;

    return result;
}

image nodeToImage(TiXmlElement* Image)
{
    std::cout<<"*nodeToImage() called*"<<std::endl;

	image result;
	TiXmlElement* element = Image->FirstChildElement();
	if(element && strcmp(element->Value(),"width")==0)
    {
        std::cout<<"*Image width being set*"<<std::endl;
		result.setWidth(doubleVal(element,"double"));
        std::cout<<"*Image width was succesfully set*"<<std::endl;
    }
	
    element=element->NextSiblingElement();
	if(element && strcmp(element->Value(),"height")==0)
    {
        std::cout<<"*Image height being set*"<<std::endl;
		result.setHeight(doubleVal(element,"double"));
        std::cout<<"*Image height was succesfully set*"<<std::endl;
    }
	
    element=element->NextSiblingElement();
	if(element && strcmp(element->Value(),"bgcolor")==0)
		result.setBgcolor(nodeToVector(element,"color"));
	
    std::cout<<"*Image Created*"<<std::endl;

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
            sim_mat.setDiffuse(nodeToVector(element,"color"));
        
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"specular")==0)
            sim_mat.setSpecular(nodeToVector(element,"color"));
        
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"reflect")==0)
            sim_mat.setReflect(nodeToVector(element,"color"));
        
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"transmit")==0)
            sim_mat.setTransmit(nodeToVector(element,"color"));
        
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"eta")==0)
            sim_mat.setEta(doubleVal(element,"double"));
        
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"n")==0)
            sim_mat.setN(doubleVal(element,"double"));
        
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"isreflect")==0)
            sim_mat.setIsreflect(strcmp(element->Attribute("isreflect"),"true"));
        
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"istransmit")==0)
            sim_mat.setIstransmit(strcmp(element->Attribute("istransmit"),"true"));

        result = &sim_mat;
    }
    else
        throw std::runtime_error(std::string("bad ") + " element");

	return result;
}

std::shared_ptr<object> nodeToObject(TiXmlElement* Object, scene scene_obj) //INCOMPLETE!
{
    const char* mat_name;
    if((mat_name = Object->Attribute("material")) && strcmp(Object->Value(),"sphere")==0) //sphere object
    {
        std::vector<material> materialslist = scene_obj.getMaterials();
        std::vector<std::string> mat_names;//to store the ID of the materials in materialslist
        for (std::vector<material>::iterator it = materialslist.begin() ; it != materialslist.end(); ++it)
        {
            mat_names.push_back((*it).getID());//extracting material IDs
        }
        std::string search_mat(mat_name);//material ID to be searched (from scene file)
        std::vector<std::string>::iterator it_str;
        it_str =  find(mat_names.begin(),mat_names.end(),search_mat);
        
        sphere* sph_obj = new sphere();

        if(it_str!=mat_names.end())
        {
            sph_obj->setMaterial(*it_str);//calls the superclass function
        }
        else
            throw std::runtime_error(std::string("material ") + " for sphere object not found");

        TiXmlElement* element = Object->FirstChildElement();

        if(element && strcmp(element->Value(),"center")==0)
            sph_obj->setCenter(nodeToVector(element,"vector3"));
        
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"radius")==0)
            sph_obj->setRadius(doubleVal(element,"double"));
        
        return std::shared_ptr<object> (sph_obj);
    }
    else
        throw std::runtime_error(std::string("bad ") + " element");

}

light* nodeToLight(TiXmlElement* Light)
{
	light *result;

	if(strcmp(Light->Value(),"pointlight")==0) //point light source
	{
		pointlight plight;
		TiXmlElement* element = Light->FirstChildElement();

        if(element && strcmp(element->Value(),"position")==0)
            plight.setPos(nodeToVector(element,"vector3"));
        
        element=element->NextSiblingElement();

        if(element && strcmp(element->Value(),"color")==0)
            plight.setColor(nodeToVector(element,"color"));
        
        element=element->NextSiblingElement();

        if(element && strcmp(element->Value(),"ka")==0)
            plight.setKa(doubleVal(element,"double"));
        
        result = &plight;

	}
	else
		throw std::runtime_error(std::string("bad ") + " element");

	return result;
}

integrator* nodeToIntegrator(TiXmlElement* Integrator)
{
    integrator *result;
    if(strcmp(Integrator->Value(),"whitted")==0)//whitted integrator
    {
        whitted whit_intg;
        TiXmlElement* element = Integrator->FirstChildElement();

        if(element && strcmp(element->Value(),"depth-of-recursion")==0)
            whit_intg.setDepth(int(doubleVal(element,"int")));
        
        result = &whit_intg;
    }
    else
        throw std::runtime_error(std::string("bad ") + " element");


    return result;
}

int main(){
    TiXmlDocument doc("./scenes/sample-scene.xml");
    
    scene scene_obj;
    /*vector<material> materialslist;
    vector<shared_ptr<object>> objectslist;
    vector<light> lightslist;*/

    if(!doc.LoadFile())
        throw std::runtime_error("bad parse");

    TiXmlElement* root=doc.RootElement();
    if(strcmp(root->Value(),"rt-scene")!=0)
    {
        std::cout<<"Root->Value()"<<root->Value()<<std::endl;
        throw std::runtime_error(std::string("bad root: ")+ root->Value());
    }
        
    for(TiXmlElement* a=root->FirstChildElement();a;a=a->NextSiblingElement())
    {
        std::cout<<"Root->Child being parsed: "<<a->Value()<<std::endl;
        if(strcmp(a->Value(),"camera")==0)
        {   
            std::cout<<"**Parsing Camera**"<<std::endl;
            scene_obj.setCamera(nodeToCamera(a));
        }
        else if(strcmp(a->Value(),"image")==0)
        {
            std::cout<<"**Parsing Image**"<<std::endl;
            scene_obj.setImage(nodeToImage(a));
        }
        /*else if(strcmp(a->Value(),"materials")==0)
        {
            for(TiXmlElement* b=a->FirstChildElement();b;b->NextSiblingElement())
            {
                materialslist.push_back(*(nodeToMaterial(b)));
            }
            scene_obj.setMaterials(materialslist);
        }
        else if(strcmp(a->Value(),"objects")==0)
        {    
        	for(TiXmlElement* b=a->FirstChildElement();b;b->NextSiblingElement())
        	{
        		objectslist.push_back(nodeToObject(b,scene_obj));
        	}
            scene_obj.setObjects(objectslist);
        }	
        else if(strcmp(a->Value(),"lights")==0)
        {
           for(TiXmlElement* b=a->FirstChildElement();b;b->NextSiblingElement())
        	{
        		lightslist.push_back(*(nodeToLight(b)));
        	}
            scene_obj.setLights(lightslist);
        }	
        else if(strcmp(a->Value(),"integrator")==0)
            scene_obj.setIntegrator(*(nodeToIntegrator(a)));
*/
    }

    /*scene_obj.rotation_matrix_formation();
    scene_obj.translation_matrix_formation();
    scene_obj.inv_translation_matrix_formation();
    scene_obj.inv_rotation_matrix_formation();*/

    int w = scene_obj.getImage().getWidth();
    int h = scene_obj.getImage().getHeight();

    double ***img_arr;
    img_arr = new double **[w];
    for(int i=0;i<w;i++)
    {
        img_arr [i] = new double*[h];
        for(int j=0;j<h;j++)
            img_arr[i][j] = new double[3];
    }

    std::vector<double> v = scene_obj.getImage().getBgcolor();
    for(int i=0;i<w;i++)
    {
        for(int j=0;j<h;j++)
        {
            img_arr[i][j][0] = v[0];
            img_arr[i][j][1] = v[1];
            img_arr[i][j][2] = v[2];
            // if(i==0 && j==0) std::cout<<"("<<v[0]<<","<<v[1]<<","<<v[2]<<")"<<std::endl;
        }
    }

    write_to_ppm(img_arr,w,h);
}
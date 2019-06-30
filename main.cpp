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
    // std::cout<<"*nodeToCamera() called*"<<std::endl;

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
    
    // std::cout<<"*Camera Created*"<<std::endl;

    return result;
}

image nodeToImage(TiXmlElement* Image)
{
    // std::cout<<"*nodeToImage() called*"<<std::endl;

	image result;
	TiXmlElement* element = Image->FirstChildElement();
	if(element && strcmp(element->Value(),"width")==0)
    {
        // std::cout<<"*Image width being set*"<<std::endl;
		result.setWidth(doubleVal(element,"double"));
        // std::cout<<"*Image width was succesfully set*"<<std::endl;
    }
	
    element=element->NextSiblingElement();
	if(element && strcmp(element->Value(),"height")==0)
    {
        // std::cout<<"*Image height being set*"<<std::endl;
		result.setHeight(doubleVal(element,"double"));
        // std::cout<<"*Image height was succesfully set*"<<std::endl;
    }
	
    element=element->NextSiblingElement();
	if(element && strcmp(element->Value(),"bgcolor")==0)
		result.setBgcolor(nodeToVector(element,"color"));
	
    // std::cout<<"*Image Created*"<<std::endl;

	return result;
}

material* nodeToMaterial(TiXmlElement* Material)
{
    // std::cout<<"*nodeToMaterial() called*"<<std::endl;
    const char *id;
    if((id = Material->Attribute("id")) && strcmp(Material->Value(),"simplemat")==0) //simplemat material
    {
        // std::cout<<"*Creating simplemat material*"<<std::endl;
        simplemat* sim_mat = new simplemat(id); //creating a simplemat object
        
        TiXmlElement* element = Material->FirstChildElement();

        // std::cout<<"*Parsing colors*"<<std::endl;
        if(element && strcmp(element->Value(),"diffuse")==0)
            sim_mat->setDiffuse(nodeToVector(element,"color"));
        
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"specular")==0)
            sim_mat->setSpecular(nodeToVector(element,"color"));
        
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"reflect")==0)
            sim_mat->setReflect(nodeToVector(element,"color"));
        
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"transmit")==0)
            sim_mat->setTransmit(nodeToVector(element,"color"));
        
        // std::cout<<"*Parsing eta*"<<std::endl;
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"eta")==0)
            sim_mat->setEta(doubleVal(element,"double"));
        
        // std::cout<<"*Parsing n*"<<std::endl;
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"n")==0)
            sim_mat->setN(doubleVal(element,"double"));
        
        // std::cout<<"*Parsing isreflect*"<<std::endl;
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"isreflect")==0)
            sim_mat->setIsreflect(strcmp(element->Attribute("bool"),"true"));
        
        // std::cout<<"*Parsing istransmit*"<<std::endl;
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"istransmit")==0)
            sim_mat->setIstransmit(strcmp(element->Attribute("bool"),"true"));

        // std::cout<<"*Material Created*"<<std::endl;
        return sim_mat;
    }
    else
        throw std::runtime_error(std::string("bad ") + "material element: " + Material->Value());
}

std::shared_ptr<object> nodeToObject(TiXmlElement* Object, scene scene_obj)
{
    const char* mat_name;
    if((mat_name = Object->Attribute("material")) && strcmp(Object->Value(),"sphere")==0) //sphere object
    {
        std::vector<material* > materialslist = scene_obj.getMaterials();
        std::vector<std::string> mat_names;//to store the ID of the materials in materialslist
        for (std::vector<material* >::iterator it = materialslist.begin() ; it != materialslist.end(); ++it)
        {
            mat_names.push_back((*it)->getID());//extracting material IDs from shared_ptr<material> element
        }
        std::string search_mat(mat_name);//material ID to be searched (from scene file)
        std::vector<std::string>::iterator it_str;
        it_str =  std::find(mat_names.begin(),mat_names.end(),search_mat);
        
        sphere* sph_obj = new sphere();

        if(it_str!=mat_names.end())
        {
            sph_obj->setMaterial(materialslist[it_str-mat_names.begin()]);//calls the superclass function
        }
        else
            throw std::runtime_error(std::string("material ") + std::string(mat_name) + " for sphere object not found");

        TiXmlElement* element = Object->FirstChildElement();

        if(element && strcmp(element->Value(),"center")==0)
            sph_obj->setCenter(nodeToVector(element,"vector3"));
        
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"radius")==0)
            sph_obj->setRadius(doubleVal(element,"double"));
        
        return std::shared_ptr<object> (sph_obj);
    }
    else
        throw std::runtime_error(std::string("bad ") + "object element: " + Object->Value());

}

light* nodeToLight(TiXmlElement* Light)
{
	if(strcmp(Light->Value(),"pointlight")==0) //point light source
	{
		pointlight* plight = new pointlight();
		TiXmlElement* element = Light->FirstChildElement();

        if(element && strcmp(element->Value(),"position")==0)
            plight->setPos(nodeToVector(element,"vector3"));
        
        element=element->NextSiblingElement();

        if(element && strcmp(element->Value(),"color")==0)
            plight->setColor(nodeToVector(element,"color"));
        
        element=element->NextSiblingElement();

        if(element && strcmp(element->Value(),"ka")==0)
            plight->setKa(doubleVal(element,"double"));
        
        return plight;
	}
	else
		throw std::runtime_error(std::string("bad ") + "light element: " + Light->Value());
}

std::shared_ptr<integrator> nodeToIntegrator(TiXmlElement* Integrator)
{
    // std::cout<<"*nodeToIntegrator() called*"<<std::endl;
    if(strcmp(Integrator->Value(),"whitted")==0)//whitted integrator
    {
        whitted* whit_intg = new whitted();
        TiXmlElement* element = Integrator->FirstChildElement();

        if(element && strcmp(element->Value(),"depth-of-recursion")==0)
        {
            // std::cout<<"*Parsing depth-of-recursion*"<<std::endl;
            whit_intg->setDepth(int(doubleVal(element,"int")));
        }

        // std::cout<<"*Whitted integrator created*"<<std::endl;
        return std::shared_ptr<integrator>(whit_intg);
    }
    else
        throw std::runtime_error(std::string("bad ") + "integrator element: " + Integrator->Value());

}

int main(){
    TiXmlDocument doc("./scenes/sample-scene.xml");
    
    scene scene_obj;
    std::vector<material* > materialslist;
    std::vector<std::shared_ptr<object> > objectslist;
    std::vector<light* > lightslist;

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
        else if(strcmp(a->Value(),"materials")==0)
        {
            std::cout<<"**Parsing Materials**"<<std::endl;
            int i=0;
            for(TiXmlElement* b=a->FirstChildElement();b;b=b->NextSiblingElement())
            {
                std::cout<<"**Parsing Material**"<<i++<<std::endl;
                materialslist.push_back(nodeToMaterial(b));
            }
            scene_obj.setMaterials(materialslist);
        }
        else if(strcmp(a->Value(),"objects")==0)
        {
            std::cout<<"**Parsing Objects**"<<std::endl;
        	for(TiXmlElement* b=a->FirstChildElement();b;b=b->NextSiblingElement())
        	{
        		objectslist.push_back(nodeToObject(b,scene_obj));
        	}
            scene_obj.setObjects(objectslist);
        }	
        else if(strcmp(a->Value(),"lights")==0)
        {
            std::cout<<"**Parsing Lights**"<<std::endl;
            for(TiXmlElement* b=a->FirstChildElement();b;b=b->NextSiblingElement())
        	{
        		lightslist.push_back(nodeToLight(b));
        	}
            scene_obj.setLights(lightslist);
        }	
        else if(strcmp(a->Value(),"integrator")==0)
            {
                std::cout<<"**Parsing Integrator**"<<std::endl;
                scene_obj.setIntegrator(nodeToIntegrator(a->FirstChildElement()));
            }
    }
    std::cout<<"******Parsing complete******"<<std::endl;

    scene_obj.rotation_matrix_formation();
    std::cout<<"*Rotation matrix formed*"<<std::endl;
    scene_obj.translation_matrix_formation();
    std::cout<<"*Translation matrix formed*"<<std::endl;
    scene_obj.inv_translation_matrix_formation();
    std::cout<<"*Inv translation matrix formed*"<<std::endl;
    scene_obj.inv_rotation_matrix_formation();
    std::cout<<"*Inv Rotation matrix formed*"<<std::endl;
    scene_obj.init_img_arr();
    std::cout<<"*Image array formed*"<<std::endl;
     //scene_obj.getCamera().setThird();
    scene_obj.render();

    std::cout<<"******Rendering complete******"<<std::endl;
}
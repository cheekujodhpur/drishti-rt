#include <exception>
#include <stdexcept> // runtime_error
#include <cstdlib> // EXIT_FAILURE
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "tinyxml.h"
#include "camera.hpp"
#include "image.hpp"
#include "materials.hpp"
/*#include "objects.hpp"
#include "lights.hpp"*/

using namespace std;

// Extracts the content of an XML element that contains only text
const char* textValue(TiXmlElement* e)
{
    TiXmlNode* first=e->FirstChild();
    if(first!=0 && first==e->LastChild() && first->Type()==TiXmlNode::TINYXML_TEXT)
        return first->Value();
    else
        throw runtime_error(string("bad ") + e->Value( ) + " element");
}

vector<double> nodeTovector(TiXmlElement* Vect)
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

    double result = atof(str);
    delete str;
    return result;
}

camera nodeToCamera(TiXmlElement* Camera)
{
    camera result;
    TiXmlElement* element = Camera->FirstChildElement();
    if(element && strcmp(element->Value(),"lookat")==0)
        result.setLookat(nodeTovector(element));

    element=element->NextSiblingElement();
    if(element && strcmp(element->Value(),"eye")==0)
        result.setEye(nodeTovector(element));

    element=element->NextSiblingElement();
    if(element && strcmp(element->Value(),"up")==0)
        result.setUp(nodeTovector(element));
    
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
		result.setBgcolor(nodeTovector(element));
	
	return result;
}

material* nodeToMaterials(TiXmlElement* Material)
{
	material *result;

	TiXmlElement* mat = Material->FirstChildElement();
    const char *id;
    if((id = mat->Attribute("id")) && strcmp(mat->Value(),"simplemat")==0) //simplemat material
    {
        simplemat sim_mat("simplemat"); //creating a simplemat object
        
        TiXmlElement* element = mat->FirstChildElement();

        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"diffuse")==0)
            sim_mat.setDiffuse(nodeTovector(element));
        
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"specular")==0)
            sim_mat.setSpecular(nodeTovector(element));
        
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"reflect")==0)
            sim_mat.setReflect(nodeTovector(element));
        
        element=element->NextSiblingElement();
        if(element && strcmp(element->Value(),"transmit")==0)
            sim_mat.setTransmit(nodeTovector(element));
        
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
        throw runtime_error(string("bad ") + mat->Value( ) + " element");

	return result;
}

/*object* nodeToObjects()
{

}

light* nodeToLights()
{

}*/

int main(){
    TiXmlDocument doc("./scenes/sample-scene.xml");
    
    vector<camera> cameralist;
    vector<image> imagelist;
    vector<material> materialslist;
    /*vector<object> objectlist;
    vector<light> lightslist;*/

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
        		materialslist.push_back(*(nodeToMaterials(b)));
        	}
           
        }
        /*else if(strcmp(a->Value(),"objects")==0)
        {    
        	for(TiXmlElement* b=a->FirstChildElement();b;b->NextSiblingElement())
        	{
        		objectslist.push_back(nodeToObjects(b));
        	}
        }	

        else if(strcmp(a->Value(),"lights")==0)
        {
           for(TiXmlElement* b=a->FirstChildElement();b;b->NextSiblingElement())
        	{
        		lightslist.push_back(nodeToLights(b));
        	}
        }*/	

        //need to edit this
        /*else if(strcmp(a->Value(),"integrator")==0)
            integratorlist.push_back(nodeToIntegrator(a));*/
    }
}
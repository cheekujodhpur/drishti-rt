#include <exception>
#include <stdexcept> // runtime_error
#include <cstdlib> // EXIT_FAILURE
#include <vector>
#include <string.h>
#include <sstream>
#include <iostream>
#include "tinyxml.h"
#include "camera.hpp"
// #include "image.hpp"
// #include "materials.hpp"
// #include "objects.hpp"
// #include "lights.hpp"
// #include "integrator.hpp"

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
    delete str;
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

int main(){
    TiXmlDocument doc("./scenes/sample-scene.xml");
    
    if(!doc.LoadFile())
        throw runtime_error("bad parse");

    TiXmlElement* root=doc.RootElement();
    if(strcmp(root->Value(),"rt-scene")!=0)
        throw runtime_error(string("bad root: ")+ root->Value());
        
    for(TiXmlElement* a=root->FirstChildElement();a;a=a->NextSiblingElement()){
        if(strcmp(a->Value(),"camera")==0)
            objectlist.push_back(nodeToCamera(a));
        /*else if(strcmp(a->Value(),"image")==0)
            objectlist.push_back(nodeToImage(a));
        else if(strcmp(a->Value(),"materials")==0)
            objectlist.push_back(nodeToMaterials(a));
        else if(strcmp(a->Value(),"objects")==0)
            objectlist.push_back(nodeToObjects(a));
        else if(strcmp(a->Value(),"lights")==0)
            objectlist.push_back(nodeToLights(a));
        else if(strcmp(a->Value(),"integrator")==0)//need to edit this
            objectlist.push_back(nodeToIntegrator(a));*/
        }
}
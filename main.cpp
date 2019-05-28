int main(){
    using namespace std;
    TiXmlDocument doc("./scenes/sample-scene.xml");
    
    if(!doc.LoadFile())
        throw runtime_error("bad parse");

    TiXmlElement* root=doc.RootElement();
    if(strcmp(root->value(),"rt-scene")!=0)
        throw runtime_error(string("bad root: ")+ root->value());
        
    for(TiXmlElement* a=root->FirstChildElement();a;a=a->NextSiblingElement()){
        if(strcmp(a->value(),"camera")==0)
            objectlist.push_back(nodeToCamera(a));
        else if(strcmp(a->value(),"image")==0)
            objectlist.push_back(nodeToImage(a));
        else if(strcmp(a->value(),"materials")==0)
            objectlist.push_back(nodeToMaterials(a));
        else if(strcmp(a->value(),"objects")==0)
            objectlist.push_back(nodeToObjects(a));
        else if(strcmp(a->value(),"lights")==0)
            objectlist.push_back(nodeToLights(a));
        else if(strcmp(a->value(),"integrator")==0)//need to edit this
            objectlist.push_back(nodeToIntegrator(a));
        }
}

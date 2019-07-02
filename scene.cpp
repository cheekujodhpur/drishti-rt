#include "scene.hpp"
#include <stddef.h> //NULL
#include <limits>
#include <math.h>
#include <fstream>
#include <iostream>
#include <typeinfo>
#include <string.h>

const double INF = std::numeric_limits<double>::infinity();

//array*array
std::vector<std::vector<double> > mat_mult(std::vector<std::vector<double> > a,std::vector<std::vector<double> > b)
{
	int num_row1 = a.size();
	int num_column1 = a[0].size();

	int num_row2 = b.size();
	int num_column2 = b[0].size();


	std::vector<double> x(4,0);

	std::vector<std::vector<double> > c(4,x);

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			for(int k=0;k<4;k++)
			{
				c[i][j]+=a[i][k]*b[k][j];
			}
		}
	}

	return c;


}

//array*vector
std::vector<double> mat_mult(std::vector<std::vector<double> > a,std::vector<double> b)
{
	std::vector<double> c(4,0);
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			c[i]+=a[i][j]*b[j];
		}

	}

	return c;
}

std::vector<std::vector<double> > transpose(std::vector<std::vector<double> > a)
{	std::vector<double> x(4,0);
	std::vector<std::vector<double> > v(4,x);

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			v[j][i]=a[i][j];
		}
	}
		return v;
}

void scene::setCamera(camera cam0)
{
	cam = cam0;
}
void scene::setImage(image img0)
{
	img = img0;
}
void scene::setIntegrator(std::shared_ptr<integrator> intg0)
{
	intg = intg0;
}
void scene::setMaterials(std::vector<material* > materials)
{
	materialslist = materials;
}
void scene::setObjects(std::vector<std::shared_ptr<object> > objects)
{
	objectslist = objects;
}
void scene::setLights(std::vector<light* > lights)
{
	lightslist = lights;
}

void scene::init_img_arr()
{
	int w = this->getImage().getWidth();
    int h = this->getImage().getHeight();
	this->img_arr = new double **[w];
    for(int i=0;i<w;i++)
    {
        img_arr [i] = new double*[h];
        for(int j=0;j<h;j++)
            img_arr[i][j] = new double[3];
    }
    
    std::vector<double> v = this->getImage().getBgcolor();
    for(int i=0;i<w;i++)
    {
        for(int j=0;j<h;j++)
        {
        	//with ambient-->
            img_arr[i][j][0] = v[0];
            img_arr[i][j][1] = v[1];
            img_arr[i][j][2] = v[2];
            
        	//without ambient-->
            /*img_arr[i][j][0] = 0;
            img_arr[i][j][1] = 0;
            img_arr[i][j][2] = 0;*/
        }
    }
}

camera scene::getCamera()
{
	return cam;
}
image scene::getImage()
{
	return img;
}
std::shared_ptr<integrator> scene::getIntegrator()
{
	return intg;
}
std::vector<material* > scene::getMaterials()
{
	return materialslist;
}
std::vector<std::shared_ptr<object> > scene::getObjects()
{
	return objectslist;
}
std::vector<light* > scene::getLights()
{
	return lightslist;
}

void scene::rotation_matrix_formation()
{
	std::vector<double> x = cam.getLookat().getVector();
	std::vector<double> z = cam.getUp().getVector();
	std::vector<double> y = cam.getThird().getVector();//need to define a getVector() in vec class
	x.push_back(0);
	y.push_back(0);
	z.push_back(0);
	std::vector<double> fourth(3,0);  //supposed to be fourth row of matrix
	fourth.push_back(1);
	
	rotation_mat.push_back(x);
	rotation_mat.push_back(y);
	rotation_mat.push_back(z);
	rotation_mat.push_back(fourth);

}
void scene::inv_rotation_matrix_formation()
{
	std::vector<std::vector<double> > v = transpose(rotation_mat);
	inv_rotation_mat = v;
}

void scene::inv_translation_matrix_formation()
{
	std::vector<double> fourth = cam.getEye().getVector();
	std::vector<double> x;
	std::vector<double> y;
	std::vector<double> z;
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


	std::vector<double> a(3,0);
	a.push_back(1);

	inv_translation_mat.push_back(x);
	inv_translation_mat.push_back(y);
	inv_translation_mat.push_back(z);
	inv_translation_mat.push_back(a);


}
void scene::translation_matrix_formation()
{
	std::vector<double> fourth = cam.getEye().getVector();  //supposed to be fourth column of translation matrix
	std::vector<double> x;
	std::vector<double> y;
	std::vector<double> z;
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

	std::vector<double> a(3,0);
	a.push_back(1);

	translation_mat.push_back(x);
	translation_mat.push_back(y);
	translation_mat.push_back(z);
	translation_mat.push_back(a);

}

vec scene::world_to_camera(vec world_c)
{
    std::vector<double> temp = world_c.getVector();
    temp.push_back(1);
    std::vector<double> temp2(4,0); //4-vector
    temp2 = mat_mult(mat_mult(rotation_mat,translation_mat),temp);

    for(int i=0;i<3;i++)
    	temp[i] = temp2[i]/temp2[3];
    
    temp.pop_back();//removing the homogeneous coordinate
    return vec(temp);
}


vec scene::camera_to_world(vec camera_c)
{
    std::vector<double> temp = camera_c.getVector();
    temp.push_back(1);
    std::vector<double> temp2(4,0); //4-vector
    temp2 = mat_mult(mat_mult(inv_translation_mat,inv_rotation_mat),temp);

    for(int i=0;i<3;i++)
    	temp[i] = temp2[i]/temp2[3];

    temp.pop_back();//removing the homogeneous coordinate
    return vec(temp);
}

std::shared_ptr<object> scene::intersect(ray Ray)
{	
	double mini = INF;
	int index = -1;
	for(int i=0;i<objectslist.size();i++)
    {
    	double x = objectslist[i]->intersect(Ray);
    	if(x < mini)
    	{
    		mini = x;
    		index = i;
    	}
    }

    if(index!=-1)
    {
    	return objectslist[index];
    }
	else
		return NULL;
}

void scene::write_to_ppm()
{
	int w = img.getWidth();
	int h = img.getHeight();
    std::ofstream imgstream ("image9.ppm");
    imgstream << "P3" <<std::endl;
    imgstream << w <<" "<< h <<std::endl;
    imgstream << "255" <<std::endl;

    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
        {
            int r = (int)255 * img_arr[j][i][0];
            int g = (int)255 * img_arr[j][i][1];
            int b = (int)255 * img_arr[j][i][2];

            imgstream << r <<" " << g <<" "<< b << "     ";
        }
        imgstream<<std::endl;
    }

}

void scene::render()
{
    double Wres = img.getWidth();
    double Hres = img.getHeight();
    double fov = cam.getFov();
    double H_phy = 2.0*tan((M_PI/180)*(0.5*fov)); // (fov/2) is the half angle height-wise
    double delta_H = H_phy/Hres;
    double delta_W = delta_H;
    double W_phy = delta_W*Wres;

    double ambient_factor = 0.05;
  //  std::cout<<Wres<<" "<<Hres<<" "<<fov<<" "<<H_phy<<" "<<delta_H<<" "<<delta_W<<" "<<W_phy<<std::endl;

    vec y = cam.getThird();y.normalise();
    vec z = cam.getUp();z.normalise();
    vec x = cam.getLookat();x.normalise();
  //  std::cout<<"Entering loop"<<std::endl;
    for(int i=0;i<Wres;i++)
    {
        for(int j=0;j<Hres;j++)
        {	//std::cout<<"Yo"<<std::endl;
            vec r;
            std::vector<double> temp_R_in_cam(3,0);
            temp_R_in_cam[0] = 1; //these are ACTUALLY in camera coordinates
            temp_R_in_cam[1] = (0.5*Wres-i)*delta_W;
            temp_R_in_cam[2] = (0.5*Hres-j)*delta_H;
            vec R_in_cam(temp_R_in_cam);
            /*for(int k=0;k<3;k++)
            {//	std::cout<<y[k]<<std::endl;
				r[k]= (0.5*Wres-i)*delta_W*y[k] + (0.5*Hres-j)*delta_H*z[k];
		//		std::cout<<r[k]<<" "<<x[k]<<std::endl;
				R_in_world[k]= r[k] + x[k];
            }*/
            vec R_in_world = camera_to_world(R_in_cam); //transforming direcion vector to world
            vec origin = cam.getEye();//in world coordinates
        //    std::cout<<"About to transform"<<std::endl;

            /*if((i==520) && (j==384))
            {
            	std::cout<<"testing slightly off-center (to the right) pixel"<<std::endl;
            }*/

            R_in_world.normalise();
            ray viewingRay(origin,R_in_world); //ray generated, originating from camera 

        	//call intersect function on scene object "this": returns the nearest one which intersects
            std::shared_ptr<object> nearest_obj = this->intersect(viewingRay);

            if(nearest_obj!=NULL)
            {
            	//extract colour out of that material and fill into arr[i][j][]
            	//assuming simplemat
            	simplemat* sim_mat = static_cast<simplemat*>(nearest_obj->getMaterial());
            	
                std::vector<double> diff_color = sim_mat->getDiffuse(); 
                for(int k=0;k<3;k++)
                    img_arr[i][j][k] = diff_color[k]*ambient_factor;

                for(int k=0;k<lightslist.size();k++)
		        {
		        	light* lightsource = lightslist[k];
		        	if(strcmp(lightsource->source_type().c_str(),"pointlight")==0)//problematic point
		    		{
		    			// std::cout<<"Entering shadow mode"<<std::endl;
		    			vec lightpos;
		    			pointlight* plight = static_cast<pointlight*>(lightsource);
		    			lightpos = plight->getPos();
		    			
		    			double intersect_param = nearest_obj->intersect(viewingRay);
		    			vec intersectPoint = viewingRay.get_point(intersect_param);
		    			vec shadow_dirn = (lightpos - intersectPoint);
		    			shadow_dirn.normalise();
		    			
		    			ray shadowRay(intersectPoint,shadow_dirn);

		    			std::shared_ptr<object> blocking_object = this->intersect(shadowRay);

		    			double block_point_param = 0;//initialisation for block point
		    			double light_source_param = 0;//initialisation for light source point
		    			
		    			if(blocking_object != NULL)
		    			{
		    				block_point_param = blocking_object->intersect(shadowRay);
			    			light_source_param = shadowRay.get_param(lightpos);
			    			/*for(int l=0;l<3;l++)
			    			{
			    				if(shadow_dirn[l]!=0)
			    				{
			    					light_source_param = (lightpos[l]-intersectPoint[l])/shadow_dirn[l];
			    					break;
			    				}
			    			}*/
		    			}
		    			
		    			if(blocking_object == NULL||light_source_param<block_point_param||block_point_param<eff_zero_shadow)
		    			{
		    				std::vector<double> lightcolor = plight->getColor();
		    				vec viewing_dirn = viewingRay.get_direction();
		    				double cosine = -(shadow_dirn.dot(viewing_dirn));
		    				cosine = std::max(cosine,0.0);

		    				for(int l=0;l<3;l++)
                				img_arr[i][j][l] += lightcolor[l]*diff_color[l]*cosine;
		    			}
		    		}
		        }
            }
        }
    }
    std::cout<<"Out of loops"<<std::endl;
    write_to_ppm();
}


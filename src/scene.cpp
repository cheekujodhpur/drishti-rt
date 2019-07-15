#include "scene.hpp"
#include <stddef.h> //NULL
#include <limits>
#include <cmath>
#include <fstream>
#include <iostream>
#include <typeinfo>
#include <string.h>
#include <stdlib.h>

//double drand48(void);

const double INF = std::numeric_limits<double>::infinity();

const int n = 2;
const double n_inv = 1.0/n;

// const int no_of_rays = 100;

//array*array
std::vector<std::vector<double> > mat_mult(std::vector<std::vector<double> > a,std::vector<std::vector<double> > b)
{
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

void scene::setAmbient(double ka0)
{
	ka = ka0;
}
void scene::setCamera(camera cam0)
{
	cam = cam0;
}
void scene::setImage(image img0)
{
	img = img0;
}
void scene::setIntegrator(integrator* intg0)
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
	int w = img.getWidth();
    int h = img.getHeight();
	this->img_arr = new double **[w];
    for(int i=0;i<w;i++)
    {
        img_arr [i] = new double*[h];
        for(int j=0;j<h;j++)
            img_arr[i][j] = new double[3];
    }
    
    std::vector<double> v = img.getBgcolor();
    for(int i=0;i<w;i++)
    {
        for(int j=0;j<h;j++)
        {
        	//with ambient-->
            img_arr[i][j][0] = v[0];
            img_arr[i][j][1] = v[1];
            img_arr[i][j][2] = v[2];
        }
    }
}

double scene::getAmbient()
{
	return ka;
}
camera scene::getCamera()
{
	return cam;
}
image scene::getImage()
{
	return img;
}
integrator* scene::getIntegrator()
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
	std::vector<double> x = cam.getLookat().v;
	std::vector<double> z = cam.getUp().v;
	std::vector<double> y = cam.getThird().v;//need to define a v in vec class
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
	std::vector<double> fourth = cam.getEye().v;
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

	inv_translation_mat.push_back(x);
	inv_translation_mat.push_back(y);
	inv_translation_mat.push_back(z);
	inv_translation_mat.push_back(a);


}
void scene::translation_matrix_formation()
{
	std::vector<double> fourth = cam.getEye().v;  //supposed to be fourth column of translation matrix
	std::vector<double> x;
	std::vector<double> y;
	std::vector<double> z;
	x.push_back(1);
	x.push_back(0);
	x.push_back(0);
	x.push_back(-fourth[0]);

	y.push_back(0);
	y.push_back(1);
	y.push_back(0);
	y.push_back(-fourth[1]);

	z.push_back(0);
	z.push_back(0);
	z.push_back(1);
	z.push_back(-fourth[2]);

	std::vector<double> a(3,0);
	a.push_back(1);

	translation_mat.push_back(x);
	translation_mat.push_back(y);
	translation_mat.push_back(z);
	translation_mat.push_back(a);

}

vec scene::world_to_camera(vec world_c)
{
    std::vector<double> temp = world_c.v;
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
    std::vector<double> temp = camera_c.v;
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
	for(unsigned int i=0;i<objectslist.size();i++)
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

void scene::write_to_ppm(char fname[])
{
    // std::cout << "writing to  " << fname << std::endl;
	int w = img.getWidth();
	int h = img.getHeight();
    std::ofstream imgstream (fname);
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

ray* scene::generate_refract(ray incidentRay,vec N, vec origin,double refract_index)
{
	vec Incident = incidentRay.get_direction();
	double n_i_t;
	double cosine = (-Incident).dot(N);
	if(cosine>0) //going into the object
		n_i_t = 1.0/refract_index;
	else if(cosine<0) //going out of the object
		n_i_t = refract_index;
	else
		return NULL;

	if(1 + n_i_t*n_i_t*(cosine*cosine - 1)<0)
		return NULL;

	double beta = n_i_t*abs(cosine) - sqrt(1 + n_i_t*n_i_t*(cosine*cosine - 1));
	vec RefractedRaydirn = Incident*n_i_t + N*beta*((cosine>0)?1:-1);
	RefractedRaydirn.normalise();

	return new ray(origin,RefractedRaydirn);
}

std::vector<double> scene::radiance(ray viewingRay, int depth, int max_depth, unsigned short xsubi[])
{
    if(depth == max_depth)
        return std::vector<double>(3,0);//blank colour
	//call intersect function on scene object "this": returns the nearest one which intersects
    std::shared_ptr<object> nearest_obj = this->intersect(viewingRay);
    std::vector<double> result_color(3,0);

    if(nearest_obj!=NULL)
    {
    	simplemat* sim_mat = static_cast<simplemat*>(nearest_obj->getMaterial()); //assuming simplemat
    	bool isReflect = sim_mat->getIsReflect();
    	bool isTransmit = sim_mat->getIsTransmit();

    	double intersect_param = nearest_obj->intersect(viewingRay);
	    vec intersectPoint = viewingRay.get_point(intersect_param);

		vec normal = nearest_obj->getNormal(intersectPoint); 
		vec incident = viewingRay.get_direction();
		double refract_index = sim_mat->getEta();

		vec refl_dirn;
		vec trans_dirn;
		vec correct_normal;
		bool isFresnel = false;
		bool toReflect = false;
		bool toTransmit = false;
		double fresnel_refract;
    	double fresnel_reflect;
    	std::vector<double> refl_col(3,0);
    	std::vector<double> refr_col(3,0);
    	std::vector<double> reflectcolor(3,0);
    	std::vector<double> refractcolor(3,0);

    	if(!isReflect && !isTransmit) //diffuse object
    	{
    		//diffuse reflection
	        std::vector<double> diff_color = sim_mat->getDiffuse(); 

            if (sim_mat->getID() == "light") 
            {
                for(int k=0;k<3;k++)
                    result_color[k] = diff_color[k];
                return result_color;
            };

	        for(int k=0;k<3;k++)
	            result_color[k] = diff_color[k]*(this->getAmbient());

	        //generate ray in random direction

			double sq_cos_theta = erand48(xsubi);
			double cos_theta = sqrt(sq_cos_theta);
			double sin_theta = sqrt(1-sq_cos_theta);
			double phi = 2*M_PI*erand48(xsubi);

            vec nl = (normal.dot(incident) < 0) ? normal : -normal;
            std::vector <double> blank_y;
            blank_y.push_back(0);blank_y.push_back(0);blank_y.push_back(1);
            vec planar_one = vec(blank_y).cross(nl); 
            planar_one.normalise();
            vec planar_two = normal.cross(planar_one); 

            vec diffuse_reflect_dirn = 
			planar_two*sin_theta*cos(phi) + 
			planar_one*sin_theta*sin(phi) + 
			nl*cos_theta;

            diffuse_reflect_dirn.normalise();
            
            refl_dirn = diffuse_reflect_dirn;
            correct_normal = normal;
            toReflect = true;
            reflectcolor = sim_mat->getDiffuse();
    	}
    	
    	else
    	{
    		double cosine = (-incident).dot(normal);
    		if(isReflect && isTransmit)
    		{
				double rand_num = erand48(xsubi);
    			// double rand_num = (double) rand() / (RAND_MAX);
    			double R_0 = (refract_index-1)*(refract_index-1)/((refract_index+1)*(refract_index+1));
				fresnel_reflect = R_0 + (1 - R_0)*pow(1 - abs(cosine),5);
    			if(rand_num> 0.5) //reflection
    			{    				
	    			refl_dirn = incident + ((cosine<0)? -normal : normal)*(2*abs(cosine));
	    			correct_normal = (cosine<0)? -normal : normal; //cosine<0 if going out of object
    				isFresnel = true;
    				toReflect = true;
    				reflectcolor = sim_mat->getReflect();
    			}
    			else //refraction
    			{
	    			ray* refractedRay_ptr = generate_refract(viewingRay,normal,intersectPoint,refract_index);
	    			if(refractedRay_ptr==NULL) // Total Internal Reflection
	    			{
		    			refl_dirn = incident + (-normal)*(2*abs(incident.dot(normal)));
	    				toReflect = true;
	    				correct_normal = -normal;
	    				reflectcolor = sim_mat->getReflect();
	    			}
	    			else
	    			{
	    				trans_dirn = (*refractedRay_ptr).get_direction();
	    				correct_normal = (cosine<0)? normal : -normal; //cosine<0 if going out of object
	    				fresnel_refract = 1 - fresnel_reflect;
						isFresnel = true;
						toTransmit = true;
						refractcolor = sim_mat->getTransmit();	//color of the material
	    			}
    			}
    		}
    		else if(isTransmit) //only refractions
    		{
    			ray* refractedRay_ptr = generate_refract(viewingRay,normal,intersectPoint,refract_index);
    			if(refractedRay_ptr==NULL) //total internal reflection
				{
					refl_dirn = incident + (-normal)*(2*abs(incident.dot(normal)));
					toReflect = true;
					correct_normal = -normal;
					reflectcolor = sim_mat->getReflect();
				}
    			else
    			{
    				trans_dirn = (*refractedRay_ptr).get_direction();
    				toTransmit = true;
    				refractcolor = sim_mat->getTransmit();	//color of the material
    				correct_normal = (cosine<0)? normal : -normal; //cosine<0 if going out of object
    			}
    		}
    		else if(isReflect) //only reflections
    		{
    			refl_dirn = incident + normal*(2*abs(incident.dot(normal)));
    			toReflect = true;
    			correct_normal = normal;
    			reflectcolor = sim_mat->getReflect();
    		}
    	}

    	// intersectPoint = intersectPoint + correct_normal*bias;
    	
    	//checking the tags
		if(isFresnel)
		{
			if(toReflect)
			{
				ray reflectedRay(intersectPoint,refl_dirn);//generate a reflected ray
    			refl_col = this->radiance(reflectedRay,depth+1,max_depth,xsubi);
    			for(int k=0;k<3;k++)
			    	result_color[k] += refl_col[k]*reflectcolor[k]*fresnel_reflect;
			}
			else if(toTransmit)
			{	
				ray refractedRay(intersectPoint,trans_dirn);//generate a refracted ray
				refr_col = this->radiance(refractedRay,depth+1,max_depth,xsubi);	//recursive step
    			for(int k=0;k<3;k++)
					result_color[k] += refr_col[k]*refractcolor[k]*fresnel_refract;
			}
		}
		else if(toReflect)
		{
			ray reflectedRay(intersectPoint,refl_dirn);//generate a reflected ray
			refl_col = this->radiance(reflectedRay,depth+1,max_depth,xsubi);
			for(int k=0;k<3;k++)
			    result_color[k] += refl_col[k]*reflectcolor[k];
		}
		else if(toTransmit)
		{
			ray refractedRay(intersectPoint,trans_dirn);//generate a refracted ray	
			refr_col = this->radiance(refractedRay,depth+1,max_depth,xsubi);	//recursive step
			for(int k=0;k<3;k++)
				result_color[k] += refr_col[k]*refractcolor[k];	//component wise multiplication	
		}

		return result_color;
    }
    else
    	return img.getBgcolor();
}

void scene::render(char fname[], const int no_of_rays)
{
    int Wres = img.getWidth();
    int Hres = img.getHeight();
    double fov = cam.getFov();
    double H_phy = 2.0*tan((M_PI/180)*(0.5*fov)); // (fov/2) is the half angle height-wise
    double delta_H = H_phy/Hres;
    double delta_W = delta_H;
    // double W_phy = delta_W*Wres;

  //  std::cout<<Wres<<" "<<Hres<<" "<<fov<<" "<<H_phy<<" "<<delta_H<<" "<<delta_W<<" "<<W_phy<<std::endl;

    vec y = cam.getThird();y.normalise();
    vec z = cam.getUp();z.normalise();
    vec x = cam.getLookat();x.normalise();

    double inv_sample_size = 1.0/(n*n*no_of_rays);
  //  std::cout<<"Entering loop"<<std::endl;
#pragma omp parallel for schedule(dynamic, 1) // OpenMP
    for(int i=0;i<Wres;i++)
    {
        std::cerr << "\rRendering " << i*100./Wres << "%";
        for(int j=0;j<Hres;j++)
        {	//std::cout<<"Yo"<<std::endl;
            vec r;
			std::vector<double> temp_R_in_cam(3,0);
			std::vector<double> color(3,0);
			unsigned short xsubi[3] = {(unsigned short)(i*i),(unsigned short)(j*j),(unsigned short)(i*j)};//seed for erand48
			
			for(int m=0;m<n;m++)
			{
				for(int l=0;l<n;l++)
				{
					for(int g = 0; g < no_of_rays; g++)
					{
						double f = erand48(xsubi);
						double x = f*n_inv; //number between 0 and 1/n
						f = erand48(xsubi);
						double y = f*n_inv; //another number between 0 and 1/n
						
						temp_R_in_cam[0] = 1; //direction in camera coordinates
						temp_R_in_cam[1] = (0.5*Wres - (i + m*n_inv + x))*delta_W;
						temp_R_in_cam[2] = (0.5*Hres - (j + l*n_inv + y))*delta_H;
						vec R_in_cam(temp_R_in_cam);
						vec R_in_world = camera_to_world(R_in_cam);   
					 	vec origin = cam.getEye();
					 	vec viewing_dirn = R_in_world - origin;
					 	viewing_dirn.normalise();
					 	
					  	ray viewingRay(origin,viewing_dirn); 

					  	whitted* _intg = static_cast<whitted*>(intg);
						int max_depth = _intg->getDepth(); //assuming whitted
						
						std::vector<double> color1 = this->radiance(viewingRay,0,max_depth, xsubi); 

						for(int b=0;b<3;b++)
							color[b] += inv_sample_size*color1[b];
					}
				}
			}
            
            for(int k=0;k<3;k++)
            	img_arr[i][j][k] = color[k];
        	
        }
    }
    std::cout<<"Out of loops"<<std::endl;
    write_to_ppm(fname);
}


#include "scene.hpp"
#include <stddef.h> //NULL
#include <limits>
#include <math.h>
#include <fstream>
#include <iostream>

const double INF = std::numeric_limits<double>::infinity();

std::vector<double> normalise(std::vector<double> v)
{   
	std::vector<double> a(3,0);
    double sqmod = v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
    for(int i=0;i<3;i++)
    {
        a[i]=v[i]/sqrt(sqmod);
    }
    return a;
}

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
void scene::setLights(std::vector<std::shared_ptr<light> > lights)
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
            img_arr[i][j][0] = v[0];
            img_arr[i][j][1] = v[1];
            img_arr[i][j][2] = v[2];
            // if(i==0 && j==0) std::cout<<"("<<v[0]<<","<<v[1]<<","<<v[2]<<")"<<std::endl;
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
std::vector<std::shared_ptr<light> > scene::getLights()
{
	return lightslist;
}

void scene::rotation_matrix_formation()
{
	std::vector<double> x = cam.getLookat();
	std::vector<double> z = cam.getUp();
	std::vector<double> y = cam.getThird();
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
	std::vector<double> fourth = cam.getEye();
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
	std::vector<double> fourth = cam.getEye();  //supposed to be fourth column of translation matrix
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

std::vector<double> scene::world_to_camera(std::vector<double> world_c)
{
    std::vector<double> camera_c(world_c.size(),0);
    std::vector<double> temp = world_c;
    temp.push_back(1);
    std::vector<double> temp2(temp.size(),0);
    temp2=mat_mult(mat_mult(rotation_mat,translation_mat),temp);

    for(int i=0;i<3;i++)
    {
    	camera_c[i]=temp2[i];
    }
    return camera_c;
}


std::vector<double> scene::camera_to_world(std::vector<double> camera_c)
{
    std::vector<double> world_c(camera_c.size(),0);
      std::vector<double> temp = camera_c;
    temp.push_back(1);
    std::vector<double> temp2(temp.size(),0);
    temp2=mat_mult(mat_mult(inv_translation_mat,inv_rotation_mat),temp);

    for(int i=0;i<3;i++)
    {
    	world_c[i] = temp2[i];
    }

    return world_c;
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
    	return objectslist[index];
	else
		return NULL;
}

void scene::write_to_ppm()
{
	int w = this->getImage().getWidth();
	int h = this->getImage().getHeight();
    std::ofstream img ("image5.ppm");
    img << "P3" <<std::endl;
    img << w <<" "<< h <<std::endl;
    img << "255" <<std::endl;

    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
        {
            int r = (int)255 * this->img_arr[j][i][0];
            int g = (int)255 * this->img_arr[j][i][1];
            int b = (int)255 * this->img_arr[j][i][2];

            img << r <<" " << g <<" "<< b << "     ";
        }
        img<<std::endl;
    }

}

void scene::render()
{
    double Wres = this->getImage().getWidth();
    double Hres = this->getImage().getHeight();
    double fov = this->getCamera().getFov();
    double H_phy = 2.0*tan(M_PI*fov/360);
    double delta_H = H_phy/Hres;
    double delta_W = delta_H;
    double W_phy = delta_W*Wres;
  //  std::cout<<Wres<<" "<<Hres<<" "<<fov<<" "<<H_phy<<" "<<delta_H<<" "<<delta_W<<" "<<W_phy<<std::endl;

    std::vector<double> y = normalise(this->getCamera().getThird());
    std::vector<double> z = normalise(this->getCamera().getUp());
    std::vector<double> x = normalise(this->getCamera().getLookat());
  //  std::cout<<"Entering loop"<<std::endl;
    for(int i=0;i<Wres;i++)
    {
        for(int j=0;j<Hres;j++)
        {	//std::cout<<"Yo"<<std::endl;
            std::vector<double> r(3,0);
            std::vector<double> R_in_world(3,0);
            for(int k=0;k<3;k++)
            {//	std::cout<<y[k]<<std::endl;
				r[k]= (i-Wres/2)*delta_W*y[k] + (Hres/2-j)*delta_H*z[k];
		//		std::cout<<r[k]<<" "<<x[k]<<std::endl;
				R_in_world[k]= r[k] + x[k];
            }

            std::vector<double> origin = this->getCamera().getEye();

        //    std::cout<<"About to transform"<<std::endl;

          //  std::vector<double> R_in_world = camera_to_world(R_in_cam);
            if((i==512) && (j==384))
            {


            /*	for(int k=0;k<3;k++)
            	{
            		std::cout<<R_in_cam[k]<<" ";
            	}*/
            	for(int k=0;k<3;k++)
            	{
            		std::cout<<R_in_world[k]<<" ";
            	}
            }

          /* for(int i=0;i<3;i++)
            {
            	std::cout<<origin[i]<<" "<<R_in_world[i]<<" "<<R_in_cam[i]<<std::endl;
            }*/
         //   std::cout<<"After transformation"<<std::endl;
            ray Ray(origin,R_in_world); //ray generated, originating from camera 
           // std::cout<<"Ray generated"<<std::endl;
        	//call intersect function on all objects and find the nearest one which intersects
            std::shared_ptr<object> nearest_obj = this->intersect(Ray);
            if(nearest_obj!=NULL)
            {
            	//extract colour out of that material and fill into arr[i][j][]
            	//assuming simplemat
            //	std::cout<<"Performing static cast"<<std::endl;
            	simplemat* sim_mat = static_cast<simplemat*>(nearest_obj->getMaterial());
            //	std::cout<<"static cast successful"<<std::endl;
            	
                std::vector<double> diff_color = sim_mat->getDiffuse(); 
                for(int k=0;k<3;k++)
                    img_arr[i][j][k] = diff_color[k];
            }            
        }
    }
    std::cout<<"Out of loops"<<std::endl;
    write_to_ppm();
}


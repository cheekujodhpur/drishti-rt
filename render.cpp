#include <math.h>
void render()
{
    double Wres = scene_obj.getImage().getWidth();
    double Hres = scene_obj.getImage().getHeight();
    double fov = scene_obj.getCamera().getFov();
    double H_phy = 2.0*tan(M_PI/180*fov/2);
    double delta_H = H_phy/Hres;
    double delta_W = delta_H;
    double W_phy = delta_W*Wres;

    std::vector<double> y = normalise(scene_obj.getCamera().getThird());
    std::vector<double> z = normalise(scene_obj.getCamera().getUp());
    std::vector<double> x = normalise(scene_obj.getCamera().getLookat());

    for(double i=0;i<Wres;i++)
    {
        for(double j=0;j<Hres;j++)
        {
           std::vector<double> r(3,0);
           std::vector<double> R_in_cam(3,0);
           for(int k=0;k<3;k++)
           {
                r[k]= ((i-Wres/2)*y[k] + (Hres/2-j)*z[k])*delta_W;
                R_in_cam[k]= r[k] + x[k];
           }

             std::vector<double> origin = scene_obj.getCamera().getEye();
             std::vector<double> R_in_world = camera_to_world(R_in_cam);
            ray Ray(origin,R_in_world)   //need to check whether order of parameters is ok and whether direction is normalised or not:checked.

    //Now call intersect function on all objects: done.
    //Need to find the nearest object which intersects:done
    //extract colour out of that material and fill into arr[i][j][]
    //send arr[w][h][] to write_to_ppm: Already done in main.

          std::shared_ptr<object> nearest_obj = scene_obj.intersect(Ray);
          std::vector<double> diff_color = nearest_obj->getMaterial()->getDiffuse();

          	for(int k=0;k<3;k++)
          	{
          		img_arr[i][j][k] = diff_color[k];
          	}
            

        }
    }

}


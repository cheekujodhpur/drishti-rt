#include "ray.hpp"

ray::ray(std::vector<double> origin,std::vector<double> direction)
{
    _origin = origin;
  //  _direction = direction;
     double a = 0;
    // std::cout<<"Origin done"<<std::endl;
    for(int i=0;i<3;i++)
    {
        a = a + direction[i]*direction[i];
    }
  //  std::cout<<"a calculated"<<" "<<a<<std::endl;


    for(int i=0;i<3;i++)
    {//std::cout<<"Inside 2nd loop"<< sqrt(a)<<std::endl;
		//double m = direction[i]/sqrt(a);
		//std::cout<<m<<std::endl;
        _direction[i] = -1*direction[i]/sqrt(a);  //this line is creating error;
       // std::cout<<_direction[i]<<std::endl;
    }
 //   std::cout<<"returning"<<std::endl;
}

std::vector<double> ray::get_origin()
{
    return _origin;
}

std::vector<double> ray::get_direction()                                     //need to return normalised direction
{
    return _direction;
}

std::vector<double> ray::get_point(int x) //returns point at parameter x
{   std::vector<double> new1(3,0);
    std::vector<double> new2(3,0);
    for(int i=0;i<3;i++)
    {
        new1[i]=x*_direction[i];
        new2[i]=new1[i]+_origin[i];
    }

    return new2;

}



#include "ray.hpp"

ray::ray(vec origin,vec direction)
{
    _origin = origin;
    _direction = direction;
    for(int i=0;i<3;i++)
        if(direction[i]!=0)
            reciprocal_dirn[i] = 1.0/direction[i];
        else
            reciprocal_dirn[i] = 0;
 //   std::cout<<"returning"<<std::endl;
}

vec ray::get_origin()
{
    return _origin;
}

vec ray::get_direction()                                     //need to return normalised direction
{
    return _direction;
}

vec ray::get_point(double x) //returns point at parameter x
{   
    return _origin+_direction*x;
}

double ray::get_param(vec pos)
{
    for(int l=0;l<3;l++)
        if(_direction[l]!=0)
            return (pos[l]-_origin[l])*reciprocal_dirn[l];
}



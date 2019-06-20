#include "ray.h"

ray::ray(vector<double> origin,vector<double> direction)
{
    _origin = origin;
    _direction = direction;
}

vector<double> ray::get_origin()
{
    return _origin;
}

vector<double> ray::get_direction()
{
    return _direction;
}

vector<double> ray::get_point(int x)
{   vector<double> new1(3,0);
    vector<double> new2(3,0);
    for(int i=0;i<3;i++)
    {
        new1[i]=x*_direction[i];
        new2[i]=new1[i]+_origin[i];
    }

    return new2;

}



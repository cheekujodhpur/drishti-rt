#ifndef __RAY_HPP_INCLUDED__
#define __RAY_HPP_INCLUDED__

#include <iostream>
#include "vector.hpp"
#include <math.h>

class ray{

	vec _origin;
 	vec _direction;

public:   
    ray(vec origin,vec direction);
    vec get_direction();
    vec get_origin();
    vec get_point(double x);
    double get_param(vec pos);

};

#endif
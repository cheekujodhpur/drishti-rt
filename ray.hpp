#ifndef __RAY_HPP_INCLUDED__
#define __RAY_HPP_INCLUDED__

#include <iostream>
#include "vector.hpp"
#include <vector>
#include <math.h>

class ray{

	vec _origin;
 	vec _direction;
 	std::vector<double> reciprocal_dirn(3);

public:   
    ray(vec origin,vec direction);
    vec get_direction();
    vec get_origin();
    vec get_point(double x);
    double get_param(vec pos);

};

#endif
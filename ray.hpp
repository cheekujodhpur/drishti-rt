#ifndef __RAY_HPP_INCLUDED__
#define __RAY_HPP_INCLUDED__

#include <iostream>
#include <vector>
#include <math.h>

class ray{

	std::vector<double> _origin = std::vector<double>(3);
 	std::vector<double> _direction = std::vector<double>(3);

public:   
    ray(std::vector<double> origin,std::vector<double> direction);
    std::vector<double> get_direction();
    std::vector<double> get_origin();
    std::vector<double> get_point(double x);
    double get_param(std::vector<double> pos)

};

#endif
#ifndef __RAY_HPP_INCLUDED__
#define __RAY_HPP_INCLUDED__

#include <iostream>
#include <vector>
#include <math.h>
//using namespace std;

class ray{

	std::vector<double> _origin;
 	std::vector<double> _direction;

public:   
    ray(std::vector<double> origin,std::vector<double> direction);
    std::vector<double> get_direction();
    std::vector<double> get_origin();
    std::vector<double> get_point(int x);

};

#endif
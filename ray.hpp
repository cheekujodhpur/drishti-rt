#ifndef __RAY_HPP_INCLUDED__
#define __RAY_HPP_INCLUDED__

#include<iostream>
#include<vector>
using namespace std;

class ray{

	 vector<double> _origin;
 	   vector<double> _direction;

    public:

   
    ray(vector<double> origin,vector<double> direction);
    vector<double> get_direction();
    vector<double> get_origin();
    vector<double> get_point(int x);

};

#endif
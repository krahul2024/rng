#ifndef RNG_H 
#define RNG_H 


#include<iostream>
#include<random>


#define ull unsigned long long 


class rng {

public:
    rng(); 
    rng(double rtp, ull max_multiplier); 

    double get_random_value(); 
    ull get_multiplier();     

    ~rng(); 

private:
    std::uniform_real_distribution<double>u_dist; 
    std::mt19937_64 rg; 

    double rtp; 
    ull max_multiplier; 
};


#endif 

#include "rng.h"

rng::rng(): u_dist(0.0, 1.0){
    this->rtp            = 0.97; 
    this->max_multiplier = 1000000; 
    std::random_device rd; 
    rg.seed(rd());
}

rng::rng(double rtp, ull max_multiplier): u_dist(0.0, 1.0){
    this->rtp            = rtp; 
    this->max_multiplier = max_multiplier; 

    std::random_device rd; 
    rg.seed(rd()); 
}

double rng::get_random_value(){
    return u_dist(rg); 
}

ull rng::get_multiplier(){
    double u = u_dist(rg);
    unsigned multiplier; 

    if(u <= 1 - (rtp / 1.01)) return 100; 

    multiplier = 100 + std::floor((100 * rtp - 100 + 100 * u) / (1 - u)); 
    return multiplier > max_multiplier ? max_multiplier : multiplier; 
}

rng::~rng(){}; 

//
//  data_processing.hpp
//  alexandria
//
//  Created by Neel Shah on 3/7/20.
//  Copyright © 2020 Neel Shah. All rights reserved.
//

#ifndef data_processing_hpp
#define data_processing_hpp

#include "stats.hpp"

//Provide useful methods for manipulating data matrices for feeding into models
//Scaling data - changing the range
// x* = (x_i - mean)/stdev

//Normalize - changing the shape of distribution
// x* = (x_i - x_min)/(x_max - x_min)

//Normalize a data point based off a certain feature and a certain statistic
double scale(double data_point, std::size_t feature, stats &stat);

//Reverse above function
double de_scale(double data_point, std::size_t feature, stats &stat);


//Note: we should pass in a a copy to retain the origin statistic
//Normalize matrix based off a certain statistic
void scale(Matrix &m, stats &stat);

//Reverse above function, but change the normalized matrix under the same stats
void de_scale(Matrix &m, stats &stat);


//TODO: Add normalizization and denormalization

#endif /* data_processing_hpp */

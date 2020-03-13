//
//  stats.hpp
//  alexandria
//
//  Created by Neel Shah on 3/7/20.
//  Copyright © 2020 Neel Shah. All rights reserved.
//

#ifndef stats_hpp
#define stats_hpp

#include "Matrix.hpp"
#include <utility>
#include <algorithm>
#include <limits>

using MinMax = std::pair<double, double>;
using Lim = std::numeric_limits<double>;
class stats{
	//Keep running mean, median, standard deviation/variance, etc.
	//Useful for further data processing especially when more
	//models are implemented
	//and useful for distribution plotting (i.e. scatter and histograms)
	
	//Note: Not keeping running median due to need of extra data structures/space
	//complexity to store it (i.e. min and max priority queues for each column)
	
public:
	stats(Matrix &_data);
	
	double mean(std::size_t col);
	
	double variance(std::size_t col);
	
	double stdev(std::size_t col);
	
	double min(std::size_t col);
	
	double max(std::size_t col);
	
	double range(std::size_t col);
	
private:
	//Don't need to create a copy!
	Matrix &data;
	std::vector<double> sums;
	std::vector<double> sq_diff;
	//TODO: STORE MAXIMUM AND MINIMUM FOR NORMALIZING !!!
	std::vector<MinMax> minmax;
	
	
	//To check if we need to recalculate
	std::size_t size;
	
	
	void recalculate();
	void update_minmax(double datum, std::size_t col);
};


#endif /* stats_hpp */

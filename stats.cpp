//
//  stats.cpp
//  alexandria
//
//  Created by Neel Shah on 3/7/20.
//  Copyright © 2020 Neel Shah. All rights reserved.
//

#include "stats.hpp"



stats::stats(Matrix &_data): data(_data), size(_data.rows()) {
	if(size == 0) throw OperationError();
	sums.reserve(data.cols());
	sq_diff.reserve(data.cols());
	minmax.reserve(data.cols());
	for(std::size_t col = 0; col < data.cols(); ++col){
		sums.push_back(0);
		minmax.push_back({Lim::max(), Lim::min()});
		for(std::size_t row = 0; row < size; ++row){
			sums[col] += data[row][col];
			update_minmax(data[row][col], col);
		}
	}
	
	for(std::size_t col = 0; col < data.cols(); ++col){
		sq_diff.push_back(0);
		for(std::size_t row = 0; row < size; ++row){
			sq_diff[col] += (data[row][col] - sums[col]/size) * (data[row][col] - sums[col]/size) ;
		}
	}
}
	
double stats::mean(std::size_t col){
	if(size != data.rows()) recalculate();
	return sums[col]/size;
}

double stats::variance(std::size_t col){
	if(size != data.rows()) recalculate();
	if(size == 1) return 0;
	return sq_diff[col]/(size - 1);
}
	
double stats::stdev(std::size_t col){
	return sqrt(variance(col));
}

double stats::min(std::size_t col){
	if(size != data.rows()) recalculate();
	return minmax[col].first;
}

double stats::max(std::size_t col){
	if(size != data.rows()) recalculate();
	return minmax[col].second;
}

double stats::range(std::size_t col){
	return max(col) - min(col);
}

void stats::recalculate() {
	for(std::size_t row = size; row < data.rows(); ++row){
		for(std::size_t col = 0; col < data.cols(); ++col){
			sums[col] += data[row][col];
			update_minmax(data[row][col], col);
		}
	}
	for(std::size_t row = size; row < data.rows(); ++row){
		for(std::size_t col = 0; col < data.cols(); ++col){
			sq_diff[col] += (data[row][col] - sums[col]/size) * (data[row][col] - sums[col]/size);
		}
	}
	size = data.rows();
}

void stats::update_minmax(double datum, std::size_t col){
	minmax[col].first = std::min(datum, minmax[col].first);
	minmax[col].second = std::max(datum, minmax[col].second);
}

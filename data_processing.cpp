//
//  data_processing.cpp
//  alexandria
//
//  Created by Neel Shah on 3/7/20.
//  Copyright © 2020 Neel Shah. All rights reserved.
//

#include "data_processing.hpp"


double scale(double data_point, std::size_t feature, stats &stat){
	return (data_point - stat.mean(feature))/stat.stdev(feature);
}


double de_scale(double data_point, std::size_t feature, stats &stat){
	return data_point * stat.stdev(feature) + stat.mean(feature);
}


void scale(Matrix &m, stats &stat) {
	for(std::size_t row = 0; row < m.rows(); ++row){
		for(std::size_t col = 0; col < m.cols(); ++col){
			scale(m[row][col], col, stat);
		}
	}
}

void de_scale(Matrix &m, stats &stat) {
	for(std::size_t row = 0; row < m.rows(); ++row){
		for(std::size_t col = 0; col < m.cols(); ++col){
			de_scale(m[row][col], col, stat);
		}
	}
}

double normalize(double data_point, std::size_t feature, stats &stat){
	return (data_point - stat.min(feature))/stat.range(feature);
}


double de_normalize(double data_point, std::size_t feature, stats &stat){
	return data_point * stat.range(feature) + stat.min(feature);
}


void normalize(Matrix &m, stats &stat) {
	for(std::size_t row = 0; row < m.rows(); ++row){
		for(std::size_t col = 0; col < m.cols(); ++col){
			normalize(m[row][col], col, stat);
		}
	}
}

void de_normalize(Matrix &m, stats &stat) {
	for(std::size_t row = 0; row < m.rows(); ++row){
		for(std::size_t col = 0; col < m.cols(); ++col){
			de_normalize(m[row][col], col, stat);
		}
	}
}

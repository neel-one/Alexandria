//
//  linear_regression.cpp
//  alexandria
//
//  Created by Neel Shah on 3/6/20.
//  Copyright © 2020 Neel Shah. All rights reserved.
//

#include "linear_regression.hpp"

linear_regression::linear_regression() {}

linear_regression::linear_regression(Matrix & X, Matrix & y){
	fit(X, y);
}

void linear_regression::fit(Matrix & X, Matrix & y){
	Matrix tp = transpose(X);
	beta = tp * X;
	beta = inverse(beta) * tp * y;
}

Matrix linear_regression::predict(Matrix & X){
	Matrix y = X * transpose(beta);
	return transpose(y);
}

double linear_regression::predict_pt(Matrix & x){
	return dot(x, beta);
}

double linear_regression::predict_pt(std::vector<double> & x){
	Matrix _x = x;
	return dot(_x, beta);
}

void linear_regression::to_csv(std::string filename){
	throw NotImplementedError();
}

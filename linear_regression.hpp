//
//  linear_regression.hpp
//  alexandria
//
//  Created by Neel Shah on 3/6/20.
//  Copyright © 2020 Neel Shah. All rights reserved.
//

#ifndef linear_regression_hpp
#define linear_regression_hpp

#include <string>
#include <iostream>
#include <fstream>
#include "Matrix.hpp"
#include "model.h"

class linear_regression: public model {
	
	linear_regression();
	
	linear_regression(Matrix & X, Matrix & y);
	
	//READ BELOW FOR EXPLANATION:
	//See en.wikipedia.org/wiki/Linear_regression
	//Fits model based off matrices X and Y based off optimization principles
	//i.e. y ~= B dot X where B = [Bo,...,Bn], X = [1, ...Xn]
	//B = argmin(Loss function) where using the sum of squared losses
	// L = sum(y - yexp)^2 where y = B dot X
	//Utilizating gradient based optimization (think calculus: the local extrema
	//occur when gradient = 0)
	//Solving we can derive B = inverse(transpose(X)*X))*transpose(X)*Y
	
	//NOTE: capital letters i.e. X, Y represent 'matrices' while lower-case
	//represent vectors
	
	//Other methods of fitting best parameters can include a machine learning
	//approach, where we initialize B some random n x 1 matrix and we can utilize
	//a similar approach of trying to slightly change Bi based off our loss function
	//However, this approach is better suited for other methods (e.g. neural networks)
	//because we can utilize better methods to set some weight matrix
	void fit(Matrix & X, Matrix & y);
	
	//friend std::ostream & operator<<(std::ostream & os, const linear_regression & l);
	
	void to_csv(std::string filename);
	
	double predict_pt(Matrix & x);
	
	double predict_pt(std::vector<double> & x);
	
	Matrix predict(Matrix & X);
	
private:
	Matrix beta;
};

//std::ostream & operator<<(std::ostream & os, const linear_regression & l);

#endif /* linear_regression_hpp */

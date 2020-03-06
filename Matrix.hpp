//
//  Matrix.hpp
//  alexandria
//
//  Created by Neel Shah on 3/5/20.
//  Copyright © 2020 Neel Shah. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <exception>
#include <math.h>

class OperationError: public std::exception {};
class NotImplementedError: public std::exception {};

class Matrix {
public:
	//GOAL: Create good, readable code
	
	/* CTORS - default (empty 0 dim, 0 matrix)
			- 0 matrix in R^(rows x cols)
			- matrix from input stream (i.e. cin, istringstream, etc) formatted by:
				"rows cols a[0][0] ... a[rows-1][cols-1]" (left to right, top to bottom)
	 
	 REQUIRES: rows, cols > 0
	*/
				
	Matrix();
	
	
	Matrix(std::size_t rows, std::size_t cols);
	
	Matrix(std::istream &in);
	
	Matrix(std::string str);
	
	Matrix(std::string &str);
	
	
	/* Don't need destructor because dynamic memory is
	 taken care of by STL vector! (Generally safer to use STL than dynamic memory due to extensive
	 testing and optimization) */
	Matrix(const Matrix &other);
	
	Matrix& operator=(const Matrix &rhs);
	
	~Matrix();
	/*                    */
	
	std::vector<double> & operator[](std::size_t row){
		return matrix[row];
	}
	
	const std::vector<double> & operator[](std::size_t row) const {
		return matrix[row];
	}
	
	bool operator==(const Matrix &other);
	
	std::size_t rows() const {
		return matrix.size();
	}
	
	std::size_t cols() const {
		if(rows() == 0) return 0;
		return matrix[0].size();
	}
	
	void transpose();
	
	//REQUIRES: n x n matrix
	double det();

	
private:
	
	std::vector< std::vector< double > > matrix;
	
};
std::ostream & operator<<(std::ostream & os, const Matrix & m);

//REQUIRES: columns of a == rows of b
//Standard matrix multiplication
Matrix operator*(const Matrix &a, const Matrix &b);



Matrix transpose(Matrix & m);

double det(Matrix & m);

//REQUIRES: two n x 1  OR 1 x n dimensional matrices
//Standard scalar result dot product
double dot(Matrix &a, Matrix &b);
//double dot(std::vector<double> &a, std::vector<double> &b);

Matrix createSmallerMatrix(Matrix & m, std::size_t skip_row, std::size_t skip_col);

//REQUIRES: n x n matrix AND det(m) != 0
Matrix inverse(Matrix & m);

/* Other functions that are not necessary but may be nice to implement at
	a later time; core linear algebra topics, etc.
 */
Matrix rref(Matrix & m);

std::size_t rank(Matrix & m);

std::size_t nullity(Matrix & m);

std::vector<Matrix> basisIM(Matrix & m);

std::vector<Matrix> basisKER(Matrix & m);



#endif /* Matrix_hpp */

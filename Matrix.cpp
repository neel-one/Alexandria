//
//  Matrix.cpp
//  alexandria
//
//  Created by Neel Shah on 3/5/20.
//  Copyright © 2020 Neel Shah. All rights reserved.
//

#include "Matrix.hpp"


Matrix::Matrix() {}

Matrix::Matrix(std::size_t rows, std::size_t cols){
	matrix = std::vector< std::vector<double> > (rows,
											  std::vector<double>(cols, 0));
}

Matrix::Matrix(std::istream &in){
	std::size_t rows, cols;
	in >> rows;
	in >> cols;
	matrix = std::vector< std::vector<double> > (rows, std::vector<double>(cols, 0));
	
	double elt;
	std::size_t i = 0;
	std::size_t j = 0;
	while(in >> elt){
		matrix[i++][j++] = elt;
		if(i == rows) i = 0;
		if(j == cols) j = 0;
	}
}

Matrix::Matrix(const Matrix &other){
	matrix = other.matrix;
}

Matrix& Matrix::operator=(const Matrix &rhs){
	matrix = rhs.matrix;
	return *this;
}

Matrix::~Matrix() {}



void Matrix::transpose(){
	Matrix m(cols(), rows());
	for(std::size_t i = 0; i < rows(); ++i){
		for(std::size_t j = 0; j < cols(); ++j){
			m[j][i] = matrix[i][j];
		}
	}
	*this = m;
}

double Matrix::det(){
	throw NotImplementedError();
}

double dot(Matrix &a, Matrix &b) {
	double product = 0;
	if(a.cols() == 1 and b.cols() == 1 and a.rows() == b.rows()){
		for(std::size_t i = 0; i < a.rows(); ++i){
			product += a[i][0] * b[i][0];
		}
		return product;
	}
	else if(a.rows() == 1 and b.rows() == 1 and a.cols() == b.cols()){
		for(std::size_t i = 0; i < a.cols(); ++i){
			product += a[0][i] * b[0][i];
		}
		return product;
	}
	throw OperationError();
}


Matrix operator*(const Matrix &a, const Matrix &b){
	//Naive cubic implementation of matrix multiplication
	if(a.cols() != b.rows()) throw OperationError();
	Matrix m(a.rows(), b.cols());
	for(std::size_t i = 0; i < a.rows(); ++i){
		for(std::size_t j = 0; j < b.cols(); ++j){
			for(std::size_t k = 0; k < a.cols(); ++k){
				m[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return m;
}

Matrix transpose(Matrix & m){
	Matrix result(m.cols(), m.rows());
	for(std::size_t i = 0; i < m.rows(); ++i){
		for(std::size_t j = 0; j < m.cols(); ++j){
			result[j][i] = m[i][j];
		}
	}
	return result;
}

double det(Matrix & m){
	throw NotImplementedError();
}

Matrix inverse(Matrix & m){
	throw NotImplementedError();
}


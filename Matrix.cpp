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
	matrix = std::vector< std::vector<double> > (rows,
												 std::vector<double>(cols, 0));
	
	double elt;
	std::size_t i = 0;
	std::size_t j = 0;
	while(in >> elt){
		matrix[i][j++] = elt;
		if(j == cols){
			j = 0;
			++i;
		}
	}
}

Matrix::Matrix(std::string str){
	std::istringstream in(str);
	std::size_t rows, cols;
	in >> rows;
	in >> cols;
	matrix = std::vector< std::vector<double> > (rows,
												 std::vector<double>(cols, 0));
	
	double elt;
	std::size_t i = 0;
	std::size_t j = 0;
	while(in >> elt){
		matrix[i][j++] = elt;
		if(j == cols){
			j = 0;
			++i;
		}
	}
}

Matrix::Matrix(std::string &str){
	std::istringstream in(str);
	std::size_t rows, cols;
	in >> rows;
	in >> cols;
	matrix = std::vector< std::vector<double> > (rows,
												 std::vector<double>(cols, 0));
	
	double elt;
	std::size_t i = 0;
	std::size_t j = 0;
	while(in >> elt){
		matrix[i][j++] = elt;
		if(j == cols){
			j = 0;
			++i;
		}
	}
}

Matrix::Matrix(const Matrix &other){
	matrix = other.matrix;
}

Matrix::Matrix(const std::vector<double> &other){
	Matrix vec(1, other.size());
	for(std::size_t i = 0; i < other.size(); ++i){
		vec[0][i] = other[i];
	}
	std::swap(matrix, vec.matrix);
}

Matrix& Matrix::operator=(const Matrix &rhs){
	matrix = rhs.matrix;
	return *this;
}

Matrix& Matrix::operator=(const std::vector<double> &rhs){
	Matrix vec(1, rhs.size());
	for(std::size_t i = 0; i < rhs.size(); ++i){
		vec[0][i] = rhs[i];
	}
	std::swap(matrix, vec.matrix);
	return *this;
}

Matrix::~Matrix() {}

void Matrix::reserve(std::size_t extra_row){
	throw NotImplementedError();
}

void Matrix::reserve_col(std::size_t extra_col){
	throw NotImplementedError();
}

bool Matrix::operator==(const Matrix &other){
	return matrix == other.matrix;
}


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
	return ::det(*this);
}

void Matrix::append(std::vector<double> &row){
	if(matrix.size() > 0 and row.size() != matrix[0].size()) throw OperationError();
	matrix.push_back(row);
}

void Matrix::append_col(std::vector<double> &col){
	if(matrix.size() != col.size()) throw OperationError();
	for(std::size_t row = 0; row < matrix.size(); ++row){
		matrix[row].push_back(col[row]);
	}
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

std::ostream & operator<<(std::ostream & os, const Matrix & m){
	for(std::size_t i = 0; i < m.rows(); ++i){
		for(std::size_t j = 0; j < m.cols(); ++j){
			os << m[i][j] << " ";
		}
		os << "\n";
	}
	return os;
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

Matrix createSmallerMatrix(Matrix & m, std::size_t skip_row, std::size_t skip_col){
	Matrix sml(m.rows() - 1, m.cols() - 1);
	std::size_t sml_row, sml_col;
	sml_row = 0;
	sml_col = 0;
	for(std::size_t i = 0; i < m.rows(); ++i){
		if(i == skip_row) continue;
		for(std::size_t j = 0; j < m.cols(); ++j){
			if(j == skip_col) continue;
			sml[sml_row][sml_col++] = m[i][j];
		}
		++sml_row;
		sml_col = 0;
	}
	
	return sml;
}
double det_helper(Matrix & m){
	
	double det = 0;
	if(m.rows() == 1) return m[0][0];
	int pow = 1;
	for(std::size_t col = 0; col < m.cols(); ++col){
		Matrix sm = createSmallerMatrix(m, 0, col);
		det += pow * m[0][col] * det_helper(sm);
		pow *= -1;
	}
	
	return det;
}

double det(Matrix & m){
	if(m.rows() != m.cols()) throw OperationError();
	return det_helper(m);
}

Matrix cofactor(Matrix &m){
	Matrix C(m.rows(), m.cols());
	for(std::size_t i = 0; i < m.rows(); ++i){
		for(std::size_t j = 0; j < m.cols(); ++j){
			Matrix ij_minor = createSmallerMatrix(m, i, j);
			C[i][j] = pow(-1, i+j) * det(ij_minor);
		}
	}
	return C;
}

Matrix adjugate(Matrix &m){
	Matrix C = cofactor(m);
	return transpose(C);
}

Matrix inverse(Matrix & m){
	double dt = det(m);
	if(dt == 0) throw OperationError();
	double det_inverse = 1 / dt;
	Matrix adj = adjugate(m);
	for(std::size_t i = 0; i < m.rows(); ++i){
		for(std::size_t j = 0; j < m.cols(); ++j){
			adj[i][j] *= det_inverse;
		}
	}
	return adj;
}

Matrix inverse(Matrix & m, double dt){
	if(dt == 0) throw OperationError();
	double det_inverse = 1 / dt;
	Matrix adj = adjugate(m);
	for(std::size_t i = 0; i < m.rows(); ++i){
		for(std::size_t j = 0; j < m.cols(); ++j){
			adj[i][j] *= det_inverse;
		}
	}
	return adj;
}


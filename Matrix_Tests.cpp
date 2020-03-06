//
//  Matrix_Tests.cpp
//  alexandria
//
//  Created by Neel Shah on 3/6/20.
//  Copyright © 2020 Neel Shah. All rights reserved.
//

#include "Matrix.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <assert.h>

using namespace std;

void msg(string str){
	cout << str << endl;
}
void passed(){
	cout << "Passed" << endl;
}
int main(){
	
	msg("0 matrix test");
	string zero = "2 2 0 0 0 0 ";
	istringstream z(zero);
	Matrix a(z);
	Matrix b(2, 2);
	assert(a == b);
	passed();
	
	msg("square multiplication test");
	string m1 = "2 2 1 2 3 4";
	string m2 = "2 2 5 6 7 8";
	istringstream mat1(m1);
	istringstream mat2(m2);
	Matrix matr1(mat1), matr2(mat2);
	Matrix result = matr1 * matr2;
	Matrix exp(2,2);
	exp[0][0] = 19;
	exp[0][1] = 22;
	exp[1][0] = 43;
	exp[1][1] = 50;
	assert(result == exp);
	passed();
	
	
	msg("create smaller matrix tests");
	Matrix sq("3 3 1 4 7 2 5 8 3 6 9");
	Matrix sm = createSmallerMatrix(sq, 0, 1);
	assert(sm.rows() == sm.cols() and sm.rows() == 2);
	assert(sm == Matrix("2 2 2 8 3 9"));
	
	Matrix sq2("3 3 1 4 7 2 5 8 3 6 9");
	Matrix sm2 = createSmallerMatrix(sq, 0, 0);
	assert(sm2 == Matrix("2 2 5 8 6 9"));
	
	Matrix sm3 = createSmallerMatrix(sq, 0, 2);
	assert(sm3 == Matrix("2 2 2 5 3 6"));
	passed();
	
	
	msg("determinant tests");
	assert(det(b) == 0);
	assert(det(sm) == -6);
	assert(det(sm2) == -3);

	cout << det(sq) << endl;
	assert(det(sq) == 0);
	passed();
	
	msg("transpose tests");
	assert(transpose(sq) == Matrix("3 3 1 2 3 4 5 6 7 8 9"));
	Matrix nsq("3 2 3 1 2 4 0 1");
	assert(nsq.rows() == 3 and nsq.cols() == 2);
	assert(transpose(nsq) == Matrix("2 3 3 2 0 1 4 1"));
	passed();
	
	msg("inverse tests");
	//Should be -3 8/3
	//           2 -5/3
	cout << inverse(sm2);
	passed();
	
	
	cout << "Test passed!" << endl;
}

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>
#include <thread>

class Matrix {
public:
	int rows;
	int colums;
	int** values;

public:
	Matrix(int rows, int columns);
	~Matrix();

	void rand_init();
	void hand_init();

	Matrix& operator+(Matrix& B);
	Matrix& operator-(Matrix& B);
	Matrix& operator*(Matrix& B);
	friend std::ostream& operator<< (std::ostream& out, const Matrix& mat);



private:
	Matrix& add(Matrix& B);
	Matrix& subtract(Matrix& B);
	Matrix& multiply(Matrix& B);

};


#endif
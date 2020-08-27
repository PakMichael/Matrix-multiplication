#include "Matrix.h"
#include <random>
#include <iostream>


void Matrix::rand_init() {
	int rows = this->rows;
	int columns = this->colums;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(1.0, 10.0);

	//Randomly initialize it
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < columns; ++col) {
			this->values[row][col] = (int)dist(mt);
		}
	}
}

void Matrix::hand_init() {

	for (int row = 0; row < this->rows; ++row) {
		std::cout << "Row " << row << std::endl;
		for (int col = 0; col < this->colums; ++col) {
			std::cin >> this->values[row][col];
		}
	}


}


Matrix::Matrix(int rows, int columns) {
	this->rows = rows;
	this->colums = columns;
	this->values = new int* [rows];

	//Create matrix 
	for (int i = 0; i < rows; ++i)
		this->values[i] = new int[columns];



	//initialize to 0
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < columns; ++col) {
			this->values[row][col] = 0;
		}
	}


}

Matrix::~Matrix() {
	for (int i = 0; i < rows; ++i)
		delete this->values[i];
	delete this->values;
}


Matrix& Matrix::add(Matrix& B) {
	if (this->rows != B.rows || this->colums != B.colums)throw std::invalid_argument("Error: rows or columns don't match!");

	Matrix* res = new Matrix(this->rows, this->colums);

	for (int row = 0; row < this->rows; ++row) {
		for (int col = 0; col < this->colums; ++col) {
			res->values[row][col] = this->values[row][col] + B.values[row][col];
		}
	}

	return *res;

}


Matrix& Matrix::subtract(Matrix& B) {
	if (this->rows != B.rows || this->colums != B.colums)throw std::invalid_argument("Error: rows or columns don't match!");

	Matrix* res = new Matrix(this->rows, this->colums);

	for (int row = 0; row < this->rows; ++row) {
		for (int col = 0; col < this->colums; ++col) {
			res->values[row][col] = this->values[row][col] - B.values[row][col];
		}
	}

	return *res;

}

Matrix& Matrix::multiply(Matrix& B) {
	if (this->colums != B.rows)throw std::invalid_argument("Error: cannot multiply A*B, dimensions don't match");

	Matrix* res = new Matrix(this->rows, B.colums);
	std::vector<std::thread> all_threads;


	for (int row = 0; row < this->rows; ++row) {
		all_threads.emplace_back([row, this, &B, &res]() {
				for (int bCol = 0; bCol < B.colums; ++bCol) {
					for (int aCol = 0; aCol < this->colums; ++aCol) {
						int temp = this->values[row][aCol] * B.values[aCol][bCol];
						res->values[row][bCol] += temp;

					}
				}
			}
		);
	}

	for (std::thread& t : all_threads) {
		t.join();
	}



	return *res;

}

Matrix& Matrix::operator+(Matrix& B) {
	return this->add(B);
}

Matrix& Matrix::operator-(Matrix& B) {
	return this->subtract(B);
}

Matrix& Matrix::operator*(Matrix& B) {
	return this->multiply(B);
}

std::ostream& operator<< (std::ostream& out, const Matrix& mat)
{
	for (int row = 0; row < mat.rows; ++row) {
		for (int col = 0; col < mat.colums; ++col) {
			out << mat.values[row][col] << ", ";
		}
		out << "\n";
	}

	return out;
}



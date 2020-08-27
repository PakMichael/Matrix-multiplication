#include <iostream>
#include "Matrix.h"

using namespace std;


Matrix create_matrix() {
	int rows;
	int columns;

	std::cout << "Number of rows: " << std::endl;
	std::cin >> rows;

	std::cout << "Number of columns: " << std::endl;
	std::cin >> columns;

	return Matrix(rows, columns);;

}

int main() {
	Matrix A = create_matrix();
	A.hand_init();
	Matrix B = create_matrix();
	B.hand_init();


	cout << A << endl;
	cout << B << endl;

	Matrix& mul = A * B;
	cout << mul << endl;


	return 0;
}
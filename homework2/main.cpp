#include <iostream>

#include "matrix.hpp"


int main(void)
{
	std::cout << "the program started" << std::endl;

	float a[3][4] = {{2.0f, 3.0f, 1.0f, 2.0f}, {4.0f, 2.0f, 1.0f, 1.0f}, {4.0f, 2.0f, 1.0f, 1.0f}};
	float b[4][2] = {{1.0f, 3.0f}, {2.0f, 4.0f}, {1.0f, 3.0f}, {2.0f, 4.0f}};
	
	Matrix<3, 4> mat_a(a);
	Matrix<4, 2> mat_b(b);	

	Matrix<3, 2> mat_c = mat_a.mult_r<2>(mat_b);

	for(int i=1; i<=3; i++){
		for(int j=1; j<=2; j++){
			std::cout << mat_c.getValue(i, j) << ", ";
		}
		std::cout << std::endl;
	}


	return 0;
}

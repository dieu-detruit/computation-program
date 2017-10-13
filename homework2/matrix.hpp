#pragma once

#include <cstring>
#include <algorithm>
#include <stdexcept>

#include "algebra.hpp"


template<const unsigned int m, const unsigned int n, typename T = float>
class Matrix{
private:
	T m_matrix[m][n];	

public:
	Matrix()
	{
		std::fill( m_matrix[0], m_matrix[m-1], T());
	}

	Matrix(const Matrix& arg)
	{
		std::memcpy(m_matrix, arg.m_matrix, sizeof(T) * m * n);
	}


	Matrix(T val)
	{
		std::fill( m_matrix[0], m_matrix[m-1], val );
	}

	Matrix(T val[m][n])
	{
		std::memcpy(m_matrix, val, sizeof(T) * m * n);
	}

	

	~Matrix() = default;

	void setValue(unsigned int row, unsigned int column, T value)
	{
		if(row > m || column > n){
			throw std::out_of_range("Matrix setValue");
		} else {
			m_matrix[row][column] = value;	
		}
	}

	T getValue(unsigned int row, unsigned int column) const
	{
		if(row > m || column > n){
			throw std::out_of_range("Matrix getValue");
			return T();
		}
		return m_matrix[row-1][column-1];	
	}

	/* 左から行列を掛ける */	
	template<const unsigned int l>
	Matrix<l, n, T> mult_l(const Matrix<l, m, T>& left) const
	{
		Matrix<l, n, T> temp(0.0f);			
		for(int i=0; i<l; i++)for(int j=0; j<m; j++){
			std::cout << "(i, j) = (" << i << ", " << j << ")" << std::endl;	
			T sum = T();	
			try{
				for(int s=0; s<m; s++)sum += left.getValue(i+1,s+1) * m_matrix[s][j];
				temp.setValue(i, j, sum); 	
			}catch(const std::out_of_range& err){
				std::cout << err.what() << std::endl;
			}
		}
		return temp;
	}

	/* 右から行列を掛ける */	
	template<const unsigned int k>
	Matrix<m, k, T> mult_r(const Matrix<n, k, T>& right) const
	{
		Matrix<m, k, T> temp(0.0f);			
		for(int i=0; i<m; i++)for(int j=0; j<n; j++){
			std::cout << "(i, j) = (" << i << ", " << j << ")" << std::endl;	
			T sum = T();	
			try{
				for(int s=0; s<n; s++)sum += m_matrix[i][s] * right.getValue(s+1, j+1);
				temp.setValue(i, j, sum); 	
			}catch(const std::out_of_range& err){
				std::cout << err.what() << std::endl;
			}
		}
		return temp;
	}

	/* *演算子で右からの積を定義する */
	template<const unsigned int k>
	Matrix<m, k, T> operator*(const Matrix<n, k, T>& right) const
	{
		return mult_r<m, k, T>(right);
	}

	/* *=演算子で右から行列をかける演算を定義する */
	

	/* m==nについてのみ累乗を定義する */	
	Matrix<m, m> pow(int exp);

	/* m==nについてのみ累乗を定義する. ^演算子 */	
	Matrix<m, m> operator^(int exp);
};

template<const unsigned int m, const unsigned int n, const unsigned int k, typename T = float>
Matrix<m, k, T> operator*(const Matrix<m, n, T>& left, const Matrix<n, k, T>& right)
{
	return nullptr;	
}

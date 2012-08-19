/*! 
 *  BigInt class header
 *  -
 *  BigInt Homework - Advanced cpp programming
 *  Master in Computer Game Development, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 5 August 2012
 */

#pragma once

#include <vector>
#include <string>
#include "Types.h"

class BigInt {
public:
	BigInt();
	BigInt(const int iInteger);
	//BigInt(const BigInt &iBigInteger);
	BigInt(const std::string &iString);

	//BigInt& operator=(const BigInt &iBigInteger);
	//BigInt& operator+(const BigInt &iBigInteger);
	//BigInt& operator+=(const BigInt &iBigInteger);
	//BigInt& operator-(const BigInt &iBigInteger);
	//BigInt& operator-=(const BigInt &iBigInteger);
	//BigInt& operator*(const BigInt &iBigInteger);
	//BigInt& operator*=(const BigInt &iBigInteger);

private:
	std::vector<store_t> mRepresentation;
};

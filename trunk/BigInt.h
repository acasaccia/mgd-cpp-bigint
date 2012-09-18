/*! 
 *  BigInt class header
 *  It's an UnsignedBigInt with a sign.
 *  Manages to turn over UnsignedBigInt all the arithmetics making the necessary sign juggling
 *  to perform valid unsigned arithmetics.
 *  -
 *  BigInt Homework - Advanced cpp programming
 *  Master in Computer Game Development, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 5 August 2012
 */

#pragma once

#include "UnsignedBigInt.h"

class BigInt {
public:

#pragma region Constructors

	BigInt();
	BigInt(const int iInteger);
	BigInt(const std::string &iString);

#pragma endregion

#pragma region Compound assignment operators

	BigInt& operator+=(const BigInt &iThat);
	BigInt& operator-=(const BigInt &iBigInteger);
	BigInt& operator*=(const BigInt &iBigInteger);
	BigInt& operator/=(const BigInt &iBigInteger);

#pragma endregion

#pragma region Binary arithmetic operators

	const BigInt operator+(const BigInt &iThat) const;
	const BigInt operator-(const BigInt &iThat) const;
	const BigInt operator*(const BigInt &iThat) const;
	const BigInt operator/(const BigInt &iThat) const;
	
#pragma endregion

#pragma region Comparison operators

	bool operator==(const BigInt &iThat) const;
	bool operator!=(const BigInt &iThat) const;
	bool operator<(const BigInt &iThat) const;
	bool operator>(const BigInt &iThat) const;
	bool operator<=(const BigInt &iThat) const;
	bool operator>=(const BigInt &iThat) const;
	
#pragma endregion

#pragma region Increment/Decrement operators

	BigInt& operator++();
	BigInt& operator--();
	BigInt operator++(int);
	BigInt operator--(int);

#pragma endregion

#pragma region Members

	bool mNegative;
	UnsignedBigInt mMagnitude;

#pragma endregion

};

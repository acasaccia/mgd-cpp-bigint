/*! 
 *  BigInt - represents a signed arbitrary precision integer
 *  Turns over UnsignedBigInt all the arithmetics doing the
 *  sign juggling to perform valid unsigned operations.
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

	Sign mSign;
	UnsignedBigInt mMagnitude;

	#pragma region Constructors

	BigInt();
	BigInt(const unsigned long long iInteger);
	BigInt(const unsigned long iInteger);
	BigInt(const unsigned int iInteger);
	BigInt(const unsigned short iInteger);
	BigInt(const long long iSignedInteger);
	BigInt(const long iSignedInteger);
	BigInt(const int iSignedInteger);
	BigInt(const short iSignedInteger);
	BigInt(const std::string &iString);
	BigInt(const UnsignedBigInt &iUnsignedBigInt);

	#pragma endregion

	#pragma region Compound assignment operators

	BigInt& operator+=(const BigInt &iThat);
	BigInt& operator-=(const BigInt &iThat);
	BigInt& operator*=(const BigInt &iThat);
	BigInt& operator/=(const BigInt &iThat);
	BigInt& operator%=(const BigInt &iThat);

	#pragma endregion

	#pragma region Binary arithmetic operators

	const BigInt operator+(const BigInt &iThat) const;
	const BigInt operator-(const BigInt &iThat) const;
	const BigInt operator*(const BigInt &iThat) const;
	const BigInt operator/(const BigInt &iThat) const;
	const BigInt operator%(const BigInt &iThat) const;
	
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

	#pragma region Public Methods

	void print(std::ostream& os) const;
	std::string toString() const;
	static std::vector<bool> BigInt::digitToBinary(store_t iDigit);

	#pragma endregion

protected:

	#pragma region Protected Methods

	// Initialization logic is the same for all integer types
	template <class T>
	void constructFromInteger(const T iInteger) {
		mSign = POSITIVE;
		mMagnitude = UnsignedBigInt(iInteger);
	}

	template <class T>
	void constructFromSignedInteger(const T iSignedInteger) {
		mSign = iSignedInteger < 0 ? NEGATIVE : POSITIVE;
		mMagnitude = UnsignedBigInt(iSignedInteger < 0 ? -iSignedInteger : iSignedInteger);
	}

	#pragma endregion
};

BigInt pow(const BigInt& iBase, const UnsignedBigInt& iExponent);

std::ostream& operator<<( std::ostream& os, const BigInt& iBigInt );
std::istream& operator>>( std::istream& is, BigInt& iBigInt );
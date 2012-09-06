/*! 
 *  Unsigned Big Integer
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
#include <iostream>
#include <cstdint>

// The following typedefs should be adjusted to get the best performance from your hardware.
// If for example 64bit arithmetic is supported, it is better to use a 64bit type
// for calculations and store digits in a 32bit type to avoid overflow  when multiplying two of them.
// Using unsigned types gives the advantage of non having to worry masking the high bit at any time.
// \see http://stackoverflow.com/questions/12018410/how-do-i-find-the-largest-integer-supported-fully-by-hardware-arithmetics

typedef uint32_t store_t;	// type to store a digit
typedef uint64_t calc_t;	// type to perform calculation on two digits without hardware overlflow

class UnsignedBigInt {
public:

#pragma region Constructors

	UnsignedBigInt();
	UnsignedBigInt(const int iInteger);
	UnsignedBigInt(const std::string &iString);

#pragma endregion

#pragma region Compound assignment operators

	UnsignedBigInt& operator+=(const UnsignedBigInt &iThat);
	UnsignedBigInt& operator-=(const UnsignedBigInt &iUnsignedBigInteger);
	UnsignedBigInt& operator*=(const UnsignedBigInt &iUnsignedBigInteger);
	UnsignedBigInt& operator/=(const UnsignedBigInt &iUnsignedBigInteger);

#pragma endregion

#pragma region Binary arithmetic operators

	const UnsignedBigInt operator+(const UnsignedBigInt &iThat) const;
	const UnsignedBigInt operator-(const UnsignedBigInt &iThat) const;
	const UnsignedBigInt operator*(const UnsignedBigInt &iThat) const;
	const UnsignedBigInt operator/(const UnsignedBigInt &iThat) const;
	
#pragma endregion

#pragma region Comparison operators

	bool operator==(const UnsignedBigInt &iThat) const;
	bool operator!=(const UnsignedBigInt &iThat) const;
	bool operator<(const UnsignedBigInt &iThat) const;
	bool operator>(const UnsignedBigInt &iThat) const;
	bool operator<=(const UnsignedBigInt &iThat) const;
	bool operator>=(const UnsignedBigInt &iThat) const;
	
#pragma endregion

#pragma region Increment/Decrement operators

	UnsignedBigInt& operator++();
	UnsignedBigInt& operator--();
	UnsignedBigInt operator++(int);
	UnsignedBigInt operator--(int);

#pragma endregion

#pragma region Public Methods and Members

	void print(std::ostream& os) const;
	std::string toString() const;
	static const calc_t mBase;

#pragma endregion

private:

#pragma region Private Methods and Members

	std::vector<store_t> mDigits;
	static calc_t initializeBase();
	const std::string UnsignedBigInt::trim(const std::string& ioString, const std::string& iWhitespace = "0");

#pragma endregion

};

std::ostream& operator<<( std::ostream& os, const UnsignedBigInt& iUnsignedBigInt );
std::istream& operator>>( std::istream& is, UnsignedBigInt& iUnsignedBigInt );
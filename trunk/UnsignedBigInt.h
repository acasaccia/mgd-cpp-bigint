/*! 
 *  UnsignedBigInt - represents an unsigned arbitrary precision integer
 *  -
 *  BigInt Homework - Advanced cpp programming
 *  Master in Computer Game Development, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 5 August 2012
 */

#pragma once

// Uncomment the following to use the largest power of 10 that fits store_t
// as base for internal representation.
#define BIGINT_PSEUDO_DECIMAL_BASE true

#include <vector>
#include <string>
#include <iostream>
#include <cstdint>
#include "Types.h"
#include "Exceptions.h"
#include "BigIntUtilities.h"

struct DivisionResult;

class UnsignedBigInt {
public:

	const static calc_t mBase;
	const static store_t mPrintBase;
	std::vector<store_t> mDigits;
	const static int mChunkDigits;

	#pragma region Constructors

	UnsignedBigInt();
	UnsignedBigInt(const unsigned long long iInteger);
	UnsignedBigInt(const unsigned long iInteger);
	UnsignedBigInt(const unsigned int iInteger);
	UnsignedBigInt(const unsigned short iInteger);
	UnsignedBigInt(const long long iSignedInteger);
	UnsignedBigInt(const long iSignedInteger);
	UnsignedBigInt(const int iSignedInteger);
	UnsignedBigInt(const short iSignedInteger);
	UnsignedBigInt(const std::string &iString);

	#pragma endregion

	#pragma region Compound assignment arithmetic operators

	UnsignedBigInt& operator+=(const UnsignedBigInt &iThat);
	UnsignedBigInt& operator-=(const UnsignedBigInt &iThat);
	UnsignedBigInt& operator*=(const UnsignedBigInt &iThat);
	UnsignedBigInt& operator/=(const UnsignedBigInt &iThat);
	UnsignedBigInt& operator%=(const UnsignedBigInt &iThat);

	#pragma endregion

	#pragma region Binary arithmetic operators

	const UnsignedBigInt operator+(const UnsignedBigInt &iThat) const;
	const UnsignedBigInt operator-(const UnsignedBigInt &iThat) const;
	const UnsignedBigInt operator*(const UnsignedBigInt &iThat) const;
	const UnsignedBigInt operator/(const UnsignedBigInt &iThat) const;
	const UnsignedBigInt operator%(const UnsignedBigInt &iThat) const;
	
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

	#pragma region Shift operators

	UnsignedBigInt& operator<<=(const int iPlaces);
	UnsignedBigInt& operator>>=(const int iPlaces);

	const UnsignedBigInt operator<<(const int iPlaces) const;
	const UnsignedBigInt operator>>(const int iPlaces) const;

	#pragma endregion

	#pragma region Bitwise operators

	UnsignedBigInt& operator&=(const UnsignedBigInt &iThat);
	UnsignedBigInt& operator|=(const UnsignedBigInt &iThat);
	UnsignedBigInt& operator^=(const UnsignedBigInt &iThat);

	const UnsignedBigInt operator&(const UnsignedBigInt &iThat) const;
	const UnsignedBigInt operator|(const UnsignedBigInt &iThat) const;
	const UnsignedBigInt operator^(const UnsignedBigInt &iThat) const;
	const UnsignedBigInt operator~() const;

	#pragma endregion

	#pragma region Public Methods

	void print(std::ostream& os) const;
	std::string toString() const;
	static std::vector<bool> UnsignedBigInt::digitToBinary(store_t iDigit); // used by non-member function pow()

	#pragma endregion

protected:

	#pragma region Protected Methods

	static calc_t initializeBase();
	static store_t initializePrintBase();
	static int initializeChunkDigits();
	static calc_t largestPowerOfTenThatFits(calc_t);

	void UnsignedBigInt::trimLeadingZeros();
	const UnsignedBigInt UnsignedBigInt::multiplyByDigit(const store_t &iMultiplier) const;
	void divide(const UnsignedBigInt &iThat, DivisionResult &oDivisionResult);
	UnsignedBigInt& quotient(const UnsignedBigInt &iThat);
	UnsignedBigInt& remainder(const UnsignedBigInt &iThat);
	store_t UnsignedBigInt::guessMultiplier(const UnsignedBigInt& iDivisor, const UnsignedBigInt& iDividend);
	
	// Initialization logic is the same for all integer types
	template <class T>
	void constructFromInteger(const T iInteger) {
		mDigits = std::vector<store_t>();
		// If input fits a single digit we initialize it
		// static cast is safe: we dont accept integer types bigger than long long
		if ( static_cast<unsigned long long>(iInteger) < mBase - 1 ) {
			store_t digit = static_cast<store_t>(iInteger);
			mDigits.push_back(digit);
		} else {
			// else we convert to string and use string constructor
			// static_cast<unsigned long long>() is needed until VS11 will fully implement the new standard
			UnsignedBigInt tmp = std::to_string( static_cast<unsigned long long>(iInteger) );
			mDigits = tmp.mDigits;
		}
	}

	template <class T>
	void constructFromSignedInteger(const T iSignedInteger) {
		if (iSignedInteger < 0)
			throw BadIntegerInitializationException();
		else
			constructFromInteger(iSignedInteger);
	}

	#pragma endregion

};

struct DivisionResult {

	UnsignedBigInt *quotient, *remainder;

	DivisionResult() {
		quotient = NULL;
		remainder = NULL;
	}

	DivisionResult(UnsignedBigInt* iQuotient, UnsignedBigInt* iRemainder) {
		quotient = iQuotient;
		remainder = iRemainder;
	}

	~DivisionResult() {
		delete(quotient);
		delete(remainder);
	}

};

std::ostream& operator<<( std::ostream& os, const UnsignedBigInt& iUnsignedBigInt );
std::istream& operator>>( std::istream& is, UnsignedBigInt& iUnsignedBigInt );

UnsignedBigInt pow(const UnsignedBigInt& iBase, const UnsignedBigInt& iExponent);
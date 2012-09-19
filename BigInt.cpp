/*! 
 *  BigInt class implementation
 *  -
 *  BigInt Homework - Advanced cpp programming
 *  Master in Computer Game Development, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 5 August 2012
 */

#include "BigInt.h"
#include <sstream>
#include <regex>

#pragma region Constructors

BigInt::BigInt() {
	mSign = POSITIVE;
	mMagnitude = UnsignedBigInt();
}

BigInt::BigInt(const unsigned long long iInteger) { constructFromInteger(iInteger); }
BigInt::BigInt(const unsigned long iInteger) { constructFromInteger(iInteger); }
BigInt::BigInt(const unsigned int iInteger) { constructFromInteger(iInteger); }
BigInt::BigInt(const unsigned short iInteger) { constructFromInteger(iInteger); }
BigInt::BigInt(const long long iSignedInteger) { constructFromSignedInteger(iSignedInteger); }
BigInt::BigInt(const long iSignedInteger) { constructFromSignedInteger(iSignedInteger); }
BigInt::BigInt(const int iSignedInteger) { constructFromSignedInteger(iSignedInteger); }
BigInt::BigInt(const short iSignedInteger) { constructFromSignedInteger(iSignedInteger); }

BigInt::BigInt(const std::string &iString) {
	
	std::regex signed_integer_with_whitespaces("^[\\s]*[+-]?[\\s]*[0-9]+[\\s]*$");

	if ( !std::regex_match( iString, signed_integer_with_whitespaces ) )
		throw BadStringInitializationException();

	std::string cleanString = iString;
	BigIntUtilities::removeWhitespaces(cleanString);
	BigIntUtilities::trimLeadingZeros(cleanString);

	if (cleanString[0] == '-') {
		mSign = NEGATIVE;
		cleanString.erase(cleanString.begin());
	} else if (cleanString[0] == '+') {
		cleanString.erase(cleanString.begin());
		mSign = POSITIVE;
	} else {
		mSign = POSITIVE;
	}

	mMagnitude = UnsignedBigInt(cleanString);
}

BigInt::BigInt(const UnsignedBigInt &iUnsignedBigInt) {
	mSign = POSITIVE;
	mMagnitude = UnsignedBigInt(iUnsignedBigInt);
}

#pragma endregion

#pragma region Compound assignment operators

BigInt& BigInt::operator+=(const BigInt &iThat) {
	if (mSign == iThat.mSign) {
		mMagnitude += iThat.mMagnitude;
	} else if ( mMagnitude > iThat.mMagnitude ) {
		mMagnitude -= iThat.mMagnitude;
	} else {
		mMagnitude = iThat.mMagnitude - mMagnitude;
		mSign = iThat.mSign;
	}
	return *this;
}

BigInt& BigInt::operator-=(const BigInt &iThat) {
	BigInt tmp = iThat;
	tmp *= -1;
	*this += tmp;
	return *this;
}

BigInt& BigInt::operator*=(const BigInt &iThat) {
	mMagnitude *= iThat.mMagnitude;
	mSign == iThat.mSign ? mSign = POSITIVE : mSign = NEGATIVE;
	return *this;
}

BigInt& BigInt::operator/=(const BigInt &iThat) {
	mMagnitude /= iThat.mMagnitude;
	mSign == iThat.mSign ? mSign = POSITIVE : mSign = NEGATIVE;
	return *this;
}

BigInt& BigInt::operator%=(const BigInt &iThat) {
	mMagnitude %= iThat.mMagnitude;
	mSign == iThat.mSign ? mSign = POSITIVE : mSign = NEGATIVE;
	return *this;
}

#pragma endregion

#pragma region Binary arithmetic operators

const BigInt BigInt::operator+(const BigInt &iThat) const {
	return BigInt(*this) += iThat;
}

const BigInt BigInt::operator*(const BigInt &iThat) const {
	return BigInt(*this) *= iThat;
}

const BigInt BigInt::operator-(const BigInt &iThat) const {
	return BigInt(*this) -= iThat;
}

const BigInt BigInt::operator/(const BigInt &iThat) const {
	return BigInt(*this) /= iThat;
}

const BigInt BigInt::operator%(const BigInt &iThat) const {
	return BigInt(*this) %= iThat;
}
	
#pragma endregion

#pragma region Comparison operators

bool BigInt::operator==(const BigInt &iThat) const {
	return (mSign == iThat.mSign && mMagnitude == iThat.mMagnitude);
}

bool BigInt::operator!=(const BigInt &iThat) const {
	return !(*this == iThat);
}

bool BigInt::operator<(const BigInt &iThat) const {
	if (mSign != iThat.mSign) {
		return mSign == NEGATIVE;
	}
	if (mSign == POSITIVE)
		return mMagnitude < iThat.mMagnitude;
	else
		return mMagnitude > iThat.mMagnitude;
}

bool BigInt::operator>(const BigInt &iThat) const {
	return !(*this <= iThat);
}

bool BigInt::operator<=(const BigInt &iThat) const {
	return *this == iThat || *this < iThat;
}

bool BigInt::operator>=(const BigInt &iThat) const {
	return !(*this < iThat);
}

#pragma endregion

#pragma region Increment/Decrement operators

BigInt& BigInt::operator++() {
	return *this += 1;
}

BigInt& BigInt::operator--() {
	return *this -= 1;
}

BigInt BigInt::operator++(int) {
    BigInt result(*this);   // make a copy for result
    ++(*this);				// Now use the prefix version to do the work
    return result;			// return the copy (the old) value.
}

BigInt BigInt::operator--(int) {
    BigInt result(*this);   // make a copy for result
    --(*this);				// Now use the prefix version to do the work
    return result;			// return the copy (the old) value.
}

#pragma endregion

#pragma region Public Methods

void BigInt::print(std::ostream& os) const {
	os << ( mSign == POSITIVE ? "" : "-" ) << mMagnitude;
}

std::string BigInt::toString() const {
	std::string returnString;
	std::stringstream ss;
    ss << *this;
	return returnString = ss.str();
}

std::vector<bool> BigInt::digitToBinary(store_t iDigit) {
	std::vector<bool> ret;
	while(iDigit) {
		if (iDigit&1)
			ret.push_back(1);
		else
			ret.push_back(0);
		iDigit>>=1;  
	}
	reverse(ret.begin(),ret.end());
	return ret;
}

#pragma endregion

#pragma region Non members operators

std::ostream& operator<<( std::ostream& os, const BigInt& iBigInt ) {
	iBigInt.print(os);
	return os;
}

std::istream& operator>>( std::istream& is, BigInt& iBigInt ) {
	// read obj from stream
	std::string tmp;
	is >> tmp;
	try {
		iBigInt = BigInt(tmp);
	} catch (BadStringInitializationException e) {
		// no valid object of T found in stream
		is.setstate(std::ios::failbit);
	}
	return is;
}

BigInt pow(const BigInt& iBase, const UnsignedBigInt& iExponent) {
	BigInt result = 1;
	std::vector<bool> binaryDigit;
	for (digits_size_t i=0; i<iExponent.mDigits.size(); i++) {
		binaryDigit = BigInt::digitToBinary(iExponent.mDigits[i]);
		for (short j=0; j<binaryDigit.size(); j++) {
			result.mMagnitude *= result.mMagnitude;
			if (binaryDigit[j])
				result.mMagnitude *= iBase.mMagnitude;
		}
	}
	bool evenExponent = iExponent.mDigits.back() % 2 == 0;
	result.mSign = evenExponent ? POSITIVE : result.mSign;
	return result;
}

#pragma endregion
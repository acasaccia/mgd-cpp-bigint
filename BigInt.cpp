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
	// @todo: implement me
}

BigInt::BigInt(const UnsignedBigInt &iUnsignedBigInt) {
	mSign = false;
	mMagnitude = UnsignedBigInt(iUnsignedBigInt);
}

#pragma endregion

#pragma region Compound assignment operators

BigInt::BigInt& operator+=(const BigInt &iThat) {
	if (mSign == iThat.mSign) {
		mMagnitude += iThat.mMagnitude;
	} else if ( mMagnitude > iThat.mMagnitude ) {
		mMagnitude -= iThat.mMagnitude;
	} else {
		mMagnitude = iThat.mMagnitude - mMagnitude;
		mSign = iThat.mSign;
	}
}

BigInt::BigInt& operator-=(const BigInt &iThat) {
	iThat *= -1;
	*this += iThat;
}

BigInt::BigInt& operator*=(const BigInt &iThat) {
	mMagnitude *= iThat.mMagnitude;
	mSign == iThat.mSign ? mSign = POSITIVE : msign = NEGATIVE;
}

BigInt::BigInt& operator/=(const BigInt &iThat) {
	mMagnitude /= iThat.mMagnitude;
	mSign == iThat.mSign ? mSign = POSITIVE : msign = NEGATIVE;
}

BigInt::BigInt& operator%=(const BigInt &iThat) {
	mMagnitude %= iThat.mMagnitude;
	mSign == iThat.mSign ? mSign = POSITIVE : msign = NEGATIVE;
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

UnsignedBigInt& UnsignedBigInt::operator++() {
	return *this += 1;
}

UnsignedBigInt& UnsignedBigInt::operator--() {
	return *this -= 1;
}

UnsignedBigInt UnsignedBigInt::operator++(int) {
    UnsignedBigInt result(*this);   // make a copy for result
    ++(*this);						// Now use the prefix version to do the work
    return result;					// return the copy (the old) value.
}

UnsignedBigInt UnsignedBigInt::operator--(int) {
    UnsignedBigInt result(*this);   // make a copy for result
    --(*this);						// Now use the prefix version to do the work
    return result;					// return the copy (the old) value.
}

#pragma endregion
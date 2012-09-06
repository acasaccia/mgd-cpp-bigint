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
#include <exception>

#pragma region Constructors

BigInt::BigInt() {

}

BigInt::BigInt(const int iInteger) {
}

BigInt::BigInt(const std::string &iString) {
	// @todo: Implement me
}

#pragma endregion

#pragma region Compound assignment operators

BigInt& BigInt::operator+=(const BigInt &iThat) {
	// @todo: Implement me
	return *this;
}

BigInt& BigInt::operator-=(const BigInt &iThat) {
	// @todo: Implement me
	return *this;
}

BigInt& BigInt::operator*=(const BigInt &iThat) {
	// @todo: Implement me
	return *this;
}

BigInt& BigInt::operator/=(const BigInt &iThat) {
	// @todo: Implement me
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

#pragma endregion

#pragma region Comparison operators

bool BigInt::operator==(const BigInt &iThat) const {
	// @todo: Implement me
	return true;
}

bool BigInt::operator!=(const BigInt &iThat) const {
	// @todo: Implement me
	return true;
}

bool BigInt::operator<(const BigInt &iThat) const {
	// @todo: Implement me
	return true;
}

bool BigInt::operator>(const BigInt &iThat) const {
	// @todo: Implement me
	return true;
}

bool BigInt::operator<=(const BigInt &iThat) const {
	return *this == iThat || *this < iThat;
}

bool BigInt::operator>=(const BigInt &iThat) const {
	return *this == iThat || *this > iThat;
}

#pragma endregion

#pragma region Increment/Decrement operators

BigInt& BigInt::operator++() {
	// @todo: Implement me
	return *this;
}

BigInt& BigInt::operator--() {
	// @todo: Implement me
	return *this;
}

BigInt BigInt::operator++(int) {
    BigInt result(*this);   // make a copy for result
    ++(*this);              // Now use the prefix version to do the work
    return result;          // return the copy (the old) value.
}

BigInt BigInt::operator--(int) {
    BigInt result(*this);   // make a copy for result
    --(*this);              // Now use the prefix version to do the work
    return result;          // return the copy (the old) value.
}

#pragma endregion
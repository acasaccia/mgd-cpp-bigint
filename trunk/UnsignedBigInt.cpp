/*! 
 *  UnsignedBigInt class implementation
 *  -
 *  BigInt Homework - Advanced cpp programming
 *  Master in Computer Game Development, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 5 August 2012
 */

#include "UnsignedBigInt.h"
#include <exception>
#include <iomanip>
#include <sstream>

#pragma region Constructors

UnsignedBigInt::UnsignedBigInt() {
	initializeBase();
	mDigits = std::vector<store_t> ();
	mDigits.push_back(0);
}

UnsignedBigInt::UnsignedBigInt(const int iInteger) {

	// @todo: do as int do or throw exceptions? Think about it.
	if (iInteger < 0)
		throw std::exception("Trying to initialize an Unsigned Big Integer with a negative value.");

	// @todo: check if int fits into our UnsignedBigInt single digit
	// we could check if it fits in a single digit, otherwise convert to string and use string constructor: GG
	// additionally this could become a template method for all integers data types
	//if ( iInteger < std::numeric_limits<store_t>::max() ) {
		initializeBase();
		mDigits = std::vector<store_t> ();
		store_t digit = static_cast<store_t>(iInteger);
		mDigits.push_back(digit);
	//} else {

	//}
}

UnsignedBigInt::UnsignedBigInt(const std::string &iString) {
	initializeBase();

	// @todo: do as int do or throw exceptions? Think about it.
	if ( iString.find_first_not_of("0123456789") != std::string::npos )
		throw std::exception("Trying to initialize an Unsigned Big Integer with an invalid string.");

	mDigits = std::vector<store_t> ();
	
	store_t carry;
	calc_t sum, digit;

	char digit_char;

	for ( std::string::size_type i = 0; i != iString.size(); ++i ) {
		digit_char = iString[i];
		carry = static_cast<calc_t>(atoi(&digit_char));

		for ( std::vector<store_t>::size_type j = mDigits.size(); j --> 0 ;) {
			digit = static_cast<calc_t>(mDigits[j]);
			sum = digit * 10 + carry;
			mDigits[j] = static_cast<store_t>(sum % mBase);
			carry = static_cast<store_t>(sum / mBase);
		}

		if (carry) {
			mDigits.insert(mDigits.begin(), carry);
		}

	}

}

#pragma endregion

#pragma region Compound assignment operators

UnsignedBigInt& UnsignedBigInt::operator+=(const UnsignedBigInt &iThat) {

	// Basic schoolhouse method

	calc_t this_digit, that_digit, sum, carry;
	carry = 0;

	std::vector<store_t>::size_type this_size = mDigits.size();
	std::vector<store_t>::size_type that_size = iThat.mDigits.size();

	// we will surely end up with a number of digits >= to the bigger addend
	if (this_size < that_size) {
		mDigits.resize( that_size, 0 );
		this_size = that_size;
	}

	for ( std::vector<store_t>::size_type i = 0; i < this_size; i++ ) {
		// promote both digits from store_t to calc_t
		// if we got no more digits we set them to 0
		this_digit = static_cast<calc_t>(mDigits[this_size - 1 - i]);
		that_digit = (that_size - 1 - i) > that_size ? 0 : static_cast<calc_t>(iThat.mDigits[that_size - 1 - i]);
		// perform addition
		sum = this_digit + that_digit + carry;
		// check for overflow
		carry = static_cast<calc_t>(sum > mBase);
		// convert back to store_t and store result
		mDigits[this_size - 1 - i] = static_cast<store_t>(sum % mBase);
	}

	if (carry)
		mDigits.insert(mDigits.begin(), 1);

	return *this;
}

UnsignedBigInt& UnsignedBigInt::operator-=(const UnsignedBigInt &iThat) {

	// Basic schoolhouse method

	// @todo: Ok "do as int do" but does it make sense overflow for an arbitrary big integer subtraction?
	// Don't think so. I think I'll just throw an exception
	calc_t this_digit, that_digit, difference, borrow;
	borrow = 0;

	std::vector<store_t>::size_type this_size = mDigits.size();
	std::vector<store_t>::size_type that_size = iThat.mDigits.size();

	if (this_size < that_size) {
		mDigits.resize( that_size, 0 );
		this_size = that_size;
	}

	for ( std::vector<store_t>::size_type i = 0; i < this_size; i++ ) {
		// promote both digits from store_t to calc_t
		// if we got no more digits we set them to 0
		this_digit = static_cast<calc_t>(mDigits[this_size - 1 - i]);
		that_digit = (that_size - 1 - i) > that_size ? 0 : static_cast<calc_t>(iThat.mDigits[that_size - 1 - i]);
		// a Lannister always pays his debt
		this_digit -= borrow;
		// check if we need borrow
		borrow = static_cast<calc_t>(this_digit < that_digit);
		// perform subtraction
		difference = this_digit - that_digit + borrow * mBase;
		// convert back to store_t and store result
		mDigits[this_size - 1 - i] = static_cast<store_t>(difference);
	}

	if (borrow)
		mDigits.insert(mDigits.begin(), mBase - 1);

	return *this;
}

UnsignedBigInt& UnsignedBigInt::operator*=(const UnsignedBigInt &iThat) {

	// @todo: Implement me

	// Basic schoolhouse method (long multiplication)
	UnsignedBigInt* result = new UnsignedBigInt();

	std::vector<store_t>::size_type this_size = mDigits.size();
	std::vector<store_t>::size_type that_size = iThat.mDigits.size();

	for ( std::vector<store_t>::size_type i = 0; i < that_size; i++ ) {
		for ( std::vector<store_t>::size_type j = 0; i < this_size; i++ ) {
			
		}
	}

	return *this;
}

UnsignedBigInt& UnsignedBigInt::operator/=(const UnsignedBigInt &iThat) {
	// @todo: Implement me
	return *this;
}

#pragma endregion

#pragma region Binary arithmetic operators

const UnsignedBigInt UnsignedBigInt::operator+(const UnsignedBigInt &iThat) const {
	return UnsignedBigInt(*this) += iThat;
}

const UnsignedBigInt UnsignedBigInt::operator*(const UnsignedBigInt &iThat) const {
	return UnsignedBigInt(*this) *= iThat;
}

const UnsignedBigInt UnsignedBigInt::operator-(const UnsignedBigInt &iThat) const {
	return UnsignedBigInt(*this) -= iThat;
}

const UnsignedBigInt UnsignedBigInt::operator/(const UnsignedBigInt &iThat) const {
	return UnsignedBigInt(*this) /= iThat;
}

#pragma endregion

#pragma region Comparison operators

bool UnsignedBigInt::operator==(const UnsignedBigInt &iThat) const {
	if ( mDigits.size() != iThat.mDigits.size() )
		return false;
	for (std::vector<store_t>::size_type i = 0; i < mDigits.size(); i++ ) {
		if (mDigits[i] != iThat.mDigits[i])
			return false;
	}
	return true;
}

bool UnsignedBigInt::operator!=(const UnsignedBigInt &iThat) const {
	return !(*this == iThat);
}

bool UnsignedBigInt::operator<(const UnsignedBigInt &iThat) const {
	std::vector<store_t>::size_type this_size = mDigits.size();
	std::vector<store_t>::size_type that_size = iThat.mDigits.size();
	if ( this_size != that_size )
		return this_size < that_size;
	for (std::vector<store_t>::size_type i = 0; i < mDigits.size(); i++ ) {
		if (mDigits[i] != iThat.mDigits[i])
			return mDigits[i] < iThat.mDigits[i];
	}
	return false;
}

bool UnsignedBigInt::operator>(const UnsignedBigInt &iThat) const {
	return !(*this <= iThat);
}

bool UnsignedBigInt::operator<=(const UnsignedBigInt &iThat) const {
	return *this == iThat || *this < iThat;
}

bool UnsignedBigInt::operator>=(const UnsignedBigInt &iThat) const {
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

#pragma region Public Methods

void UnsignedBigInt::print(std::ostream& os) const {
	calc_t decimalDigitsInADigit = static_cast<calc_t>( log10(static_cast<long double>(mBase) ) );
	os << mDigits.front(); // no padding for most significant digit, ty
	for ( std::vector<store_t>::size_type i = 1; i < mDigits.size() ; i++) {
		os << std::setfill('0') << std::setw(decimalDigitsInADigit) << mDigits[i];
	}
}

std::string UnsignedBigInt::toString() const {
	std::string returnString;
	std::stringstream ss;
    ss << *this;
	return returnString = ss.str();
}

#pragma endregion

#pragma region Private Methods and Members

calc_t UnsignedBigInt::initializeBase() {
	// Get largest power of ten that fits store_t + 1.
	calc_t max_base = static_cast<calc_t>(std::numeric_limits<store_t>::max()) + 1;
	calc_t base = 1;
	while (base < max_base)
		base *= 10;
	return base / 10;
}

const calc_t UnsignedBigInt::mBase = UnsignedBigInt::initializeBase();

#pragma endregion

#pragma region Non members operators

std::ostream& operator<<( std::ostream& os, const UnsignedBigInt& iUnsignedBigInt ) {
	iUnsignedBigInt.print(os);
	return os;
}

std::istream& operator>>( std::istream& is, UnsignedBigInt& iUnsignedBigInt ) {
	// read obj from stream
	std::string tmp;
	is >> tmp;
	try {
		iUnsignedBigInt = UnsignedBigInt(tmp);
	} catch (std::exception e) {
		// no valid object of T found in stream
		is.setstate(std::ios::failbit);
	}
	return is;
}

#pragma endregion
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
#include <iomanip>
#include <sstream>

const calc_t UnsignedBigInt::mBase = UnsignedBigInt::initializeBase();

#pragma region Constructors

UnsignedBigInt::UnsignedBigInt() {
	mDigits = std::vector<store_t> ();
	mDigits.push_back(0);
}

UnsignedBigInt::UnsignedBigInt(const unsigned long long iInteger) { constructFromInteger(iInteger); }
UnsignedBigInt::UnsignedBigInt(const unsigned long iInteger) { constructFromInteger(iInteger); }
UnsignedBigInt::UnsignedBigInt(const unsigned int iInteger) { constructFromInteger(iInteger); }
UnsignedBigInt::UnsignedBigInt(const unsigned short iInteger) { constructFromInteger(iInteger); }
UnsignedBigInt::UnsignedBigInt(const long long iSignedInteger) { constructFromSignedInteger(iSignedInteger); }
UnsignedBigInt::UnsignedBigInt(const long iSignedInteger) { constructFromSignedInteger(iSignedInteger); }
UnsignedBigInt::UnsignedBigInt(const int iSignedInteger) { constructFromSignedInteger(iSignedInteger); }
UnsignedBigInt::UnsignedBigInt(const short iSignedInteger) { constructFromSignedInteger(iSignedInteger); }

UnsignedBigInt::UnsignedBigInt(const std::string &iString) {

	if ( iString.find_first_not_of("0123456789") != std::string::npos )
		throw BadStringInitializationException();

	std::string cleanString = iString;
	cleanString = trimLeadingZeros(cleanString);

	mDigits = std::vector<store_t> ();
	
	store_t carry;
	calc_t sum, digit;

	char digit_char;

	for ( std::string::size_type i = 0; i != cleanString.size(); ++i ) {
		digit_char = cleanString[i];
		carry = static_cast<calc_t>(atoi(&digit_char));

		for ( digits_size_t j = mDigits.size(); j --> 0 ;) {
			digit = static_cast<calc_t>(mDigits[j]);
			sum = digit * 10 + carry;
			mDigits[j] = static_cast<store_t>(sum % mBase);
			carry = static_cast<store_t>(sum / mBase);
		}

		if (carry)
			mDigits.insert(mDigits.begin(), carry);
	}

}

#pragma endregion

#pragma region Compound assignment operators

UnsignedBigInt& UnsignedBigInt::operator+=(const UnsignedBigInt &iThat) {

	// Basic schoolhouse method
	calc_t this_digit, that_digit, sum, carry;
	carry = 0;

	digits_size_t this_size = mDigits.size();
	digits_size_t that_size = iThat.mDigits.size();

	// we will surely end up with a number of digits >= to the bigger addend
	if ( this_size < that_size ) {
		while ( mDigits.size() < that_size ) {
			mDigits.insert(mDigits.begin(), 0);
		}
		this_size = that_size;
	}

	for ( digits_size_t i = 0; i < this_size; i++ ) {
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

	// Check that this > that or throw an exception
	if (*this < iThat)
		throw InvalidSubtractionException();

	// Basic schoolhouse method
	calc_t this_digit, that_digit, difference, borrow;
	borrow = 0;

	digits_size_t this_size = mDigits.size();
	digits_size_t that_size = iThat.mDigits.size();

	if ( this_size < that_size ) {
		mDigits.resize( that_size, 0 );
		this_size = that_size;
	}

	for ( digits_size_t i = 0; i < this_size; i++ ) {
		// promote both digits from store_t to calc_t
		// if we got no more digits we set them to 0
		this_digit = static_cast<calc_t>(mDigits[this_size - 1 - i]);
		that_digit = (that_size - 1 - i) > that_size ? 0 : static_cast<calc_t>(iThat.mDigits[that_size - 1 - i]);
		this_digit -= borrow;
		// check if we need borrow
		borrow = static_cast<calc_t>(this_digit < that_digit);
		// perform subtraction
		difference = this_digit - that_digit + borrow * mBase;
		// convert back to store_t and store result
		mDigits[this_size - 1 - i] = static_cast<store_t>(difference);
	}
	trimLeadingZeros();
	return *this;
}

UnsignedBigInt& UnsignedBigInt::operator*=(const UnsignedBigInt &iThat) {
	UnsignedBigInt partial, result = UnsignedBigInt();
	store_t multiplier;
	digits_size_t that_size = iThat.mDigits.size();
	for ( digits_size_t i = 0; i < that_size; i++ ) {
		multiplier = static_cast<store_t>(iThat.mDigits[that_size - 1 - i]);
		partial = this->multiplyByDigit(multiplier);
		for (digits_size_t c = 0; c < i; c++) {
			partial.mDigits.push_back(0); // shift left by i column
		}
		result += partial;
	}
	*this = result;
	trimLeadingZeros();
	return *this;
}

const UnsignedBigInt UnsignedBigInt::multiplyByDigit(const store_t &iMultiplier) const {
	UnsignedBigInt tmpUnsignedBigInt = UnsignedBigInt(*this);
	digits_size_t size = tmpUnsignedBigInt.mDigits.size();
	calc_t multiplier, current_digit, tmp, carry;
	multiplier = multiplier = static_cast<calc_t>(iMultiplier);
	carry = 0;
	for ( digits_size_t i = 0; i < size; i++ ) {
		// promote both to calc_t
		current_digit = static_cast<calc_t>(tmpUnsignedBigInt.mDigits[size - 1 - i]);
		tmp = current_digit * multiplier + carry;
		carry = tmp / mBase;
		tmpUnsignedBigInt.mDigits[size - 1 - i] = static_cast<store_t>(tmp % mBase);
	}
	if (carry)
		tmpUnsignedBigInt.mDigits.insert(tmpUnsignedBigInt.mDigits.begin(), carry);
	return tmpUnsignedBigInt;
}

UnsignedBigInt& UnsignedBigInt::operator/=(const UnsignedBigInt &iThat) {
	return divide(iThat, QUOTIENT);
}

UnsignedBigInt& UnsignedBigInt::operator%=(const UnsignedBigInt &iThat) {
	return divide(iThat, REMAINDER);
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

const UnsignedBigInt UnsignedBigInt::operator%(const UnsignedBigInt &iThat) const {
	return UnsignedBigInt(*this) %= iThat;
}


#pragma endregion

#pragma region Comparison operators

bool UnsignedBigInt::operator==(const UnsignedBigInt &iThat) const {
	if ( mDigits.size() != iThat.mDigits.size() )
		return false;
	for (digits_size_t i = 0; i < mDigits.size(); i++ ) {
		if (mDigits[i] != iThat.mDigits[i])
			return false;
	}
	return true;
}

bool UnsignedBigInt::operator!=(const UnsignedBigInt &iThat) const {
	return !(*this == iThat);
}

bool UnsignedBigInt::operator<(const UnsignedBigInt &iThat) const {
	digits_size_t this_size = mDigits.size();
	digits_size_t that_size = iThat.mDigits.size();
	if ( this_size != that_size )
		return this_size < that_size;
	for (digits_size_t i = 0; i < mDigits.size(); i++ ) {
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

#pragma region Public Methods and Members

void UnsignedBigInt::print(std::ostream& os) const {
	calc_t decimalDigitsInADigit = static_cast<calc_t>( log10(static_cast<long double>(mBase) ) );
	os << mDigits.front(); // no padding for most significant digit, ty
	for ( digits_size_t i = 1; i < mDigits.size() ; i++) {
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

#pragma region Protected Methods and Members

calc_t UnsignedBigInt::initializeBase() {
	// Use as base the bigger value that can be stored in store_t
	// return static_cast<calc_t>(std::numeric_limits<store_t>::max()) + 1;
	// Get largest power of ten that fits store_t + 1.
	calc_t max_base = static_cast<calc_t>(std::numeric_limits<store_t>::max()) + 1;
	calc_t base = 1;
	while (base < max_base)
		base *= 10;
	return base / 10;

}

const std::string UnsignedBigInt::trimLeadingZeros(const std::string& ioString)
{
    const size_t beginStr = ioString.find_first_not_of("0");
    if (beginStr == std::string::npos)
        return "";
    return ioString.substr(beginStr);
}

void UnsignedBigInt::trimLeadingZeros() {
	std::vector<store_t>::iterator it = mDigits.begin();
	while ( *it == 0 && mDigits.size() > 1 ) {
		it = mDigits.erase(it);
		it = mDigits.begin();
	}
}

UnsignedBigInt& UnsignedBigInt::divide(const UnsignedBigInt &iThat, divisionResult iMode) {
	
	UnsignedBigInt quotient, divisor, tmp;
	calc_t tmp_q, tmp_r;

	digits_size_t n = iThat.mDigits.size();

	if (n == 1)
		return divideByDigit(iThat.mDigits[0], iMode);

	digits_size_t m = mDigits.size() - n;

	// add a digit to dividend
	mDigits.insert(mDigits.begin(), 0);

	store_t d =  static_cast<store_t>(mBase - 1) /  static_cast<store_t>(iThat.mDigits[0]);

	divisor = iThat * d;	// normalize divisor
	*this *= d;				// multiply dividend accordingly

	// number of loops is dividend digits - divisor digits
	digits_size_t j = m;
	
	while ( j > 0 ) {

		tmp_q = ( static_cast<calc_t>(mDigits[m-j]) * static_cast<calc_t>(mBase) + static_cast<calc_t>(mDigits[m-j+1]) ) / static_cast<calc_t>(divisor.mDigits[0]);
		tmp_r = ( static_cast<calc_t>(mDigits[m-j]) * static_cast<calc_t>(mBase) + static_cast<calc_t>(mDigits[m-j+1]) ) % static_cast<calc_t>(divisor.mDigits[0]);

		bool repeat_test = true;

		while (repeat_test) {
			if (tmp_q == mBase || tmp_q * divisor.mDigits[1] > mBase * tmp_r + mDigits[m-j+2]) {
				tmp_q--;
				tmp_r += divisor.mDigits[0];
				if ( tmp_r < mBase )
					repeat_test = true;
				else
					repeat_test = false;
			} else {
				repeat_test = false;
			}
		}

		tmp = 0;

		// pick n digits from j to j+n
		for (digits_size_t i = m-j; i<=m-j+n; i++) {
			if (tmp == 0)
				tmp.mDigits[0] = mDigits[i];
			else
				tmp.mDigits.push_back(mDigits[i]);
				
		}

		// compute divisor * digit quotient
		tmp -= divisor * tmp_q;

		// replace selected digit with computed value
		while (tmp.mDigits.size()<=n)
			tmp.mDigits.insert(tmp.mDigits.begin(),0);

		for (digits_size_t i=0; i<=n; i++) {
			mDigits[m-j+i] = tmp.mDigits[i];
		}

		if (quotient == 0)
			quotient.mDigits[0] = tmp_q;
		else
			quotient.mDigits.push_back(tmp_q);

		j--;

	}
	
	iMode == QUOTIENT ? *this = quotient : *this /= d;

	return *this;
}

UnsignedBigInt& UnsignedBigInt::divideByDigit(const store_t &iDivisor, divisionResult iMode) {
	return *this;
}

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

#pragma region Other functions

UnsignedBigInt pow(const UnsignedBigInt& iBase, const int iExponent);

#pragma endregion
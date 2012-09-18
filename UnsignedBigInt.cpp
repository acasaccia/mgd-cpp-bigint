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

	mDigits = std::vector<store_t>();

	if ( std::strcmp(cleanString.c_str(), "0") == 0 ) {
		mDigits.push_back(0);
		return;
	}

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

#pragma region Public Methods

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

std::vector<bool> UnsignedBigInt::digitToBinary(store_t iDigit) {
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

#pragma region Protected Methods

calc_t UnsignedBigInt::initializeBase() {
	// Use as base the bigger value that can be stored in store_t
	// return static_cast<calc_t>(std::numeric_limits<store_t>::max()) + 1;

	// This is much easier for human readability: see readme file for details.
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
		return "0";
    return ioString.substr(beginStr);
}

void UnsignedBigInt::trimLeadingZeros() {
	std::vector<store_t>::iterator it = mDigits.begin();
	while ( *it == 0 && mDigits.size() > 1 ) {
		it = mDigits.erase(it);
		it = mDigits.begin();
	}
}

UnsignedBigInt& UnsignedBigInt::divide(const UnsignedBigInt &iDivisor, divisionResult iMode) {
	
	if (iDivisor == 0)
		throw DivideByZeroException();

	UnsignedBigInt subdividend, subremainder, quotient, product;
	digits_size_t n, dividend_size;
	store_t multiplier;
	bool first_round = true;

	n = 1;
		
	dividend_size = mDigits.size();
	subdividend = 0;

	// pick first n digits of dividend until candidate > divisor
	do {
		subdividend.mDigits = std::vector<store_t>(mDigits.begin(), mDigits.begin()+n);
		n++;
	} while (subdividend < iDivisor && n <= dividend_size);

	// remove the picked digits from dividend
	mDigits = std::vector<store_t>(mDigits.begin() + (n-1), mDigits.end());
		
	// find out how many times divisor fits into subdividend
	multiplier = getMultiplier(iDivisor, subdividend);
	subremainder = subdividend - iDivisor * static_cast<store_t>(multiplier);
	quotient.mDigits.push_back(multiplier);

	while ( mDigits.size() > 0 ) {
		subdividend = subremainder * mBase + mDigits.front();
		mDigits.erase(mDigits.begin());
		multiplier = getMultiplier(iDivisor, subdividend);
		subremainder = subdividend - iDivisor * static_cast<store_t>(multiplier);
		quotient.mDigits.push_back(multiplier);
	}

	iMode == QUOTIENT ? mDigits = quotient.mDigits : mDigits = subremainder.mDigits;
	
	trimLeadingZeros();

	return *this;
}

store_t UnsignedBigInt::getMultiplier(const UnsignedBigInt& iDivisor, const UnsignedBigInt& iDividend) {

	store_t min = 0;
	store_t max = std::numeric_limits<store_t>::max();
	store_t j;

	while (max - min > 1 ) {
		j = static_cast<store_t>( ( static_cast<calc_t>(max) + static_cast<calc_t>(min) ) / 2 );
		if (iDivisor * j == iDividend) {
			return j;
		}
		if (iDivisor * j < iDividend) {
			min = j;
		}
		if (iDivisor * j > iDividend) {
			max = j;
		}
	}

	j = max;
	if (iDivisor * j > iDividend)
		j--;
	return j;
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
	} catch (BadStringInitializationException e) {
		// no valid object of T found in stream
		is.setstate(std::ios::failbit);
	}
	return is;
}

UnsignedBigInt pow(const UnsignedBigInt& iBase, const UnsignedBigInt& iExponent) {
	UnsignedBigInt result = 1;
	std::vector<bool> binaryDigit;
	for (digits_size_t i=0; i<iExponent.mDigits.size(); i++) {
		binaryDigit = UnsignedBigInt::digitToBinary(iExponent.mDigits[i]);
		for (short j=0; j<binaryDigit.size(); j++) {
			result *= result;
			if (binaryDigit[j])
				result *= iBase;
		}
	}
	return result;
}

#pragma endregion
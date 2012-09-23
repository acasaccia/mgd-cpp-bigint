/*! 
 *  BigInt - represents an unsigned arbitrary precision integer
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
#include <regex>

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

	// optional whitespaces - mandatory [0-9] digits - optional whitespaces
	std::regex integer_with_whitespaces("^[\\s]*[0-9]+[\\s]*$");

	if ( !std::regex_match( iString, integer_with_whitespaces ) )
		throw BadStringInitializationException();

	std::string cleanString = iString;
	BigIntUtilities::removeWhitespaces(cleanString);
	BigIntUtilities::trimLeadingZeros(cleanString);

	mDigits = std::vector<store_t>();

	if ( std::strcmp(cleanString.c_str(), "0") == 0 ) {
		mDigits.push_back(0);
		return;
	}

	store_t carry;
	calc_t sum, digit;

	char digit_char;

	for ( std::string::size_type i = 0; i != cleanString.size(); ++i ) {
		digit_char = cleanString.at(i);
		carry = static_cast<calc_t>(atoi(&digit_char));

		for ( digits_size_t j = mDigits.size(); j --> 0 ;) {
			digit = static_cast<calc_t>(mDigits.at(j));
			sum = digit * 10 + carry;
			mDigits.at(j) = static_cast<store_t>(sum % mBase);
			carry = static_cast<store_t>(sum / mBase);
		}

		if (carry)
			mDigits.insert(mDigits.begin(), carry);
	}

}

#pragma endregion

#pragma region Compound assignment arithmetic operators

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
		this_digit = static_cast<calc_t>(mDigits.at(this_size - 1 - i));
		that_digit = (that_size - 1 - i) > that_size ? 0 : static_cast<calc_t>(iThat.mDigits.at(that_size - 1 - i));
		// perform addition
		sum = this_digit + that_digit + carry;
		// check for overflow
		carry = static_cast<calc_t>(sum > mBase);
		// convert back to store_t and store result
		mDigits.at(this_size - 1 - i) = static_cast<store_t>(sum % mBase);
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

	for ( digits_size_t i = 0; i < this_size; i++ ) {
		// promote both digits from store_t to calc_t
		// if we got no more digits we set them to 0
		this_digit = static_cast<calc_t>(mDigits.at(this_size - 1 - i));
		that_digit = (that_size - 1 - i) > that_size ? 0 : static_cast<calc_t>(iThat.mDigits.at(that_size - 1 - i));
		this_digit -= borrow;
		// check if we need borrow
		borrow = static_cast<calc_t>(this_digit < that_digit);
		// perform subtraction
		difference = this_digit - that_digit + borrow * mBase;
		// convert back to store_t and store result
		mDigits.at(this_size - 1 - i) = static_cast<store_t>(difference);
	}
	trimLeadingZeros();
	return *this;
}

UnsignedBigInt& UnsignedBigInt::operator*=(const UnsignedBigInt &iThat) {
	UnsignedBigInt partial, result = UnsignedBigInt();
	store_t multiplier;
	digits_size_t that_size = iThat.mDigits.size();
	for ( digits_size_t i = 0; i < that_size; i++ ) {
		multiplier = static_cast<store_t>(iThat.mDigits.at(that_size - 1 - i));
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

UnsignedBigInt& UnsignedBigInt::operator/=(const UnsignedBigInt &iThat) {
	return quotient(iThat);
}

UnsignedBigInt& UnsignedBigInt::operator%=(const UnsignedBigInt &iThat) {
	return remainder(iThat);
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
	digits_size_t this_size = mDigits.size();
	if ( this_size != iThat.mDigits.size() )
		return false;
	for (digits_size_t i = 0; i < this_size; i++ ) {
		if (mDigits.at(i) != iThat.mDigits.at(i))
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
	for (digits_size_t i = 0; i < this_size; i++ ) {
		if (mDigits.at(i) != iThat.mDigits.at(i))
			return mDigits.at(i) < iThat.mDigits.at(i);
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

#pragma region Increment / Decrement operators

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

#pragma region Shift operators

UnsignedBigInt& UnsignedBigInt::operator<<=(const int iPlaces) {
	if ( iPlaces < 0 )
		throw NegativeShiftException();
	return *this *= pow( UnsignedBigInt(2), UnsignedBigInt(iPlaces) );
}

UnsignedBigInt& UnsignedBigInt::operator>>=(const int iPlaces) {
	if ( iPlaces < 0 )
		throw NegativeShiftException();
	return *this /= pow( UnsignedBigInt(2), UnsignedBigInt(iPlaces) );
}

const UnsignedBigInt UnsignedBigInt::operator<<(const int iPlaces) const {
	UnsignedBigInt result(*this);
	return result <<= iPlaces;
}

const UnsignedBigInt UnsignedBigInt::operator>>(const int iPlaces) const {
	UnsignedBigInt result(*this);
	return result >>= iPlaces;
}

#pragma endregion

#pragma region Bitwise operators

UnsignedBigInt& UnsignedBigInt::operator&=(const UnsignedBigInt &iThat) {
	digits_size_t this_size = mDigits.size();
	digits_size_t that_size = iThat.mDigits.size();
	if (this_size > that_size)
		mDigits.erase(mDigits.begin(), mDigits.begin() + this_size - that_size);
	for(digits_size_t c=0; c<mDigits.size(); c++)
		mDigits.at(c) &= iThat.mDigits.at(c);
	trimLeadingZeros();
	return *this;
}

UnsignedBigInt& UnsignedBigInt::operator|=(const UnsignedBigInt &iThat) {
	digits_size_t this_size = mDigits.size();
	digits_size_t that_size = iThat.mDigits.size();
	if (this_size < that_size)
		mDigits.insert(mDigits.begin(), that_size - this_size);
	for(digits_size_t c=0; c<mDigits.size(); c++)
		mDigits.at(c) |= iThat.mDigits.at(c);
	trimLeadingZeros();
	return *this;
}

UnsignedBigInt& UnsignedBigInt::operator^=(const UnsignedBigInt &iThat) {
	digits_size_t this_size = mDigits.size();
	digits_size_t that_size = iThat.mDigits.size();
	if (this_size < that_size)
		mDigits.insert(mDigits.begin(), that_size - this_size);
	for(digits_size_t c=0; c<mDigits.size(); c++)
		mDigits.at(c) ^= iThat.mDigits.at(c);
	trimLeadingZeros();
	return *this;
}

const UnsignedBigInt UnsignedBigInt::operator&(const UnsignedBigInt &iThat) const {
	return UnsignedBigInt(*this) &= iThat;
}

const UnsignedBigInt UnsignedBigInt::operator|(const UnsignedBigInt &iThat) const {
	return UnsignedBigInt(*this) |= iThat;
}

const UnsignedBigInt UnsignedBigInt::operator^(const UnsignedBigInt &iThat) const {
	return UnsignedBigInt(*this) ^= iThat;
}

const UnsignedBigInt UnsignedBigInt::operator~() const {
	UnsignedBigInt result(*this);
	for(digits_size_t c=0; c<result.mDigits.size(); c++)
		result.mDigits.at(c) = ~result.mDigits.at(c);
	result.trimLeadingZeros();
	return result;
}

#pragma endregion

#pragma region Public Methods

void UnsignedBigInt::print(std::ostream& os) const {

#ifdef BIGINT_PSEUDO_DECIMAL_BASE

	calc_t decimalDigitsInADigit = static_cast<calc_t>( log10(static_cast<long double>(mBase) ) );
    os << mDigits.front(); // no padding for most significant digit
    for ( digits_size_t i = 1; i < mDigits.size() ; i++) {
            os << std::setfill('0') << std::setw(decimalDigitsInADigit) << mDigits.at(i);
    }

#else

	if (*this == 0) {
		os << "0";
		return;
	}

	store_t chunk_base = getPrintBase();
	int chunk_digits = static_cast<int>( log10(static_cast<long double>(chunk_base) ) );

	std::string buffer;
	std::vector<const std::string> chunksVector;
	
	UnsignedBigInt this_copy(*this);
	UnsignedBigInt chunk;

	DivisionResult result;

	while ( this_copy > 0 ) {
		this_copy.divide(chunk_base, result);
		chunk = *(result.remainder);
		this_copy = *(result.quotient);
		buffer = std::to_string(static_cast<unsigned long long>(chunk.mDigits.front()));
		BigIntUtilities::leftPadChunk(buffer, chunk_digits);
		chunksVector.insert(chunksVector.begin(), std::string(buffer));
	}

	buffer = chunksVector.front();
	BigIntUtilities::trimLeadingZeros(buffer);
	os << buffer;

	for(digits_size_t i=1; i<chunksVector.size(); i++) {
		os << chunksVector.at(i);
	}

#endif

}

std::string UnsignedBigInt::toString() const {
	std::string returnString;
	std::stringstream ss;
    ss << *this;
	return returnString = ss.str();
}

std::vector<bool> UnsignedBigInt::digitToBinary(store_t iDigit) {
	std::vector<bool> ret = std::vector<bool>();
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

#ifdef BIGINT_PSEUDO_DECIMAL_BASE

	calc_t max_value = static_cast<calc_t>(std::numeric_limits<store_t>::max());
	calc_t base = 1, prev_base = 1;
	while (base >= prev_base && base < max_value) {
		prev_base = base;
		base *= 10;
	}
	return static_cast<store_t>(prev_base);

#else
	
	return static_cast<calc_t>(std::numeric_limits<store_t>::max());

#endif
	
}

const store_t UnsignedBigInt::getPrintBase() const {
	// largest power of ten that fits store_t
	calc_t max_value = mBase - 1;
	calc_t base = 1, prev_base = 1;
	while (base >= prev_base && base < max_value) {
		prev_base = base;
		base *= 10;
	}
	return static_cast<store_t>(prev_base);
}

void UnsignedBigInt::trimLeadingZeros() {
	std::vector<store_t>::iterator it = mDigits.begin();
	while ( *it == 0 && mDigits.size() > 1 ) {
		it = mDigits.erase(it);
		it = mDigits.begin();
	}
}

const UnsignedBigInt UnsignedBigInt::multiplyByDigit(const store_t &iMultiplier) const {
	UnsignedBigInt tmpUnsignedBigInt = UnsignedBigInt(*this);
	digits_size_t size = tmpUnsignedBigInt.mDigits.size();
	calc_t multiplier, current_digit, tmp, carry;
	multiplier = multiplier = static_cast<calc_t>(iMultiplier);
	carry = 0;
	for ( digits_size_t i = 0; i < size; i++ ) {
		// promote both to calc_t
		current_digit = static_cast<calc_t>(tmpUnsignedBigInt.mDigits.at(size - 1 - i));
		tmp = current_digit * multiplier + carry;
		carry = tmp / mBase;
		tmpUnsignedBigInt.mDigits.at(size - 1 - i) = static_cast<store_t>(tmp % mBase);
	}
	if (carry)
		tmpUnsignedBigInt.mDigits.insert(tmpUnsignedBigInt.mDigits.begin(), carry);
	return tmpUnsignedBigInt;
}

void UnsignedBigInt::divide(const UnsignedBigInt &iDivisor, DivisionResult &oDivisionResult) {

	if (iDivisor == 0)
		throw DivideByZeroException();

	UnsignedBigInt subdividend, product;
	UnsignedBigInt *subremainder = new UnsignedBigInt();
	UnsignedBigInt *quotient = new UnsignedBigInt();
	digits_size_t n, dividend_size;
	store_t multiplier;
	bool first_round = true;

	n = 1;
		
	dividend_size = mDigits.size();
	subdividend = 0;

	// pick first n digits of dividend until subdividend > divisor
	do {
		subdividend.mDigits = std::vector<store_t>(mDigits.begin(), mDigits.begin()+n);
		n++;
	} while (subdividend < iDivisor && n <= dividend_size);

	// remove the picked digits from dividend
	mDigits = std::vector<store_t>(mDigits.begin() + (n-1), mDigits.end());
		
	// find out how many times divisor fits into subdividend
	multiplier = guessMultiplier(iDivisor, subdividend);
	subdividend -= iDivisor * multiplier;
	subremainder->mDigits = subdividend.mDigits;
	quotient->mDigits.push_back(multiplier);

	while ( mDigits.size() > 0 ) {
		subdividend = *subremainder * mBase + mDigits.front();
		mDigits.erase(mDigits.begin());
		multiplier = guessMultiplier(iDivisor, subdividend);
		subdividend -= iDivisor * multiplier;
		subremainder->mDigits = subdividend.mDigits;
		quotient->mDigits.push_back(multiplier);
	}

	quotient->trimLeadingZeros();

	oDivisionResult.quotient = quotient;
	oDivisionResult.remainder = subremainder;

}

UnsignedBigInt& UnsignedBigInt::quotient(const UnsignedBigInt &iThat) {
	DivisionResult result;
	divide(iThat, result);
	*this = *(result.quotient);
	return *this;
}

UnsignedBigInt& UnsignedBigInt::remainder(const UnsignedBigInt &iThat) {
	DivisionResult result;
	divide(iThat, result);
	*this = *(result.remainder);
	return *this;
}

store_t UnsignedBigInt::guessMultiplier(const UnsignedBigInt& iDivisor, const UnsignedBigInt& iDividend) {

	store_t min = 0;
	store_t max = std::numeric_limits<store_t>::max();
	store_t j;
	UnsignedBigInt tmp;

	while (max - min > 1 ) {
		j = static_cast<store_t>( ( static_cast<calc_t>(max) + static_cast<calc_t>(min) ) / 2 );
		tmp = iDivisor * j;
		if (tmp == iDividend) {
			return j;
		} else if (tmp < iDividend) {
			min = j;
		} else if (tmp > iDividend) {
			max = j;
		}
	}

	return iDivisor * max > iDividend ? min : max;
}

#pragma endregion

#pragma region Stream operators and Exponentation

std::ostream& operator<<( std::ostream& os, const UnsignedBigInt& iUnsignedBigInt ) {
	iUnsignedBigInt.print(os);
	return os;
}

std::istream& operator>>( std::istream& is, UnsignedBigInt& iUnsignedBigInt ) {
	// read obj from stream
	std::string tmp = "";
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
		binaryDigit = UnsignedBigInt::digitToBinary(iExponent.mDigits.at(i));
		for (unsigned short j=0; j<binaryDigit.size(); j++) {
			result *= result;
			if (binaryDigit.at(j))
				result *= iBase;
		}
	}
	return result;
}

#pragma endregion
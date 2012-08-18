/*! 
 *  Some template metaprogramming to automagically get the best type
 *  to store a BigInt digit, depending on maximum integer available
 *  on this implementation.
 *  \see http://stackoverflow.com/questions/12018410/how-do-i-find-the-largest-integer-supported-fully-by-hardware-arithmetics
 *  \see http://stackoverflow.com/questions/7038797/automatically-pick-a-variable-type-big-enough-to-hold-a-specified-number
 *  -
 *  BigInt Homework - Advanced cpp programming
 *  Master in Computer Game Development, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 5 August 2012
 */

#include <stdint.h>

template<unsigned long long Max>
struct RequiredBits
{
    enum {
		value = Max <= 0xffff     ?  8 :
				Max <= 0xffffffff ? 16 :
									32
    };
};

template<int bits> struct SelectDigitType_;
template<> struct SelectDigitType_ <8> { typedef uint8_t type; };
template<> struct SelectDigitType_<16> { typedef uint16_t type; };
template<> struct SelectDigitType_<32> { typedef uint32_t type; };

template<unsigned long long Max>
struct SelectDigitType : SelectDigitType_<RequiredBits<Max>::value> {};

typedef SelectDigitType<INTMAX_MAX>::type digit_t;
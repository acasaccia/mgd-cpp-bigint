
BigInt Homework - Advanced cpp programming
Master in Computer Game Development, Verona, Italy
See problem description @ https://code.google.com/p/mgd-cpp-bigint/

author Andrea Casaccia
date 5 August 2012

===============================================================================

SIGNED ARBITRARY BIG INTEGERS

Having UnsignedBigInt up and running I thinked of BigInt as an UnsignedBigInt
with a sign. I forwarded to UnsignedBigInt all the arithmetics making the
necessary sign juggling to perform valid unsigned operations.

===============================================================================

UNSIGNED BIGINT INTERNAL REPRESENTATION

Performance-wise the ideal choice is to use as base the square root of the
largest integer supported fully by hardware arithmetics. Larger bases allow to
represent the same number with less digits, and avoiding overflow grants us
the best efficiency over the used hardware. [1]

I defined two basic types:
store_t to store a single digit,
calc_t to perform arithmetics on two digits avoiding overflow

typedef uint32_t store_t;
typedef uint64_t calc_t;

These typedefs should be adjusted to get the best performance from the used
hardware. If for example 64bit arithmetic is supported, it is better to use a
64bit type for calculations, and to store digits in a 32bit type to avoid
overflow when multiplying two of them. [2]

Using an unsigned type gives the advantage of non having to worry masking
the high bit at any time.

On the other side, conversion to base 10 will be necessary when displaying
to get a human readable representation.

I found an interesting compromise between SPEED - SPACE - READABILITY is using
the largest power of ten that fits into the chosen store type. It saves a lot of
space and gives a huge performance boost compared to decimal representation and
saves us having to bother for conversions. Debugging is also a lot easier.

The tradeoff is on bitwise/shift operators: they have worse performance and slightly
more complex implementation.

[1] "The Algorithm Design Manual" Skiena S. pag. 423
[2] My question on SO on how to pick the correct digit size:
	 http://stackoverflow.com/questions/12018410/how-do-i-find-the-largest-integer-fully-supported-by-hardware-arithmetics

===============================================================================

UNSIGNED BIGINT ARITHMETICS

All binary operators have been implemented in terms of their compound operators,
so look at those to see the actual code.

Additions, subtractions and multiplications have been implemented with the basic
schoolhouse method: they are well known and perform reasonably well. [3]

For division I had to implement a binary search when looking for how many times
divisor fits into dividend, this way I achieved decent performances for the
purpose of this project.

For exponentation I used exponentation by squaring method:
http://en.wikipedia.org/wiki/Exponentiation_by_squaring

[3] "The Art of Computer Programming", Knuth D. E. pag. 265

===============================================================================

IMPLEMENTATION NOTES

The sign of % operator has been implemented as in the C++11 specification,
the same as dividend. http://en.wikipedia.org/wiki/Modulo_operation

Shift operators have been implemented as "arithmetic" shifts, simply stating
that a << b = a * 2^b . The standard discourages the use of shift with
signed integer types, because the result is implementation dependent. In this
implementation I preserve the sign and work as expected on number's magnitude.

Shifting by a negative value is undefined behaviour in the standard, I throw an
exception when it happens.

Other bitwise operators are implemented as plain "logical" operators: I perform
those digit to digit. If one operand is smaller in digits than the other, its
missing digits are considered zeros. For (signed) BigInt sign is taken into
account: "+" is a true value, "-" a false one.

===============================================================================

KNOWN BUGS

I must have used some uninitiliazed variable somewhere :/
All works in Debug mode but when compiling in Release I get undefined behaviour.

===============================================================================
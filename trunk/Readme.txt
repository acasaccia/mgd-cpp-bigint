
BigInt Homework - Advanced cpp programming
Master in Computer Game Development, Verona, Italy
See problem description @ https://code.google.com/p/mgd-cpp-bigint/

author Andrea Casaccia
date 5 August 2012

===============================================================================

INTERNAL REPRESENTATION

To do the arithmetic the ideal choice is to use as base the square root of the
largest integer supported fully by hardware arithmetics. Larger bases allow to
represent the same number with less digits, and avoiding overflow grants us
the best efficiency over the used hardware.

Two basic types are defined:
store_t to store a single digit,
calc_t to perform arithmetics on two digits avoiding overflow

typedef uint32_t store_t;
typedef uint64_t calc_t;

These typedefs should be adjusted to get the best performance from the used
hardware. If for example 64bit arithmetic is supported, it is better to use a
64bit type for calculations while storing digits in a 32bit type to avoid
overflow when multiplying two of them. [2]

Using an unsigned type should give the advantage of non having to worry masking
the high bit at any time. [3]

On the other side, conversion to base 10 will be necessary when displaying
to get a human readable representation. [1]

I found an interesting compromise between SPEED - SPACE - HUMAN READABILITY is using
as the base for big integer representation the largest power of ten that fits into
the chosen store type [4]. It saves a lot of space compared to decimal representation
and saves us having to bother for conversions. Debug is also a lot easier.

[1] "The Algorithm Design Manual" - S. Skiena, pag 423.
[2], [3] My question on SO on how to avoid hardware overflow:
http://stackoverflow.com/questions/12018410/how-do-i-find-the-largest-integer-supported-fully-by-hardware-arithmetics
[4] Some suggestions on how to implement arbitrary precision arithmetic. The guy uses signed
	basic types instead of unsigned (which doesn't seem a great idea), but the "largest power
	of ten base" method is great.
http://stackoverflow.com/questions/1218149/arbitrary-precision-arithmetic-explanation

===============================================================================

SIGNED ARBITRARY BIG INTEGERS


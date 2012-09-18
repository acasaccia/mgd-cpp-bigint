
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
the best efficiency over the used hardware. [*]

Two basic types are defined:
store_t to store a single digit,
calc_t to perform arithmetics on two digits avoiding overflow

typedef uint32_t store_t;
typedef uint64_t calc_t;

These typedefs should be adjusted to get the best performance from the used
hardware. If for example 64bit arithmetic is supported, it is better to use a
64bit type for calculations while storing digits in a 32bit type to avoid
overflow when multiplying two of them.

Using an unsigned type should give the advantage of non having to worry masking
the high bit at any time.

On the other side, conversion to base 10 will be necessary when displaying
to get a human readable representation.

I found an interesting compromise between SPEED - SPACE - REPRESENTATION is using
as the base for big integer representation the largest power of ten that fits into
the chosen store type. It saves a lot of space compared to decimal representation
and saves us having to bother for conversions. Debug is also a lot easier.

===============================================================================

UNSIGNED ARBITRARY INTEGER ARITHMETICS

All binary operators have been implemented in terms of their compound operators,
so look at those to see the actual code.
Additions, subtractions and multiplications have been implemented with the basic
schoolhouse method: they are well known and perform reasonably well.

For division the only trick I had to implement was a binary search when looking
at how many times divisor fits into dividend, linear one with large cipher was
incredibly slow.

===============================================================================

SIGNED ARBITRARY BIG INTEGERS

Having UnsignedBigInt up and running I implemented unary sign operator on a 
wrapper class, transposing the actual arithmetics to UnsignedBigInt as necessary.

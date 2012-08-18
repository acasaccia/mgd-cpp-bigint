
BigInt Homework - Advanced cpp programming
Master in Computer Game Development, Verona, Italy
See problem description @ https://code.google.com/p/mgd-cpp-bigint/

author Andrea Casaccia
date 5 August 2012

===============================================================================

I made the basic design choices after reading the arbitrary-precision
arithmetic chapter on "The Algorithm Design Manual" by S.Skiena, pag 423.

To do the arithmetic the ideal choice is to use as base the square root of the
largest integer supported fully by hardware arithmetics. Larger bases allow to
represent the same number with less digits, while avoiding overflow grants us
the best efficiency over the used hardware.

According to C++11 that type is: std::intmax_t
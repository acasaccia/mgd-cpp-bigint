/*! 
 *  These typedefs should be adjusted to get the best performance from your hardware.
 *  If for example 64bit arithmetic is supported, it is better to use a 64bit type
 *  for calculations and store digits in a 32bit type to avoid overflow  when 
 *  multiplying two of them.
 *  \see Readme.txt
 *  \see http://stackoverflow.com/questions/12018410/how-do-i-find-the-largest-integer-supported-fully-by-hardware-arithmetics
 *  -
 *  BigInt Homework - Advanced cpp programming
 *  Master in Computer Game Development, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 5 August 2012
 */

#pragma once

#include <cstdint>

typedef int32_t store_t;
typedef int64_t calc_t;
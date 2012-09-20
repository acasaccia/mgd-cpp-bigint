/*! 
 *  The following typedefs should be adjusted to get the best performance from your hardware.
 *  If for example 64bit arithmetic is supported, it is better to use a 64bit type
 *  for calculations and store digits in a 32bit type to avoid overflow  when multiplying two of them.
 *  Using unsigned types is required by the implementation.
 *  -
 *  BigInt Homework - Advanced cpp programming
 *  Master in Computer Game Development, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 5 August 2012
 */

#pragma once

typedef uint32_t store_t;	// type to store a digit
typedef uint64_t calc_t;	// type to perform calculation on two digits without hardware overlflow, see my question on how to choose this:
							// http://stackoverflow.com/questions/12018410/how-do-i-find-the-largest-integer-supported-fully-by-hardware-arithmetics

typedef std::vector<store_t>::size_type digits_size_t;

enum DivisionResult { QUOTIENT, REMAINDER };
enum Sign { POSITIVE, NEGATIVE };
/*! 
 *  BigInt class implementation
 *  -
 *  BigInt Homework - Advanced cpp programming
 *  Master in Computer Game Development, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 5 August 2012
 */

#include "BigInt.h"
#include <vector>

BigInt::BigInt() {
	mRepresentation = std::vector<store_t> ();
	mRepresentation.push_back(0);
}

BigInt::BigInt(int iInteger) {
	mRepresentation = std::vector<store_t> ();
	mRepresentation.push_back(iInteger);
}

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
	mRepresentation = std::vector<bool> ();
	mRepresentation.push_back(false);
}

BigInt::BigInt(int iInteger) {
	while ( iInteger > 1 ) {
		iInteger%=2;
		mRepresentation.push_back(static_cast<bool>(iInteger));
	}
}

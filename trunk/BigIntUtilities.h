/*! 
 *  Some namespaced utilities functions reused here and there in the library.
 *  -
 *  BigInt Homework - Advanced cpp programming
 *  Master in Computer Game Development, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 5 August 2012
 */

#pragma once

#include <string>

namespace BigIntUtilities {
	void trimLeadingZeros(std::string& ioString);
	void removeWhitespaces(std::string& ioString);
}
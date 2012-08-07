/*! 
 *  BigInt class header
 *  -
 *  BigInt Homework - Advanced cpp programming
 *  Master in Computer Game Development, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 5 August 2012
 */

#pragma once
#include <vector>

class BigInt {
public:
	BigInt();
	BigInt(int iInteger);
private:
	std::vector<bool> mRepresentation;
};

/*! 
 *  Exceptions thrown by BigInt operations
 *  -
 *  BigInt Homework - Advanced cpp programming
 *  Master in Computer Game Development, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 5 August 2012
 */

#pragma once

#include <exception>

class BadStringInitializationException : public std::exception {
	const char* what() const { return "Invalid characters found in initialization string.";	}
};

class BadIntegerInitializationException : public std::exception {
	const char* what() const { return "Tried to initialize an UnsignedBigInt with a negative value."; }
};

class InvalidSubtractionException : public std::exception {
	const char* what() const { return "Tried to perform an UnsignedBigInt subtraction which would result in a negative value."; }
};

class DivideByZeroException : public std::exception {
	const char* what() const { return "Tried to perform division by zero.";	}
};

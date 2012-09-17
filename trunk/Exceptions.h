
#pragma once

#include <exception>

class BadIntegerInitializationException : std::exception {
	const char* what() const {
		return "Can't initialize from negative integer.";
	}
};

class BadStringInitializationException : std::exception {
	const char* what() const {
		return "Can't initialize from string. Allowed characters: [0-9].";
	}
};

class InvalidSubtractionException : std::exception {
	const char* what() const {
		return "Tried to perform subtraction on two UnsignedBigInt which would have caused a negative value.";
	}
};

class DivideByZeroException : std::exception {
	const char* what() const {
		return "Tried to perform division by zero.";
	}
};

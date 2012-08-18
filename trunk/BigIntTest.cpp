/*! 
 *  BigInt test
 *  -
 *  BigInt Homework - Advanced cpp programming
 *  Master in Computer Game Development, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 5 August 2012
 */

#include <ctime>
#include <string>
#include <vector>
#include <iostream>
#include "BigInt.h"

int main(int argc, char **argv) {

	std::clock_t begin = clock();

	std::vector<std::string> args(argv, argv + argc);

	BigInt* test = new BigInt(15);

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << __cplusplus << std::endl;
	std::cout << "Done [Elapsed: " << elapsed_secs << "\"]" << std::endl;

	return EXIT_SUCCESS;
}
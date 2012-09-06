/*! 
 *  BigInt test
 *  -
 *  BigInt Homework - Advanced cpp programming
 *  Master in Computer Game Development, Verona, Italy
 *  -
 *  \author Andrea Casaccia
 *  \date 5 August 2012
 */

#include "gtest/gtest.h"
#include "BigInt.h"
#include <iostream>
#include <sstream>
#include <string>

namespace {

	// The fixture for testing class Foo.
	class UnsignedBigIntTest : public ::testing::Test {};

	// I wrote this tests copy/pasting from a Sage worksheet http://www.sagemath.org/

	TEST_F(UnsignedBigIntTest, StringConstructors) {
		UnsignedBigInt a = UnsignedBigInt("47562497562947562947650245792");
		ASSERT_STREQ("47562497562947562947650245792",(a).toString().c_str());
		a = UnsignedBigInt("657465327280000000000000000000000245");
		ASSERT_STREQ("657465327280000000000000000000000245",(a).toString().c_str());
		a = UnsignedBigInt("00000000000010000000011111111000000000000000000000100000000011111111");
		ASSERT_STREQ("10000000011111111000000000000000000000100000000011111111",(a).toString().c_str());
	}

	TEST_F(UnsignedBigIntTest, Comparison) {
		UnsignedBigInt a, b, c;
		a = UnsignedBigInt("62497562947562947650245791");
		b = UnsignedBigInt("47562497562947562947650245792");
		ASSERT_TRUE(a < b);
		ASSERT_TRUE(a != b);
		ASSERT_TRUE(b > a);
		a = UnsignedBigInt("47562497562947562947650245791");
		b = UnsignedBigInt("47562497562947562947650245792");
		ASSERT_TRUE(a < b);
		ASSERT_TRUE(a != b);
		ASSERT_TRUE(b > a);
		a = UnsignedBigInt("29465429765154625427428736298750983567364537654286498479402989765564526565265466");
		b = UnsignedBigInt("29465429765154625427428736298750983567364537654286498479402989765564526565265466");
		ASSERT_TRUE(a == b);
		ASSERT_TRUE(a <= b);
		ASSERT_TRUE(a >= b);
	}

	TEST_F(UnsignedBigIntTest, Additions) {
		UnsignedBigInt a, b, c;
		a = UnsignedBigInt("47562497562947562947650245792");
		b = UnsignedBigInt(   "24729560249562456409874450");
		c = a + b;
		ASSERT_STREQ("47587227123197125404060120242",(c).toString().c_str());
		a = UnsignedBigInt("78652846526572987549028759875928462846584276548276582476584726584725682745684276");
		b = UnsignedBigInt("29465429765154625427428736298750983567364537654286498479402989765564526565265466");
		c = UnsignedBigInt();
		c += a; c += b;
		ASSERT_STREQ("108118276291727612976457496174679446413948814202563080955987716350290209310949742",(c).toString().c_str());
		a = UnsignedBigInt("232635627000000000000006834562312");
		b = UnsignedBigInt("234562");
		c = a + b;
		ASSERT_STREQ("232635627000000000000006834796874",(c).toString().c_str());
	}

	TEST_F(UnsignedBigIntTest, Subtractions) {
		UnsignedBigInt a, b, c;
		a = UnsignedBigInt("1");
		b = UnsignedBigInt("2");
		c = a - b;
		ASSERT_STREQ("999999999999999999",(c).toString().c_str());
		a = UnsignedBigInt("8375639165791754013759651937651937651937659");
		b = UnsignedBigInt("747214317243172437125");
		c = a - b;
		ASSERT_STREQ("8375639165791754013758904723334694479500534",(c).toString().c_str());
		a = UnsignedBigInt("72456128765412865184556316565331561365183658675015640194857109547601956130749");
		b = UnsignedBigInt("154817245182745182549124591287462198456354127964531876541872458127654712");
		a -= b;
		ASSERT_STREQ("72455973948167682439373767440740273902985202320887675662980567675143828476037",(a).toString().c_str());
	}

	TEST_F(UnsignedBigIntTest, Multiplications) {
	}
	
	TEST_F(UnsignedBigIntTest, Divisions) {
	}

	TEST_F(UnsignedBigIntTest, IncrementDecrement) {
		UnsignedBigInt a = UnsignedBigInt("8375639165791754013759651937651937651937659");
		ASSERT_STREQ("8375639165791754013759651937651937651937660",(++a).toString().c_str());
		a--;
		ASSERT_STREQ("8375639165791754013759651937651937651937659",(a).toString().c_str());
		ASSERT_STREQ("8375639165791754013759651937651937651937659",(a++).toString().c_str());
		ASSERT_STREQ("8375639165791754013759651937651937651937660",(a).toString().c_str());
	}

	TEST_F(UnsignedBigIntTest, IOStreams) {
		std::stringstream ss (std::stringstream::in | std::stringstream::out);
		std::stringstream out (std::stringstream::in | std::stringstream::out);
		UnsignedBigInt a;
		ss << "184518345183764381746 ThisShouldFailAssert";
		ss >> a;
		out << a;
		ASSERT_FALSE(ss.fail());
		ASSERT_STREQ("184518345183764381746",(out).str().c_str());
		ss >> a;
		ASSERT_TRUE(ss.fail());
	}


}  // namespace

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

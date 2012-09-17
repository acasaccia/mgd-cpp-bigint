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
#include <limits>

namespace {

	// The fixture for testing class UnsignedBigInt.
	class UnsignedBigIntTest : public ::testing::Test {};

	// The operations on huge integers in this tests have been copy/pasted from a Sage worksheet http://www.sagemath.org/

	#pragma region Integer constructors

	TEST_F(UnsignedBigIntTest, IntegerConstructors) {

		UnsignedBigInt a, b;
		ASSERT_THROW(a = UnsignedBigInt(-1), BadIntegerInitializationException);

		a = 4;
		ASSERT_STREQ("4", a.toString().c_str());

		a = 12345;
		ASSERT_STREQ("12345", a.toString().c_str());

		a = 4294967295;
		ASSERT_STREQ("4294967295", a.toString().c_str());

		a = 441243123294967295;
		ASSERT_STREQ("441243123294967295", a.toString().c_str());

	}

	#pragma endregion

	#pragma region String constructors

	TEST_F(UnsignedBigIntTest, StringConstructors) {

		UnsignedBigInt a;
		ASSERT_THROW(a = UnsignedBigInt("WAT?"), BadStringInitializationException);
		ASSERT_THROW(a = UnsignedBigInt("-1"), BadStringInitializationException);

		a = UnsignedBigInt("00000000");
		ASSERT_STREQ("0",(a).toString().c_str());

		a = UnsignedBigInt("47562497562947562947650245792");
		ASSERT_STREQ("47562497562947562947650245792", a.toString().c_str());

		a = UnsignedBigInt("657465327280000000000000000000000245");
		ASSERT_STREQ("657465327280000000000000000000000245", a.toString().c_str());

		a = UnsignedBigInt("00000000000010000000011111111000000000000000000000100000000011111111");
		ASSERT_STREQ("10000000011111111000000000000000000000100000000011111111",(a).toString().c_str());

	}

	#pragma endregion

	#pragma region Comparison

	TEST_F(UnsignedBigIntTest, Comparison) {

		UnsignedBigInt a, b;
		a = UnsignedBigInt("62497562947562947650245791");
		b = UnsignedBigInt("47562497562947562947650245792");
		ASSERT_TRUE(a < b);
		ASSERT_TRUE(a != b);
		ASSERT_TRUE(b > a);
		ASSERT_FALSE(b > b);
		ASSERT_FALSE(b != b);

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
		ASSERT_FALSE(a > b);
		ASSERT_FALSE(b < a);

	}

	#pragma endregion

	#pragma region Additions

	TEST_F(UnsignedBigIntTest, Additions) {

		UnsignedBigInt a, b, c;
		a = UnsignedBigInt("47562497562947562947650245792");
		b = UnsignedBigInt("247295602495624564");
		c = a + b;
		ASSERT_STREQ("47562497563194858550145870356", c.toString().c_str());

		a = UnsignedBigInt("247295602495624564");
		b = UnsignedBigInt("47562497562947562947650245792");
		c = a + b;
		ASSERT_STREQ("47562497563194858550145870356", c.toString().c_str());

		a = UnsignedBigInt("78652846526572987549028759875928462846584276548276582476584726584725682745684276");
		b = UnsignedBigInt("29465429765154625427428736298750983567364537654286498479402989765564526565265466");
		c = UnsignedBigInt();
		c += a;
		c += b;
		ASSERT_STREQ("108118276291727612976457496174679446413948814202563080955987716350290209310949742", c.toString().c_str());

		a = UnsignedBigInt("232635627000000000000006834562312");
		b = UnsignedBigInt("234562");
		c = a + b;
		ASSERT_STREQ("232635627000000000000006834796874", c.toString().c_str());

		c = b + 100;
		ASSERT_STREQ("234662", c.toString().c_str());

		c += 330;
		ASSERT_STREQ("234992", c.toString().c_str());
	}

	#pragma endregion

	#pragma region Subtractions

	TEST_F(UnsignedBigIntTest, Subtractions) {

		UnsignedBigInt a, b, c;
		a = UnsignedBigInt("1");
		b = UnsignedBigInt("2");
		ASSERT_THROW(a - b, InvalidSubtractionException);

		a = UnsignedBigInt("8375639165791754013759651937651937651937659");
		b = UnsignedBigInt("747214317243172437125");
		c = a - b;
		ASSERT_STREQ("8375639165791754013758904723334694479500534", c.toString().c_str());

		a = UnsignedBigInt("72456128765412865184556316565331561365183658675015640194857109547601956130749");
		b = UnsignedBigInt("154817245182745182549124591287462198456354127964531876541872458127654712");
		a -= b;
		ASSERT_STREQ("72455973948167682439373767440740273902985202320887675662980567675143828476037", a.toString().c_str());

		a = UnsignedBigInt("747214317243172437126");
		b = UnsignedBigInt("747214317243172437125");
		c = a - b;
		ASSERT_STREQ("1", c.toString().c_str());

		a = UnsignedBigInt("747214317243172437126");
		b = UnsignedBigInt("747214317243172437126");
		c = a - b;
		ASSERT_STREQ("0", c.toString().c_str());
	}

	#pragma endregion

	#pragma region Multiplications

	TEST_F(UnsignedBigIntTest, Multiplications) {

		UnsignedBigInt a, b, c;

		a = UnsignedBigInt("24729560249562456409874450");
		ASSERT_STREQ((a+a).toString().c_str(), (a * 2).toString().c_str());

		a = UnsignedBigInt("24729560249562456409874450");
		ASSERT_STREQ("335431755225065158743537039800", (a * 13564).toString().c_str());

		a = UnsignedBigInt("24729560249562456409874450");
		ASSERT_STREQ("609230695138272545563067054475150", (a * 24635727).toString().c_str());

		a = UnsignedBigInt("24729560249562456409874450");
		b = UnsignedBigInt("1465175465341265345612");
		ASSERT_STREQ("36233144946337530042279736528864738908778413400", (a * b).toString().c_str());

		a = UnsignedBigInt("1745918347510738461398467013641034601346717386413846138764");
		b = UnsignedBigInt("71654715471634517635471364571364571141314314134314314");
		ASSERT_STREQ("125103282427588281550192056577169443769029849466081089451295466250281217549479829973992739353032132125635467896", (a * b).toString().c_str());

	}

	#pragma endregion

	#pragma region Divisions
	
	TEST_F(UnsignedBigIntTest, Divisions) {

		UnsignedBigInt a, b, c;

		a = UnsignedBigInt("10002893652093475029347699500345000015858500009475000011111");
		b = UnsignedBigInt("0000");
		ASSERT_THROW(a / b, DivideByZeroException);

		a = UnsignedBigInt("10000000000000000000000000000000000000000000000000000011111");
		b = UnsignedBigInt("500000000000000000000000000000");
		ASSERT_STREQ("20000000000000000000000000000", (a / b).toString().c_str());

		a = UnsignedBigInt("220000000000222");
		b = UnsignedBigInt("2");
		ASSERT_STREQ("110000000000111", (a / b).toString().c_str());

		a = UnsignedBigInt("47562497562947562947650245792");
		b = UnsignedBigInt("247295602495624564");
		ASSERT_STREQ("192330543216", (a / b).toString().c_str());

		a = UnsignedBigInt("236135716361436519856974811659278549273845691284519254912345");
		b = UnsignedBigInt("983475693482652938765924387652938756");
		ASSERT_STREQ("240103256162071692058670", (a / b).toString().c_str());

	}

	#pragma endregion

	#pragma region Arithmetics summary

	TEST_F(UnsignedBigIntTest, ArithmeticSummary) {

		UnsignedBigInt a, b;

		a = UnsignedBigInt("37865392874568327496520394757622039865203956870394562309874569238569238745693287659287345629387546928375693874569238745692387");
		b = a + a;

		ASSERT_STREQ((b / 2).toString().c_str(), (a).toString().c_str());
		ASSERT_STREQ((b * b).toString().c_str(), (a * a * 4).toString().c_str());
		ASSERT_STREQ((b * b - a).toString().c_str(), ((a * a * 4) - a).toString().c_str());

	}
	#pragma endregion

	#pragma region Remainders

	TEST_F(UnsignedBigIntTest, Remainder) {

		UnsignedBigInt a, b, c;

		a = UnsignedBigInt("10000000000000000000000000000000000000000000000000000011111");
		b = UnsignedBigInt("500000000000000000000000000000");
		ASSERT_STREQ("11111", (a % b).toString().c_str());

		a = UnsignedBigInt("47562497562947562947650245792");
		b = UnsignedBigInt("247295602495624564");
		ASSERT_STREQ("36085290337087968", (a % b).toString().c_str());

		a = UnsignedBigInt("236135716361436519856974811659278549273845691284519254912345");
		b = UnsignedBigInt("983475693482652938765924387652938756");
		ASSERT_STREQ("290962808750621283678503626186097825", (a % b).toString().c_str());

	}	

	#pragma endregion

	#pragma region Increment / Decrement

	TEST_F(UnsignedBigIntTest, IncrementDecrement) {
		UnsignedBigInt a = UnsignedBigInt("8375639165791754013759651937651937651937659");
		ASSERT_STREQ("8375639165791754013759651937651937651937660", (++a).toString().c_str());
		a--;
		ASSERT_STREQ("8375639165791754013759651937651937651937659", a.toString().c_str());
		ASSERT_STREQ("8375639165791754013759651937651937651937659", (a++).toString().c_str());
		ASSERT_STREQ("8375639165791754013759651937651937651937660", a.toString().c_str());
	}

	#pragma endregion

	#pragma region Input / Output streams

	TEST_F(UnsignedBigIntTest, IOStreams) {
		std::stringstream ss (std::stringstream::in | std::stringstream::out);
		std::stringstream out (std::stringstream::in | std::stringstream::out);
		UnsignedBigInt a;
		ss << "184518345183764381746 ThisWillMakeInputStreamFail";
		ss >> a;
		out << a;
		ASSERT_FALSE(ss.fail());
		ASSERT_STREQ("184518345183764381746", out.str().c_str());
		ss >> a;
		ASSERT_TRUE(ss.fail());
	}

	#pragma endregion



	// The fixture for testing class BigInt.
	class BigIntTest : public ::testing::Test {};

	TEST_F(BigIntTest, Nothing) {
	}


}  // namespace

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

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
#include <fstream>
#include <streambuf>

namespace {

	class UnsignedBigIntTest : public ::testing::Test {};

	// The operations on big integers have been copy/pasted from a Sage worksheet http://www.sagemath.org/

	#pragma region Integer constructors

	TEST_F(UnsignedBigIntTest, IntegerConstructors) {

		UnsignedBigInt a;
		ASSERT_THROW(a = UnsignedBigInt(-1), BadIntegerInitializationException);

		a = 4;
		ASSERT_EQ("4", a.toString());

		a = 12345;
		ASSERT_EQ("12345", a.toString());

		a = 4294967295;
		ASSERT_EQ("4294967295", a.toString());

		a = 441243123294967295;
		ASSERT_EQ("441243123294967295", a.toString());

	}

	#pragma endregion

	#pragma region String constructors

	TEST_F(UnsignedBigIntTest, StringConstructors) {

		UnsignedBigInt a;
		ASSERT_THROW(a = UnsignedBigInt("WAT?"), BadStringInitializationException);
		ASSERT_THROW(a = UnsignedBigInt("-1"), BadStringInitializationException);

		a = UnsignedBigInt("00000000");
		ASSERT_EQ("0", a.toString());

		a = UnsignedBigInt("47562497562947562947650245792");
		ASSERT_EQ("47562497562947562947650245792", a.toString());

		a = UnsignedBigInt("657465327280000000000000000000000245");
		ASSERT_EQ("657465327280000000000000000000000245", a.toString());

		a = UnsignedBigInt("00000000000010000000011111111000000000000000000000100000000011111111");
		ASSERT_EQ("10000000011111111000000000000000000000100000000011111111", a.toString());

	}

	#pragma endregion

	#pragma region Comparisons

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
		ASSERT_EQ("47562497563194858550145870356", c.toString());

		a = UnsignedBigInt("247295602495624564");
		b = UnsignedBigInt("47562497562947562947650245792");
		c = a + b;
		ASSERT_EQ("47562497563194858550145870356", c.toString());

		a = UnsignedBigInt("78652846526572987549028759875928462846584276548276582476584726584725682745684276");
		b = UnsignedBigInt("29465429765154625427428736298750983567364537654286498479402989765564526565265466");
		c = UnsignedBigInt();
		c += a;
		c += b;
		ASSERT_EQ("108118276291727612976457496174679446413948814202563080955987716350290209310949742", c.toString());

		a = UnsignedBigInt("232635627000000000000006834562312");
		b = UnsignedBigInt("234562");
		c = a + b;
		ASSERT_EQ("232635627000000000000006834796874", c.toString());

		c = b + 100;
		ASSERT_EQ("234662", c.toString());

		c += 330;
		ASSERT_EQ("234992", c.toString());

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
		ASSERT_EQ("8375639165791754013758904723334694479500534", c.toString());

		a = UnsignedBigInt("72456128765412865184556316565331561365183658675015640194857109547601956130749");
		b = UnsignedBigInt("154817245182745182549124591287462198456354127964531876541872458127654712");
		a -= b;
		ASSERT_EQ("72455973948167682439373767440740273902985202320887675662980567675143828476037", a.toString());

		a = UnsignedBigInt("747214317243172437126");
		b = UnsignedBigInt("747214317243172437125");
		c = a - b;
		ASSERT_EQ("1", c.toString());

		a = UnsignedBigInt("747214317243172437126");
		b = UnsignedBigInt("747214317243172437126");
		c = a - b;
		ASSERT_EQ("0", c.toString());

	}

	#pragma endregion

	#pragma region Multiplications

	TEST_F(UnsignedBigIntTest, Multiplications) {

		UnsignedBigInt a, b, c;

		a = UnsignedBigInt("24729560249562456409874450");
		ASSERT_EQ((a+a).toString(), (a * 2).toString());

		a = UnsignedBigInt("24729560249562456409874450");
		ASSERT_EQ("335431755225065158743537039800", (a * 13564).toString());

		a = UnsignedBigInt("24729560249562456409874450");
		ASSERT_EQ("609230695138272545563067054475150", (a * 24635727).toString());

		a = UnsignedBigInt("24729560249562456409874450");
		b = UnsignedBigInt("1465175465341265345612");
		ASSERT_EQ("36233144946337530042279736528864738908778413400", (a * b).toString());

		a = UnsignedBigInt("1745918347510738461398467013641034601346717386413846138764");
		b = UnsignedBigInt("71654715471634517635471364571364571141314314134314314");
		ASSERT_EQ("125103282427588281550192056577169443769029849466081089451295466250281217549479829973992739353032132125635467896", (a * b).toString());

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
		ASSERT_EQ("20000000000000000000000000000", (a / b).toString());

		a = UnsignedBigInt("220000000000222");
		b = UnsignedBigInt("2");
		ASSERT_EQ("110000000000111", (a / b).toString());

		a = UnsignedBigInt("47562497562947562947650245792");
		b = UnsignedBigInt("247295602495624564");
		ASSERT_EQ("192330543216", (a / b).toString());

		a = UnsignedBigInt("236135716361436519856974811659278549273845691284519254912345");
		b = UnsignedBigInt("983475693482652938765924387652938756");
		ASSERT_EQ("240103256162071692058670", (a / b).toString());

		a = UnsignedBigInt(	"236135716361436519856974811659278549273845691284519254912345"
							"236135716361436519856974811659278549273845691284519254912345"
							"236135716361436519856974811659278549273845691284519254912345"
							"236135716361436519856974811659278549273845691284519254912345"
							"236135716361436519856974811659278549273845691284519254912345"
							"236135716361436519856974811659278549273845691284519254912345"
							"236135716361436519856974811659278549273845691284519254912345"
							"236135716361436519856974811659278549273845691284519254912345" );

		b = UnsignedBigInt("983475693482652938765924387652938756");

		ASSERT_EQ("2401032561620716920586702958515504539548019245730252129136795226451"
					 "5720740626968741500207014010579384821294206662285869439432072274300"
					 "3340031091055871693721551638876232004112082485593799743553306079770"
					 "2172089677605907309441625820925742356813440007167030230362449086997"
					 "8024465691925330867165122238232793592290046490240917478900885360319"
					 "6797114383075735543112573037512692598935077866488150983847250256197"
					 "174619108635589722306059668648186616213097", (a / b).toString());

	}

	#pragma endregion

	#pragma region Remainders

	TEST_F(UnsignedBigIntTest, Remainder) {

		UnsignedBigInt a, b, c;

		a = UnsignedBigInt("10000000000000000000000000000000000000000000000000000011111");
		b = UnsignedBigInt("500000000000000000000000000000");
		ASSERT_EQ("11111", (a % b).toString());

		a = UnsignedBigInt("47562497562947562947650245792");
		b = UnsignedBigInt("247295602495624564");
		ASSERT_EQ("36085290337087968", (a % b).toString());

		a = UnsignedBigInt("236135716361436519856974811659278549273845691284519254912345");
		b = UnsignedBigInt("983475693482652938765924387652938756");
		ASSERT_EQ("290962808750621283678503626186097825", (a % b).toString());

	}	

	#pragma endregion

	#pragma region Increment / Decrement

	TEST_F(UnsignedBigIntTest, IncrementDecrement) {

		UnsignedBigInt a = UnsignedBigInt("8375639165791754013759651937651937651937659");
		ASSERT_EQ("8375639165791754013759651937651937651937660", (++a).toString());
		a--;
		ASSERT_EQ("8375639165791754013759651937651937651937659", a.toString());
		ASSERT_EQ("8375639165791754013759651937651937651937659", (a++).toString());
		ASSERT_EQ("8375639165791754013759651937651937651937660", a.toString());

	}

	#pragma endregion

	#pragma region Shifting

	TEST_F(UnsignedBigIntTest, Shifting) {

		int places = 23;
		UnsignedBigInt a, b;
		b = pow(UnsignedBigInt(2), UnsignedBigInt(places));
		a = UnsignedBigInt("83164513654178581346831");
		ASSERT_EQ((a * b).toString(), (a << places).toString());
		ASSERT_EQ((a / b).toString(), (a >> places).toString());

		places = 56;
		b = pow(UnsignedBigInt(2), UnsignedBigInt(places));
		a = UnsignedBigInt("83164513654178581346831");
		ASSERT_EQ((a * b).toString(), (a << places).toString());
		ASSERT_EQ((a / b).toString(), (a >> places).toString());

		places = -121;
		ASSERT_THROW((a >> places).toString(), NegativeShiftException);

	}
	
	#pragma endregion

	#pragma region Bitwise

	TEST_F(UnsignedBigIntTest, Bitwise) {
	
#ifdef BIGINT_PSEUDO_DECIMAL_BASE

		// this is not done with binary base because I should rewrite test case
		// (internal representation changes)

		UnsignedBigInt a, b;

		//83164513654178581346831
		//0x000144dc 0x1e9dbda2 0x22a6a60f
		//00000000000000010100010011011100 00011110100111011011110110100010 00100010101001101010011000001111
		a = UnsignedBigInt("83164513654178581346831");

		//83164494987948267926831
		//0x000144dc 0x1d80eaac 0x0ff83d2f 
		//00000000000000010100010011011100 00011101100000001110101010101100 00001111111110000011110100101111
		b = UnsignedBigInt("83164494987948267926831");

		//83164478193824044049423
		//0x000144dc 0x1c80a8a0 0x02a0240f
		//00000000000000010100010011011100 00011101100000001110101010101100 00001111111110000011110100101111
		//00000000000000010100010011011100 00011110100111011011110110100010 00100010101001101010011000001111
		//00000000000000010100010011011100 00011100100000001010100010100000 00000010101000000010010000001111
		ASSERT_EQ((a & b).toString(), "83164478193824044049423");

		//83164530448302805224239
		//0x000144dc 0x1f9dffae 0x2ffebf2f
		//00000000000000010100010011011100 00011101100000001110101010101100 00001111111110000011110100101111
		//00000000000000010100010011011100 00011110100111011011110110100010 00100010101001101010011000001111
		//00000000000000010100010011011100 00011111100111011111111110101110 00101111111111101011111100101111
		ASSERT_EQ((a | b).toString(), "83164530448302805224239");

		//52254478761174816
		//0x00000000 0x031d570e 0x2d5e9b20
		//00000000000000010100010011011100 00011101100000001110101010101100 00001111111110000011110100101111
		//00000000000000010100010011011100 00011110100111011011110110100010 00100010101001101010011000001111
		//00000000000000000000000000000000 00000011000111010101011100001110 00101101010111101001101100100000
		ASSERT_EQ((a ^ b).toString(), "52254478761174816");

		//429488413137813131173713620464
		//0xfffebb23 0xe162425d 0xdd5959f0
		//00000000000000010100010011011100 00011110100111011011110110100010 00100010101001101010011000001111
		//11111111111111101011101100100011 11100001011000100100001001011101 11011101010110010101100111110000
		ASSERT_EQ((~a).toString(), "429488413137813131173713620464");

#endif

	}

	#pragma endregion

	#pragma region Exponentation

	TEST_F(UnsignedBigIntTest, Exponentation) {

		UnsignedBigInt a, b, c;

		a = UnsignedBigInt("214518345");
		b = UnsignedBigInt("4");
		c = pow(a,b);

		ASSERT_EQ("2117667399768367790914905597950625", c.toString());

#ifdef BIGINT_PSEUDO_DECIMAL_BASE

		// this is not done with binary base because outputting the huge number with the
		// base conversion toString method would take too long (about 10 minutes on my 3Ghz Dual-Core)

		a = UnsignedBigInt("214124124431412132545");
		b = UnsignedBigInt("1840");
		c= pow(a,b); // lol, 36,5Kb. We do what we must because we can!

		std::ifstream t("..\\214124124431412132545^1840.txt");
		std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

		// if this fails it probably means the file with the result hasn't been loaded properly
		ASSERT_TRUE(str.size()>0);

		// using strcmp here because gtest fixture buffer seems not large enough to compare these
		int comparison = std::strcmp(str.c_str(), c.toString().c_str());
		ASSERT_EQ(comparison, 0);

#endif

	}

	#pragma endregion

	#pragma region Summary

	TEST_F(UnsignedBigIntTest, Summary) {

		UnsignedBigInt a, b;

		a = UnsignedBigInt("378653928745683274965203947576220398652039568703945623098745692385"
						   "692387456932876592873456293875469283756938745692387456923874525252");
		b = a + a;
		ASSERT_EQ((b / 2).toString(), a.toString());
		ASSERT_EQ((pow(b,2)).toString(), (a * a * 4).toString());
		ASSERT_EQ((b * b - a).toString(), ((a * a * 4) - a).toString());

		b = a * a * a;
		ASSERT_EQ(pow(a,3).toString(), b.toString());

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
		ASSERT_EQ("184518345183764381746", out.str());
		ss >> a;
		ASSERT_TRUE(ss.fail());

	}

	#pragma endregion

	class BigIntTest : public ::testing::Test {};

	#pragma region Integer constructors

	TEST_F(BigIntTest, IntegerConstructors) {

		BigInt a;

		a = -4;
		ASSERT_EQ("-4", a.toString());

		a = 12345;
		ASSERT_EQ("12345", a.toString());

		a = -42949672;
		ASSERT_EQ("-42949672", a.toString());

		a = 441243123294967295;
		ASSERT_EQ("441243123294967295", a.toString());

	}

	#pragma endregion

	#pragma region String constructors

	TEST_F(BigIntTest, StringConstructors) {

		BigInt a;
		ASSERT_THROW(a = BigInt("WAT?"), BadStringInitializationException);
		ASSERT_THROW(a = BigInt("00-000-0"), BadStringInitializationException);

		a = BigInt("   00000000 ");
		ASSERT_EQ("0", a.toString());

		a = BigInt("-47562497562947562947650245792     ");
		ASSERT_EQ("-47562497562947562947650245792", a.toString());

		a = BigInt("   +  657465327280000000000000000000000245             ");
		ASSERT_EQ("657465327280000000000000000000000245", a.toString());

		a = BigInt("00000000000010000000011111111000000000000000000000100000000011111111");
		ASSERT_EQ("10000000011111111000000000000000000000100000000011111111", a.toString());

	}

	#pragma endregion

	#pragma region Comparison

	TEST_F(BigIntTest, Comparison) {

		BigInt a, b;
		a = BigInt("-62497562947562947650245791");
		b = BigInt("47562497562947562947650245792");
		ASSERT_TRUE(a < b);
		ASSERT_TRUE(a != b);
		ASSERT_TRUE(b > a);
		ASSERT_FALSE(b > b);
		ASSERT_FALSE(b != b);

		a = BigInt("-47562497562947562947650245792");
		b = BigInt("47562497562947562947650245792");
		ASSERT_TRUE(a < b);
		ASSERT_TRUE(a != b);
		ASSERT_TRUE(b > a);

		a = BigInt("-47562497562947562947650245792");
		b = BigInt("-475624975629475629476502457926857");
		ASSERT_TRUE(a > b);
		ASSERT_TRUE(a != b);
		ASSERT_TRUE(b < a);

		a = BigInt("-29465429765154625427428736298750983567364537654286498479402989765564526565265466");
		b = BigInt("-29465429765154625427428736298750983567364537654286498479402989765564526565265466");
		ASSERT_TRUE(a == b);
		ASSERT_TRUE(a <= b);
		ASSERT_TRUE(a >= b);
		ASSERT_FALSE(a > b);
		ASSERT_FALSE(b < a);

	}

	#pragma endregion

	#pragma region Additions

	TEST_F(BigIntTest, Additions) {

		BigInt a, b, c;
		a = BigInt("-1");
		b = BigInt("-2");
		c = a + b;
		ASSERT_EQ("-3", c.toString());

		a = BigInt("-8375639165791754013759651937651937651937659");
		b = BigInt("747214317243172437125");
		c = a + b;
		ASSERT_EQ("-8375639165791754013758904723334694479500534", c.toString());

		a = BigInt("72456128765412865184556316565331561365183658675015640194857109547601956130749");
		b = BigInt("-154817245182745182549124591287462198456354127964531876541872458127654712");
		a += b;
		ASSERT_EQ("72455973948167682439373767440740273902985202320887675662980567675143828476037", a.toString());

		a = BigInt("-747214317243172437126");
		b = BigInt("747214317243172437125");
		c = a + b;
		ASSERT_EQ("-1", c.toString());

		a = BigInt("747214317243172437126");
		b = BigInt("-747214317243172437126");
		c = a + b;
		ASSERT_EQ("0", c.toString());

	}

	#pragma endregion

	#pragma region Subtractions

	TEST_F(BigIntTest, Subtractions) {

		BigInt a, b, c;
		a = BigInt("1");
		b = BigInt("2");
		c = a - b;
		ASSERT_EQ("-1", c.toString());

		a = BigInt("-8375639165791754013759651937651937651937659");
		b = BigInt("-747214317243172437125");
		c = a - b;
		ASSERT_EQ("-8375639165791754013758904723334694479500534", c.toString());

		a = BigInt("72456128765412865184556316565331561365183658675015640194857109547601956130749");
		b = BigInt("154817245182745182549124591287462198456354127964531876541872458127654712");
		a -= b;
		ASSERT_EQ("72455973948167682439373767440740273902985202320887675662980567675143828476037", a.toString());

		a = BigInt("-47562497563194858550145870356");
		b = BigInt("-47562497562947562947650245792");
		c = a - b;
		ASSERT_EQ("-247295602495624564", c.toString());

		a = BigInt("29465429765154625427428736298750983567364537654286498479402989765564526565265466");
		b = BigInt("78652846526572987549028759875928462846584276548276582476584726584725682745684276");
		c = BigInt("108118276291727612976457496174679446413948814202563080955987716350290209310949742");
		c -= a;
		c -= b;
		ASSERT_EQ("0", c.toString());

	}

	#pragma endregion

	#pragma region Multiplications

	TEST_F(BigIntTest, Multiplications) {

		BigInt a, b, c;

		a = BigInt("-24729560249562456409874450");
		ASSERT_EQ((a+a).toString(), (a * 2).toString());

		a = BigInt("24729560249562456409874450");
		ASSERT_EQ("-335431755225065158743537039800", (a * -13564).toString());

		a = BigInt("-24729560249562456409874450");
		ASSERT_EQ("609230695138272545563067054475150", (a * -24635727).toString());

		a = BigInt("24729560249562456409874450");
		b = BigInt("1465175465341265345612");
		ASSERT_EQ("36233144946337530042279736528864738908778413400", (a * b).toString());

		a = BigInt("-1745918347510738461398467013641034601346717386413846138764");
		b = BigInt("71654715471634517635471364571364571141314314134314314");
		ASSERT_EQ("-125103282427588281550192056577169443769029849466081089451295466250281217549479829973992739353032132125635467896", (a * b).toString());

	}

	#pragma endregion

	#pragma region Divisions
	
	TEST_F(BigIntTest, Divisions) {

		BigInt a, b, c;

		a = BigInt("-10002893652093475029347699500345000015858500009475000011111");
		b = BigInt("-0000");
		ASSERT_THROW(a / b, DivideByZeroException);

		a = BigInt("10000000000000000000000000000000000000000000000000000011111");
		b = BigInt("-500000000000000000000000000000");
		ASSERT_EQ("-20000000000000000000000000000", (a / b).toString());

		a = BigInt("-220000000000222");
		b = BigInt("2");
		ASSERT_EQ("-110000000000111", (a / b).toString());

		a = BigInt("-47562497562947562947650245792");
		b = BigInt("-247295602495624564");
		ASSERT_EQ("192330543216", (a / b).toString());

		a = BigInt("236135716361436519856974811659278549273845691284519254912345");
		b = BigInt("983475693482652938765924387652938756");
		ASSERT_EQ("240103256162071692058670", (a / b).toString());

		a = BigInt(	"236135716361436519856974811659278549273845691284519254912345"
							"236135716361436519856974811659278549273845691284519254912345"
							"236135716361436519856974811659278549273845691284519254912345"
							"236135716361436519856974811659278549273845691284519254912345"
							"236135716361436519856974811659278549273845691284519254912345"
							"236135716361436519856974811659278549273845691284519254912345"
							"236135716361436519856974811659278549273845691284519254912345"
							"236135716361436519856974811659278549273845691284519254912345" );

		b = BigInt("-983475693482652938765924387652938756");

		ASSERT_EQ("-2401032561620716920586702958515504539548019245730252129136795226451"
					 "5720740626968741500207014010579384821294206662285869439432072274300"
					 "3340031091055871693721551638876232004112082485593799743553306079770"
					 "2172089677605907309441625820925742356813440007167030230362449086997"
					 "8024465691925330867165122238232793592290046490240917478900885360319"
					 "6797114383075735543112573037512692598935077866488150983847250256197"
					 "174619108635589722306059668648186616213097", (a / b).toString());

	}

	#pragma endregion

	#pragma region Remainders

	TEST_F(BigIntTest, Remainder) {

		BigInt a, b, c;

		a = BigInt("-10000000000000000000000000000000000000000000000000000011111");
		b = BigInt("500000000000000000000000000000");
		ASSERT_EQ("-11111", (a % b).toString());

		a = BigInt("47562497562947562947650245792");
		b = BigInt("-247295602495624564");
		ASSERT_EQ("36085290337087968", (a % b).toString());

		a = BigInt("-236135716361436519856974811659278549273845691284519254912345");
		b = BigInt("-983475693482652938765924387652938756");
		ASSERT_EQ("-290962808750621283678503626186097825", (a % b).toString());

	}	

	#pragma endregion

	#pragma region Increment / Decrement, unary sign

	TEST_F(BigIntTest, IncrementDecrement) {

		BigInt a = BigInt("-8375639165791754013759651937651937651937660");
		ASSERT_EQ("-8375639165791754013759651937651937651937659", (++a).toString());
		a--;
		ASSERT_EQ("-8375639165791754013759651937651937651937660", a.toString());
		ASSERT_EQ("8375639165791754013759651937651937651937660", (-(a++)).toString());
		ASSERT_EQ("8375639165791754013759651937651937651937659", (-a).toString());

		a = BigInt("-3");
		ASSERT_EQ("-2", (++a).toString());
		ASSERT_EQ("-1", (++a).toString());
		ASSERT_EQ("0", (++a).toString());
		ASSERT_EQ("1", (++a).toString());
		ASSERT_EQ("1", (a++).toString());
		ASSERT_EQ("2", (a).toString());
		ASSERT_EQ("1", (--a).toString());
		ASSERT_EQ("0", (--a).toString());
		ASSERT_EQ("0", (a--).toString());
		ASSERT_EQ("-2", (--a).toString());
		ASSERT_EQ("2", (-a).toString());

	}

	#pragma endregion

	#pragma region Shifting

	TEST_F(BigIntTest, Shifting) {

		int places = 23;
		BigInt a;
		UnsignedBigInt b;
		b = pow(UnsignedBigInt(2), UnsignedBigInt(places));

		a = BigInt("-83164513654178581346831");
		ASSERT_EQ((a * b).toString(), (a << places).toString());
		ASSERT_EQ((a / b).toString(), (a >> places).toString());

	}
	
	#pragma endregion

	#pragma region Bitwise

	TEST_F(BigIntTest, Bitwise) {
	
#ifdef BIGINT_PSEUDO_DECIMAL_BASE

		// this is not done with binary base because I should rewrite test case
		// (internal representation changes)

		BigInt a, b;

		a = 1;
		b = -11;

		// These are just to test the signs, hardcore tests have already been done on UnsignedBigInt
		ASSERT_EQ((a & b).toString(), "-1");
		ASSERT_EQ((a | b).toString(), "11");
		ASSERT_EQ((a ^ b).toString(), "10");
		ASSERT_EQ((~a).toString(), "-4294967294");

#endif

	}
	
	#pragma endregion

	#pragma region Exponentation

	TEST_F(BigIntTest, Exponentation) {

		BigInt a, c, d;
		UnsignedBigInt b;

		a = -214518345;
		b = 4;
		c = pow(a,b);
		ASSERT_EQ("2117667399768367790914905597950625", c.toString());

		a = 214518345;
		b = 4;
		c = pow(a,b);
		ASSERT_EQ("2117667399768367790914905597950625", c.toString());

		a = -214518345;
		b = 3;
		c = pow(a,b);
		d = a * a * a;
		ASSERT_EQ(d.toString(), c.toString());

	}

	#pragma endregion

}  // namespace

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

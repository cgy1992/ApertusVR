#include "pch.h"
#include "gtest/gtest.h"
#include "../../include/apeColor.h"

TEST(ColorClass, Default_Constructor) {
	ape::Color col;

	EXPECT_EQ("Color(0, 0, 0, 1)", col.toString());
	EXPECT_EQ("{ \"r\": 0, \"g\": 0, \"b\": 0, \"a\": 1 }", col.toJsonString());
	EXPECT_EQ(0, col.getR());
	EXPECT_EQ(0, col.getG());
	EXPECT_EQ(0, col.getB());
	EXPECT_EQ(1, col.getA());
}

TEST(ColorClass, Constructor) {
	ape::Color col(1, 2, 3, 4);

	EXPECT_EQ("Color(1, 2, 3, 4)", col.toString());
	EXPECT_EQ("{ \"r\": 1, \"g\": 2, \"b\": 3, \"a\": 4 }", col.toJsonString());
	EXPECT_EQ(1, col.getR());
	EXPECT_EQ(2, col.getG());
	EXPECT_EQ(3, col.getB());
	EXPECT_EQ(4, col.getA());
}

TEST(ColorClass, File_Writing_Reading) {
	ape::Color col1(1, 2, 3, 4);
	ape::Color col2;

	std::ofstream writeFile1("output.txt");
	col1.write(writeFile1, false);

	writeFile1.close();

	std::ifstream readFile1("output.txt");
	col2.read(readFile1);

	EXPECT_EQ(1, col2.getR());
	EXPECT_EQ(2, col2.getG());
	EXPECT_EQ(3, col2.getB());
	EXPECT_EQ(4, col2.getA());

	readFile1.close();



	ape::Color col3(1, 2, 3, 4);
	ape::Color col4;

	std::ofstream writeFile2("output.txt");
	col3.write(writeFile2);
	writeFile2.close();

	std::ifstream readFile2("output.txt");
	long sizeInBytes = 16;
	readFile2.read(reinterpret_cast<char*>(&sizeInBytes), sizeof(long));
	col4.read(readFile2);

	EXPECT_EQ(1, col4.getR());
	EXPECT_EQ(2, col4.getG());
	EXPECT_EQ(3, col4.getB());
	EXPECT_EQ(4, col4.getA());

	readFile2.close();



}

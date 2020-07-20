#include "pch.h"
#include "gtest/gtest.h"
#include "../../include/apeVector4.h"

TEST(Vector4Class, Default_Constructor) {
	ape::Vector4 vec;

	EXPECT_EQ(0.0f, vec.getX());
	EXPECT_EQ(0.0f, vec.getY());
	EXPECT_EQ(0.0f, vec.getZ());
	EXPECT_EQ(0.0f, vec.getW());
	vec.x = 2;
	vec.y = 3;
	vec.z = 4;
	EXPECT_EQ(2.0f, vec.getX());
	EXPECT_EQ(3.0f, vec.getY());
	EXPECT_EQ(4.0f, vec.getZ());
}

TEST(Vector4Class, Constructors) {
	ape::Vector4 vec(2, 3, 4, 5);

	EXPECT_EQ(2.0f, vec.getX());
	EXPECT_EQ(3.0f, vec.getY());
	EXPECT_EQ(4.0f, vec.getZ());
	EXPECT_EQ(5.0f, vec.getW());
}

TEST(Vector4Class, Functions) {
	ape::Vector4 vec(2, 3, 4, 5);

	EXPECT_EQ("2, 3, 4, 5\n", vec.toString());
	EXPECT_EQ("{ \"x\": 2, \"y\": 3, \"z\": 4, \"w\": 5 }", vec.toJsonString());

	std::vector<float> myVec{ 2,3,4,5 };
	EXPECT_EQ(myVec, vec.toVector());
}
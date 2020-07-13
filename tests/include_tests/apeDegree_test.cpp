#include "pch.h"
#include "gtest/gtest.h"
#include "../../include/apeDegree.h"

TEST(DegreeClass, Default_Constructor) {
	ape::Degree deg;
	float zer = 0;

	EXPECT_EQ(zer, deg.getDegree());
	EXPECT_EQ(zer, deg.toRadian());
}

TEST(DegreeClass, Constructor) {
	ape::Degree deg(90);
	float x = 90;

	EXPECT_EQ(x, deg.getDegree());
	EXPECT_EQ(float(0.5*ape_PI), deg.toRadian());

	ape::Degree deg2(137);
	x = 137;

	EXPECT_EQ(x, deg2.getDegree());
	EXPECT_EQ(float(137 * ape_PI / 180), deg2.toRadian());

	ape::Degree deg3(180);
	x = 180;

	EXPECT_EQ(x, deg3.getDegree());
	EXPECT_EQ(float(ape_PI), deg3.toRadian());

	ape::Degree deg4(360);
	x = 360;

	EXPECT_EQ(x, deg4.getDegree());
	EXPECT_EQ(float(2*ape_PI), deg4.toRadian());
}
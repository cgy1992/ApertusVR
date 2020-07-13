#include "pch.h"
#include "gtest/gtest.h"
#include "../../include/apeRadian.h"

TEST(RadianClass, Default_Constructor) {
	ape::Radian rad;

	EXPECT_EQ(0, rad.getRadian());
	EXPECT_EQ(0, rad.toDegree());
}

TEST(RadianClass, Constructor) {
	ape::Radian rad(1);

	EXPECT_EQ(1, rad.getRadian());
	EXPECT_EQ(float(180/ape_PI), rad.toDegree());

	ape::Radian rad2(ape_PI);

	EXPECT_EQ(float(ape_PI), rad2.getRadian());
	EXPECT_EQ(float(180), rad2.toDegree());
}

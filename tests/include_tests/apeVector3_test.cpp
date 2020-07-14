#include "pch.h"
#include "gtest/gtest.h"
#include "../../include/apeVector3.h"

TEST(Vector3Class, Default_Constructor) {
	ape::Vector3 vec;

	EXPECT_EQ(0.0f, vec.getX());
	EXPECT_EQ(0.0f, vec.getY());
	EXPECT_EQ(0.0f, vec.getZ());
	vec.x = 2;
	vec.y = 3;
	vec.z = 4;
	EXPECT_EQ(2.0f, vec.getX());
	EXPECT_EQ(3.0f, vec.getY());
	EXPECT_EQ(4.0f, vec.getZ());
}

TEST(Vector3Class, Constructors) {
	ape::Vector3 vec(2,3,4);

	EXPECT_EQ(2.0f, vec.getX());
	EXPECT_EQ(3.0f, vec.getY());
	EXPECT_EQ(4.0f, vec.getZ());

	ape::Vector3 vec2(5);

	EXPECT_EQ(5.0f, vec2.getX());
	EXPECT_EQ(5.0f, vec2.getY());
	EXPECT_EQ(5.0f, vec2.getZ());
}

TEST(Vector3Class, Distance_functions) {
	ape::Vector3 vec(2, 3, 4);
	float sqLenght = 2*2 + 3*3 + 4*4;
	EXPECT_EQ(sqLenght, vec.squaredLength());

	float length = sqrt(sqLenght);
	EXPECT_EQ(length, vec.length());

	ape::Vector3 vec2(2, 3, 4);
	EXPECT_EQ(0.0f, vec.distance(vec2));

	ape::Vector3 vec3;
	EXPECT_EQ(0.0f, vec3.squaredLength());

	EXPECT_EQ(0.0f, vec3.length());

	EXPECT_EQ(length, vec3.distance(vec));

	ape::Vector3 vec4(-5);
	sqLenght = 3 * (-5 * -5);
	length = sqrt(sqLenght);
	EXPECT_EQ(sqLenght, vec4.squaredLength());
	EXPECT_EQ(length, vec4.length());
}

TEST(Vector3Class, Products) {
	ape::Vector3 vec(2, 3, 4);
	ape::Vector3 vec2(0);
	EXPECT_EQ(0.0f, vec.crossProduct(vec2).getX());
	EXPECT_EQ(0.0f, vec.crossProduct(vec2).getY());
	EXPECT_EQ(0.0f, vec.crossProduct(vec2).getZ());

	ape::Vector3 vec3(1);
	EXPECT_EQ(float(3*1-4*1), vec.crossProduct(vec3).getX());
	EXPECT_EQ(float(4 * 1 - 2 * 1), vec.crossProduct(vec3).getY());
	EXPECT_EQ(float(2 * 1 - 3 * 1), vec.crossProduct(vec3).getZ());

	EXPECT_EQ(float(4 * 1 - 3 * 1), vec3.crossProduct(vec).getX());
	EXPECT_EQ(float(2 * 1 - 4 * 1), vec3.crossProduct(vec).getY());
	EXPECT_EQ(float(3 * 1 - 2 * 1), vec3.crossProduct(vec).getZ());
	EXPECT_EQ(0.0f, vec.dotProduct(vec2));
	EXPECT_EQ(float(2+3+4), vec.dotProduct(vec3));

}

TEST(Vector3Class, Operators) {
	ape::Vector3 vec(2, 3, 4);
	ape::Vector3 vec2(0);
	ape::Vector3 vec3(2);
	vec2 = vec3;
	EXPECT_EQ(2.0f, vec2.getX());
	EXPECT_EQ(2.0f, vec2.getY());
	EXPECT_EQ(2.0f, vec2.getZ());
	vec2 = 0.0f;
	EXPECT_EQ(0.0f, vec2.getX());
	EXPECT_EQ(0.0f, vec2.getY());
	EXPECT_EQ(0.0f, vec2.getZ());
	EXPECT_TRUE(vec2 < vec3);
	EXPECT_TRUE(vec3 > vec2);

	EXPECT_TRUE(vec2 < vec);
	EXPECT_FALSE(vec2 > vec);

	EXPECT_FALSE(vec3 < vec);
	EXPECT_FALSE(vec3 > vec);

	EXPECT_FALSE(vec3.equalTo(vec));
	EXPECT_FALSE(vec2.equalTo(vec));
	EXPECT_FALSE(vec3.equalTo(vec2));
	vec2 = 2.0f;
	EXPECT_TRUE(vec3.equalTo(vec2));
	vec2 = 0.0f;


	EXPECT_TRUE(vec3 != vec);
	EXPECT_TRUE(vec2 != vec);
	EXPECT_TRUE(vec3 != vec2);
	vec2 = 2.0f;
	EXPECT_FALSE(vec3 != vec2);
	vec2 = 0.0f;

	EXPECT_FALSE(vec3== vec);
	EXPECT_FALSE(vec2==vec);
	EXPECT_FALSE(vec3==vec2);
	vec2 = 2.0f;
	EXPECT_TRUE(vec3==vec2);
}
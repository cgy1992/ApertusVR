#include "pch.h"
#include "gtest/gtest.h"
#include "math.h"
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

TEST(Vector3Class, Operators1) {
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

TEST(Vector3Class, Operators2) {
	ape::Vector3 vec(2, 3, 4);
	ape::Vector3 vec2(1);
	ape::Vector3 vec3(2);
	ape::Vector3 vec4;

	
	EXPECT_FALSE(vec2 == vec3);
	EXPECT_TRUE(vec2 * 2 == vec3);

	EXPECT_TRUE(vec2 < vec);
	EXPECT_FALSE(vec2*2 < vec);

	EXPECT_TRUE(vec4 < vec);
	EXPECT_TRUE(vec4 * 10 < vec);


	EXPECT_FALSE(vec2 == vec3);
	EXPECT_TRUE(vec2 == vec3 / 2);

	EXPECT_TRUE(vec2 < vec);
	EXPECT_FALSE(vec2 < vec/2);

	EXPECT_TRUE(vec4 < vec);
	EXPECT_TRUE(vec4 < vec / 10);

	vec4 = 4.0f;
	EXPECT_TRUE(vec4 / 2 == vec2*2);
	vec4 = 0.0f;

	EXPECT_EQ(INFINITY, (vec/ vec4).getX());
	EXPECT_EQ(INFINITY, (vec / vec4).getY());
	EXPECT_EQ(INFINITY, (vec / vec4).getZ());

	vec4 = 4.0f;
	EXPECT_ANY_THROW(vec4 / 0.0f);

	vec4 = 0.0f;
	EXPECT_ANY_THROW(vec4 / 0.0f);

	vec4 = 0.0f;
	EXPECT_TRUE(vec4 == vec * vec2 * vec3 * vec4);
	EXPECT_TRUE(vec3 == vec2 * vec3);
	EXPECT_EQ(4.0f, (vec*vec3).getX());
	EXPECT_EQ(6.0f, (vec*vec3).getY());
	EXPECT_EQ(8.0f, (vec*vec3).getZ());

	EXPECT_TRUE(vec2 + vec2 == vec3);
	EXPECT_TRUE(vec3 - vec2 == vec2);

	EXPECT_EQ(3.0f, (vec2 + vec).getX());
	EXPECT_EQ(4.0f, (vec2 + vec).getY());
	EXPECT_EQ(5.0f, (vec2 + vec).getZ());

	EXPECT_EQ(0.0f, (vec3 - vec).getX());
	EXPECT_EQ(-1.0f, (vec3 - vec).getY());
	EXPECT_EQ(-2.0f, (vec3 - vec).getZ());

	EXPECT_EQ(-2.0f, (- vec).getX());
	EXPECT_EQ(-3.0f, (- vec).getY());
	EXPECT_EQ(-4.0f, (- vec).getZ());

	vec2 += vec;
	EXPECT_EQ(3.0f, vec2.getX());
	EXPECT_EQ(4.0f, vec2.getY());
	EXPECT_EQ(5.0f, vec2.getZ());

	vec3 -= vec;
	EXPECT_EQ(0.0f, vec3.getX());
	EXPECT_EQ(-1.0f, vec3.getY());
	EXPECT_EQ(-2.0f, vec3.getZ());
}

TEST(Vector3Class, Functions) {
	ape::Vector3 vec(2, 3, 4);
	ape::Vector3 vec2(1);
	ape::Vector3 vec3(2);
	ape::Vector3 vec4;
	float myLength = 1.0f / vec.length();
	EXPECT_EQ(1.0f/myLength, vec.normalise());
	EXPECT_EQ(float(2.0f * myLength), vec.getX());
	EXPECT_EQ(float(3.0f * myLength), vec.getY());
	EXPECT_EQ(float(4.0f * myLength), vec.getZ());

	ape::Vector3 vec1(2, 3, 4);

	EXPECT_EQ("2, 3, 4", vec1.toString());
	EXPECT_EQ("{ \"x\": 2, \"y\": 3, \"z\": 4 }", vec1.toJsonString());

	std::vector<float> stdVec{ 2.0f,3.0f,4.0f };
	EXPECT_EQ(stdVec[0], vec1.toVector()[0]);
	EXPECT_EQ(stdVec[1], vec1.toVector()[1]);
	EXPECT_EQ(stdVec[2], vec1.toVector()[2]);
}
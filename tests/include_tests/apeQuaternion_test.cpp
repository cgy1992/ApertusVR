#include "pch.h"
#include "gtest/gtest.h"
#include "../../include/apeQuaternion.h"

TEST(QuaternionClass, Default_Constructor) {
	ape::Quaternion quat;

	EXPECT_FLOAT_EQ(1.0f, quat.getW());
	EXPECT_FLOAT_EQ(0.0f, quat.getX());
	EXPECT_FLOAT_EQ(0.0f, quat.getY());
	EXPECT_FLOAT_EQ(0.0f, quat.getZ());
	EXPECT_EQ("1, 0, 0, 0", quat.toString());
	EXPECT_EQ("{ \"w\": 1, \"x\": 0, \"y\": 0, \"z\": 0 }", quat.toJsonString());
	std::vector<float> vec{ 1,0,0,0 };
	std::vector<float> vec2 = quat.toVector();
	for (int i = 0; i < 4; i++) {
		EXPECT_FLOAT_EQ(vec[i], vec2[i]);
	}
}

TEST(QuaternionClass, Constructor_float) {
	ape::Quaternion quat(1,2,3,4);

	EXPECT_FLOAT_EQ(1.0f, quat.getW());
	EXPECT_FLOAT_EQ(2.0f, quat.getX());
	EXPECT_FLOAT_EQ(3.0f, quat.getY());
	EXPECT_FLOAT_EQ(4.0f, quat.getZ());
	EXPECT_EQ("1, 2, 3, 4", quat.toString());
	EXPECT_EQ("{ \"w\": 1, \"x\": 2, \"y\": 3, \"z\": 4 }", quat.toJsonString());
	std::vector<float> vec{ 1,2,3,4 };
	std::vector<float> vec2 = quat.toVector();
	for (int i = 0; i < 4; i++) {
		EXPECT_FLOAT_EQ(vec[i], vec2[i]);
	}
}

TEST(QuaternionClass, Constructor_degree) {
	ape::Vector3 vec(1, 2, 3);
	ape::Degree deg(90);
	ape::Quaternion quat(deg, vec);
	float mySin = std::sin(0.5*deg.toRadian());
	EXPECT_FLOAT_EQ(std::cos(0.5*deg.toRadian()), quat.getW());
	EXPECT_FLOAT_EQ(mySin, quat.getX());
	EXPECT_FLOAT_EQ(mySin*2, quat.getY());
	EXPECT_FLOAT_EQ(mySin*3, quat.getZ());
}

TEST(QuaternionClass, Constructor_radian) {
	ape::Vector3 vec(1, 2, 3);
	ape::Radian rad(0.5);
	ape::Quaternion quat(rad, vec);
	float mySin = std::sin(0.5*rad.radian);
	EXPECT_FLOAT_EQ(std::cos(0.5*rad.radian), quat.getW());
	EXPECT_FLOAT_EQ(mySin, quat.getX());
	EXPECT_FLOAT_EQ(mySin * 2, quat.getY());
	EXPECT_FLOAT_EQ(mySin * 3, quat.getZ());
}

TEST(QuaternionClass, Constructor_matrix) {
	ape::Matrix3 mat(1,0,0,0,1,0,0,0,1);
	ape::Quaternion quat(mat);
	EXPECT_FLOAT_EQ(1.0f, quat.getW());
	EXPECT_FLOAT_EQ(0.0f, quat.getX());
	EXPECT_FLOAT_EQ(0.0f, quat.getY());
	EXPECT_FLOAT_EQ(0.0f, quat.getZ());

	ape::Matrix3 mat2(-1, 0, 0, 0, -1, 0, 0, 0, -1);
	ape::Quaternion quat2(mat2);
	EXPECT_FLOAT_EQ(0.0f, quat2.getW());
	EXPECT_FLOAT_EQ(0.5*std::sqrt(2), quat2.getX());
	EXPECT_FLOAT_EQ(0.0f, quat2.getY());
	EXPECT_FLOAT_EQ(0.0f, quat2.getZ());

	ape::Matrix3 mat3(0,1,2,
					  3,4,5,
					  6,7,8);
	ape::Quaternion quat3(mat3);
	float root = std::sqrt(0 + 4 + 8 + 1);
	EXPECT_FLOAT_EQ(0.5*root, quat3.getW());
	root = 0.5 / root;
	EXPECT_FLOAT_EQ((7-5)*root, quat3.getX());
	EXPECT_FLOAT_EQ((2 - 6)*root, quat3.getY());
	EXPECT_FLOAT_EQ((3 - 1)*root, quat3.getZ());

	ape::Matrix3 mat4(-8, -7, -6,
					  -5, -4, -3,
					  -2, -1, 0);
	ape::Quaternion quat4(mat4);
	root = std::sqrt(0 - -8 - -4 + 1);
	EXPECT_FLOAT_EQ(0.5*root, quat4.getZ());
	root = 0.5 / root;
	EXPECT_FLOAT_EQ((-5 - -7)*root, quat4.getW());
	EXPECT_FLOAT_EQ((-6 + -2)*root, quat4.getX());
	EXPECT_FLOAT_EQ((-3 + -1)*root, quat4.getY());
	
}

TEST(QuaternionClass, Basic_Operators) {
	ape::Quaternion quat(1, 2, 3, 4);
	ape::Quaternion quat2;
	ape::Quaternion quat3(1, 2, 3, 4);
	EXPECT_FLOAT_EQ(2.0f, (quat+quat2).getW());
	EXPECT_FLOAT_EQ(2.0f, (quat+quat2).getX());
	EXPECT_FLOAT_EQ(3.0f, (quat+quat2).getY());
	EXPECT_FLOAT_EQ(4.0f, (quat+quat2).getZ());

	EXPECT_FLOAT_EQ(0.0f, (quat - quat2).getW());
	EXPECT_FLOAT_EQ(2.0f, (quat - quat2).getX());
	EXPECT_FLOAT_EQ(3.0f, (quat - quat2).getY());
	EXPECT_FLOAT_EQ(4.0f, (quat - quat2).getZ());

	EXPECT_FLOAT_EQ(0.0f, (quat2 - quat).getW());
	EXPECT_FLOAT_EQ(-2.0f, (quat2 - quat).getX());
	EXPECT_FLOAT_EQ(-3.0f, (quat2 - quat).getY());
	EXPECT_FLOAT_EQ(-4.0f, (quat2 - quat).getZ());
	
	quat = -quat;
	EXPECT_FLOAT_EQ(-1.0f, quat.getW());
	EXPECT_FLOAT_EQ(-2.0f, quat.getX());
	EXPECT_FLOAT_EQ(-3.0f, quat.getY());
	EXPECT_FLOAT_EQ(-4.0f, quat.getZ());

	quat = quat / -1;
	EXPECT_FLOAT_EQ(1.0f, quat.getW());
	EXPECT_FLOAT_EQ(2.0f, quat.getX());
	EXPECT_FLOAT_EQ(3.0f, quat.getY());
	EXPECT_FLOAT_EQ(4.0f, quat.getZ());

	quat = quat / 0;
	EXPECT_FLOAT_EQ(INFINITY, quat.getW());
	EXPECT_FLOAT_EQ(INFINITY, quat.getX());
	EXPECT_FLOAT_EQ(INFINITY, quat.getY());
	EXPECT_FLOAT_EQ(INFINITY, quat.getZ());

	EXPECT_TRUE(quat2 < quat);
	EXPECT_FALSE(quat < quat2);
	EXPECT_FALSE(quat3 < quat2);
	EXPECT_FALSE(quat3 > quat2);
}

TEST(QuaternionClass, Mutliplication_Operators) {
	ape::Quaternion quat(1, 2, 3, 4);
	ape::Quaternion quat2;
	ape::Vector3 vec(1, 2, 3);
	ape::Vector3 vec2 = quat * vec;

	ape::Vector3 vec3(2, 3, 4);
	ape::Vector3 res1 = vec3.crossProduct(vec);
	ape::Vector3 res2 = (vec3.crossProduct(res1))*2.0f;
	res1 = res1 * 2.0f;
	ape::Vector3 res3 = vec + res1 + res2;

	EXPECT_FLOAT_EQ(res3.getX(), vec2.getX());
	EXPECT_FLOAT_EQ(res3.getY(), vec2.getY());
	EXPECT_FLOAT_EQ(res3.getZ(), vec2.getZ());

	ape::Quaternion quat3 = quat * quat2;
	EXPECT_FLOAT_EQ(1.0f, quat3.getW());
	EXPECT_FLOAT_EQ(2.0f, quat3.getX());
	EXPECT_FLOAT_EQ(3.0f, quat3.getY());
	EXPECT_FLOAT_EQ(4.0f, quat3.getZ());

	ape::Quaternion quat4 = quat * quat;
	EXPECT_FLOAT_EQ(float(1*1-2*2-3*3-4*4), quat4.getW());
	EXPECT_FLOAT_EQ(float(1*2+2*1+3*4-4*3), quat4.getX());
	EXPECT_FLOAT_EQ(float(1*3+3*1+4*2-2*4), quat4.getY());
	EXPECT_FLOAT_EQ(float(1*4+4*1+2*3-3*2), quat4.getZ());
}

TEST(QuaternionClass, Funtcions) {
	ape::Quaternion quat(1, 2, 3, 4);
	ape::Quaternion quat2;
	ape::Quaternion quat3(1, 2, 3, 4);

	EXPECT_TRUE(quat.equals(quat3, 0));
	EXPECT_FALSE(quat.equals(quat2,0));

	EXPECT_FLOAT_EQ(float(1 + 4 + 9 + 16), quat.Norm());
	EXPECT_FLOAT_EQ(1.0f,quat2.Norm());
	EXPECT_FLOAT_EQ(float(1 + 4 + 9 + 16), quat.normalise());
	EXPECT_FLOAT_EQ(1.0f, quat2.normalise());

	EXPECT_FLOAT_EQ(1.0f, quat2.getW());
	EXPECT_FLOAT_EQ(0.0f, quat2.getX());
	EXPECT_FLOAT_EQ(0.0f, quat2.getY());
	EXPECT_FLOAT_EQ(0.0f, quat2.getZ());

	float divide = std::sqrt(1 + 4 + 9 + 16);
	EXPECT_FLOAT_EQ(1.0f/divide, quat.getW());
	EXPECT_FLOAT_EQ(2.0f/divide, quat.getX());
	EXPECT_FLOAT_EQ(3.0f/divide, quat.getY());
	EXPECT_FLOAT_EQ(4.0f/divide, quat.getZ());

	divide *= divide;
	quat3 = quat3.Inverse();
	EXPECT_FLOAT_EQ(1.0f / divide, quat3.getW());
	EXPECT_FLOAT_EQ(-2.0f / divide, quat3.getX());
	EXPECT_FLOAT_EQ(-3.0f / divide, quat3.getY());
	EXPECT_FLOAT_EQ(-4.0f / divide, quat3.getZ());

	ape::Quaternion quat4(0, 0, 0, 0);
	quat4.Inverse();
	EXPECT_FLOAT_EQ(0.0f, quat4.getW());
	EXPECT_FLOAT_EQ(0.0f, quat4.getX());
	EXPECT_FLOAT_EQ(0.0f, quat4.getY());
	EXPECT_FLOAT_EQ(0.0f, quat4.getZ());

	ape::Quaternion quat5(1, 2, 3, 4);
	ape::Quaternion quat6;
	EXPECT_FLOAT_EQ(1.0f, quat5.Dot(quat6));
	EXPECT_FLOAT_EQ(float(1+4+9+16), quat5.Dot(quat5));
}
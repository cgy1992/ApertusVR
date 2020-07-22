#include "pch.h"
#include "gtest/gtest.h"
#include "../../include/apeMatrix3.h"
#include "../../include/apeVector3.h"

TEST(Matrix3Class, Default_Constructor) {
	ape::Matrix3 mat;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			EXPECT_EQ(0.0f, mat[i][j]);
		}
	}
}
TEST(Matrix3Class, Constructor) {
	ape::Matrix3 mat(0,1,2,3,4,5,6,7,8);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			EXPECT_EQ(float(i*3+j), mat[i][j]);
		}
	}
}

TEST(Matrix3Class, Functions) {
	ape::Matrix3 mat1;
	ape::Matrix3 mat2(0, 1, 2, 3, 4, 5, 6, 7, 8);

	mat1.swap(mat2);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			EXPECT_EQ(float(i * 3 + j), mat1[i][j]);
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			EXPECT_EQ(0.0f, mat2[i][j]);
		}
	}

	mat1 = mat1.Transpose();
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			EXPECT_EQ(float(i * 3 + j), mat1[j][i]);
		}
	}

	ape::Matrix3 mat3(1, 0, 0, 0, 1, 0, 0, 0, 1);
	ape::Matrix3 mat4;
	EXPECT_FALSE(mat4.Inverse(mat4, 0.01f));
	EXPECT_TRUE(mat3.Inverse(mat4, 0.01f));
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if(i == j)
				EXPECT_EQ(1.0f, mat4[j][i]);
			else
				EXPECT_EQ(0.0f, mat4[j][i]);
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			mat4[i][j] = 0.0f;
		}
	}

	ape::Matrix3 result;
	result = mat4.Inverse(0.01f);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			EXPECT_EQ(0.0f, result[i][j]);
		}
	}

	result = mat3.Inverse(0.01f);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == j)
				EXPECT_EQ(1.0f, result[i][j]);
			else
				EXPECT_EQ(0.0f, result[i][j]);
		}
	}
	mat1[0][0] = 2.0f;
	result = mat1.Inverse(0.01f);
	result = result * mat1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == j) 
				EXPECT_EQ(1.0f, result[i][j]);	
			else
				EXPECT_EQ(0.0f, result[i][j]);
		}
	}

	EXPECT_EQ(-6.0f, mat1.Determinant());
	EXPECT_EQ(1.0f, mat3.Determinant());
}

TEST(Matrix3Class, Operators) {
	ape::Matrix3 mat1;
	ape::Matrix3 mat2(0, 1, 2, 3, 4, 5, 6, 7, 8);
	ape::Matrix3 mat2_2(0, 1, 2, 3, 4, 5, 6, 7, 8);
	ape::Matrix3 mat3(1, 0, 0, 0, 1, 0, 0, 0, 1);
	ape::Matrix3 mat4;
	ape::Matrix3 mat5(8, 7, 6, 5, 4, 3, 2, 1, 0);
	float* res = mat2[0];
	
	EXPECT_EQ(0.0f, res[0]);
	EXPECT_EQ(1.0f, res[1]);
	EXPECT_EQ(2.0f, res[2]);
	res = mat1[1];
	EXPECT_EQ(0.0f, res[0]);
	EXPECT_EQ(0.0f, res[1]);
	EXPECT_EQ(0.0f, res[2]);
	res = mat3[2];
	EXPECT_EQ(0.0f, res[0]);
	EXPECT_EQ(0.0f, res[1]);
	EXPECT_EQ(1.0f, res[2]);

	EXPECT_TRUE(mat1 == mat4);
	EXPECT_FALSE(mat2 == mat3);
	EXPECT_FALSE(mat1 == mat3);
	EXPECT_FALSE(mat2 == mat4);
	EXPECT_TRUE(mat2 == mat2_2);
	
	
	ape::Matrix3 mat6 = mat2 * mat3;
	ape::Matrix3 mat7 = mat2 * mat5;
	ape::Matrix3 mat8 = mat5 * mat2;
	mat4 = mat2 * mat1;
	float expected[9] = { 9,6,3,54,42,30,99,78,57 };


	

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			EXPECT_EQ(float(i*3+j), (mat1+mat2)[i][j]);
			EXPECT_EQ(float(-(i * 3 + j)), (mat1 - mat2)[i][j]);


			if (i == j)
				EXPECT_EQ(float(i * 3 + j-1), (mat2 - mat3)[i][j]);
			else
				EXPECT_EQ(float(-(i * 3 + j)), (mat3 - mat2)[i][j]);

			EXPECT_EQ(0.0f, mat4[i][j]);
			EXPECT_EQ(float(i * 3 + j), mat6[i][j]);
			EXPECT_EQ(expected[i * 3 + j], mat7[i][j]);
			EXPECT_EQ(expected[8-(i * 3 + j)], mat8[i][j]);
		}
	}


	mat1 = mat1 * 5;
	mat2_2 = mat2 * 5;
	mat3 = mat3 * 5;

	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			EXPECT_EQ(0.0f, mat1[i][j]);
			EXPECT_EQ(float(i * 3 + j)*5, mat2_2[i][j]);

			if (i == j)
				EXPECT_EQ(5.0f, mat3[i][j]);
			else
				EXPECT_EQ(0.0f, mat3[i][j]);
		}
	}

	ape::Vector3 vec(3, 2, 1);
	float expected3[3] = { 44, 26, 8 };
	ape::Vector3 vec2 = mat2 * vec;
	ape::Vector3 vec3 = mat1 * vec;
	ape::Vector3 vec4 = mat5 * vec;

	EXPECT_EQ("4, 22, 40", vec2.toString());
	EXPECT_EQ("0, 0, 0", vec3.toString());
	EXPECT_EQ("44, 26, 8", vec4.toString());

}

TEST(Matrix3Class, DQUDecomp) {
	ape::Matrix3 mat1;
	ape::Matrix3 mat2(2, 1, 2, 3, 4, 5, 6, 7, 8);
	ape::Matrix3 mat3(1, 0, 0, 0, 1, 0, 0, 0, 1);

	ape::Vector3 kD, kU;
	ape::Matrix3 kQ;

	mat1.QDUDecomposition(kQ, kD, kU);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			EXPECT_TRUE(isnan(kQ[i][j]));
		}
	}

	mat2.QDUDecomposition(kQ, kD, kU);
	float res[9] = { 0.285714, -0.909137, 0.303046,
					 0.428571, 0.404061, 0.808122,
					 0.857143, 0.101015, -0.505076
	};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			EXPECT_NEAR(-res[i*3+j], kQ[i][j], 0.0001);
		}
	}
	EXPECT_NEAR(-7, kD.x, 0.0001);
	EXPECT_NEAR(-1.4142135, kD.y, 0.0001);
	EXPECT_NEAR(-0.6060915, kD.z, 0.0001);

	EXPECT_NEAR(-8.0f/-7.0f, kU.x, 0.0001);
	EXPECT_NEAR(-9.5714285/-7, kU.y, 0.0001);
	EXPECT_NEAR(-1.0101525/-1.4142135, kU.z, 0.0001);

	mat3.QDUDecomposition(kQ, kD, kU);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if(i==j)
				EXPECT_FLOAT_EQ(1.0f, kQ[i][j]);
			else
				EXPECT_FLOAT_EQ(0.0f, kQ[i][j]);
		}
	}

	EXPECT_FLOAT_EQ(1.0f, kD.x);
	EXPECT_FLOAT_EQ(1.0f, kD.y);
	EXPECT_FLOAT_EQ(1.0f, kD.z);

	EXPECT_FLOAT_EQ(0.0f, kU.x);
	EXPECT_FLOAT_EQ(0.0f, kU.y);
	EXPECT_FLOAT_EQ(0.0f, kU.z);
}

TEST(Matrix3Class, String_json_vec) {
	ape::Matrix3 mat1;
	ape::Matrix3 mat2(0, 1, 2, 3, 4, 5, 6, 7, 8);
	EXPECT_EQ("0, 0, 0\n0, 0, 0\n0, 0, 0\n", mat1.toString());
	EXPECT_EQ("[ [ 0, 0, 0 ], [ 0, 0, 0 ], [ 0, 0, 0 ] ]", mat1.toJsonString());

	EXPECT_EQ("0, 1, 2\n3, 4, 5\n6, 7, 8\n", mat2.toString());
	EXPECT_EQ("[ [ 0, 1, 2 ], [ 3, 4, 5 ], [ 6, 7, 8 ] ]", mat2.toJsonString());

	std::vector<float> vec1 = mat1.toVector();
	for (int i = 0; i < 9; i++) {
		EXPECT_EQ(0.0f, vec1[i]);
	}

	std::vector<float> vec2 = mat2.toVector();
	for (int i = 0; i < 9; i++) {
		EXPECT_EQ(float(i), vec2[i]);
	}
}
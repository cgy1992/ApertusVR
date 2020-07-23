/*MIT License

Copyright (c) 2018 MTA SZTAKI

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#ifndef APE_QUATERNION_H
#define APE_QUATERNION_H

#include <cmath>
#include <sstream>
#include <vector>
#include "apeDegree.h"
#include "apeMatrix3.h"
#include "apeRadian.h"
#include "apeVector3.h"

namespace ape
{
	//! A struct for storing and handling quaternions
	struct Quaternion
	{
		//! Float numbers for storing the quaternion's data, but only the real numbers
		float w, x, y, z;


		//! Default constructor
		/*!
		It creates a quaternion with w=1.0, x=y=z=0.0
		*/
		Quaternion() :
			w(1.0f), x(0.0f), y(0.0f), z(0.0f)
		{}

		//! Constructor
		/*!
		Creates a quaternion with the given float values
		\param _w will be the value of w
		\param _x will be the value of x
		\param _y will be the value of y
		\param _z will be the value of z
		*/
		Quaternion(float _w, float _x, float _y, float _z) :
			w(_w), x(_x), y(_y), z(_z)
		{}

		//! Constructor
		/*!
		Creates a quaternion from a degree and a Vector3
		\param _degRot is an ape::Degree reference
		\param _axRost is an ape::Vector3 reference
		*/
		Quaternion(const ape::Degree& _degRot, const ape::Vector3& _axRot)
		{
			FromAngleAxis(ape::Radian(_degRot.toRadian()), _axRot);
		}

		//! Constructor
		/*!
		Creates a quaternion from a radian and a Vector3
		\param _radRot is an ape::Radian reference
		\param _axRost is an ape::Vector3 reference
		*/
		Quaternion(const ape::Radian& _radRot, const ape::Vector3& _axRot)
		{
			FromAngleAxis(_radRot, _axRot);
		}

		//! Constructor
		/*!
		Creates a quaternion from a 3*3 matrix
		\param m3x3 is an ape::Matrix3 reference
		*/
		Quaternion(const ape::Matrix3& m3x3)
		{
			FromRotationMatrix(m3x3);
		}

		/*!
		Overloading the + operator, so it adds two quaternions coordinate by coordinate
		\param rkQ is a reference to the Quaternion that will be added
		*/
		Quaternion operator+ (const Quaternion& rkQ) const
		{
			return Quaternion(w + rkQ.w, x + rkQ.x, y + rkQ.y, z + rkQ.z);
		}

		/*!
		Overloading the - operator, so it subtracts two quaternions coordinate by coordinate
		\param rkQ is a reference to the Quaternion that will be subtracted
		*/
		Quaternion operator- (const Quaternion& rkQ) const
		{
			return Quaternion(w - rkQ.w, x - rkQ.x, y - rkQ.y, z - rkQ.z);
		}

		/*!
		Overloading the - operator, so it multiplies all values with -1
		*/
		Quaternion operator- () const
		{
			return Quaternion(-w, -x, -y, -z);
		}

		/*!
		Overloading the / operator, so it divides all values with the given float value
		\param fScalar is the float the quaternion will be divided with
		*/
		Quaternion operator / (const float fScalar) const
		{
			return Quaternion(
			           w / fScalar,
			           x / fScalar,
			           y / fScalar,
			           z / fScalar);
		}

		/*!
		Overloading the * operator, so it multiplies the quaternion with a vector3
		\param v is a reference to the vector3 the quaternion will be multiplied with
		*/
		ape::Vector3 operator* (const ape::Vector3& v) const
		{
			ape::Vector3 uv, uuv;
			ape::Vector3 qvec(x, y, z);
			uv = qvec.crossProduct(v);
			uuv = qvec.crossProduct(uv);
			uv = uv * (2.0f * w);
			uuv = uuv * 2.0f;
			return v + uv + uuv;
		}

		/*!
		Overloading the < operator, so it returns true only if coordinate by coordinate all
		values of the other quaternion are smaller
		\param rkQ is a reference to the other Quaternion
		*/
		bool operator < (const Quaternion& rkQ) const
		{
			return (w < rkQ.w && x < rkQ.x && y < rkQ.y && z < rkQ.z);
		}

		/*!
		Overloading the > operator, so it returns true only if coordinate by coordinate all
		values of the other quaternion are bigger
		\param rkQ is a reference to the other Quaternion
		*/
		bool operator > (const Quaternion& rkQ) const
		{
			return (w > rkQ.w  && x > rkQ.x && y > rkQ.y && z > rkQ.z);
		}

		/*!
		A function that multiplies 2 quaternions
		\param rkQ is a reference to a Quaternion
		*/
		Quaternion product(const Quaternion& rkQ) const
		{
			return Quaternion(
				w * rkQ.w - x * rkQ.x - y * rkQ.y - z * rkQ.z,
				w * rkQ.x + x * rkQ.w + y * rkQ.z - z * rkQ.y,
				w * rkQ.y + y * rkQ.w + z * rkQ.x - x * rkQ.z,
				w * rkQ.z + z * rkQ.w + x * rkQ.y - y * rkQ.x);
		}

		/*!
		Overloading the * operator, so it multiplies the quaternion with another quaternion
		\param rkQ is a reference to a quaternion
		*/
		Quaternion operator* (const Quaternion& rkQ) const
		{
			return product(rkQ);
		}

		/*!
		Creates a quaternion from a radian (angle) and a vector3 (axis)
		\param _angleRadian is an ape::Radian
		\param _axid is an ape::Vector3
		*/
		void FromAngleAxis(ape::Radian _angleRadian, const ape::Vector3& _axis)
		{
			float fHalfAngle((float)(0.5 * _angleRadian.radian));
			float fSin = std::sin(fHalfAngle);
			w = std::cos(fHalfAngle);
			x = fSin * _axis.x;
			y = fSin * _axis.y;
			z = fSin * _axis.z;
		}

		/*
		Creates a quaternion from a 3*3 matrix
		\param kRot is an ape::Matrix3 reference
		*/
		void FromRotationMatrix(const ape::Matrix3& kRot)
		{
			float fTrace = kRot[0][0] + kRot[1][1] + kRot[2][2];
			float fRoot;

			if (fTrace > 0.0)
			{
				fRoot = std::sqrt(fTrace + 1.0f);
				w = 0.5f * fRoot;
				fRoot = 0.5f / fRoot;
				x = (kRot[2][1] - kRot[1][2]) * fRoot;
				y = (kRot[0][2] - kRot[2][0]) * fRoot;
				z = (kRot[1][0] - kRot[0][1]) * fRoot;
			}
			else
			{
				static size_t s_iNext[3] = { 1, 2, 0 };
				size_t i = 0;
				if (kRot[1][1] > kRot[0][0])
					i = 1;
				if (kRot[2][2] > kRot[i][i])
					i = 2;
				size_t j = s_iNext[i];
				size_t k = s_iNext[j];

				fRoot = std::sqrt(kRot[i][i] - kRot[j][j] - kRot[k][k] + 1.0f);
				float* apkQuat[3] = { &x, &y, &z };
				*apkQuat[i] = 0.5f * fRoot;
				fRoot = 0.5f / fRoot;
				w = (kRot[k][j] - kRot[j][k]) * fRoot;
				*apkQuat[j] = (kRot[j][i] + kRot[i][j]) * fRoot;
				*apkQuat[k] = (kRot[k][i] + kRot[i][k]) * fRoot;
			}
		}

		/*
		Returns true only if all coodinates are equal to the other quaternion's appropiate
		coordinates
		*/
		bool equals(const ape::Quaternion& _q2, ape::Radian _tolerance)
		{
			/*float fCos = w * _q2.w + x * _q2.x + y * _q2.y + z * _q2.z;
			float angle = std::acos(fCos);
			return (abs(angle) <= _tolerance.radian) || abs(angle - ape_PI) <= _tolerance.radian;*/
			return (_q2.x == x) && (_q2.y == y) && (_q2.z == z) && (_q2.w == w);
		}

		/*!
		Returns sum of the squared coordinates
		*/
		float Norm() const
		{
			return w * w + x * x + y * y + z * z;
		}

		/*!
		Normalises the quaternion and returns the square of the length
		*/
		float normalise()
		{
			float len = Norm();
			float factor = 1.0f / std::sqrt(len);
			w = w * factor;
			x = x * factor;
			y = y * factor;
			z = z * factor;
			return len;
		}

		/*!
		Returns the inverse of the normalised quaternion
		*/
		Quaternion Inverse() const
		{
			float fNorm = Norm();
			if (fNorm > 0.0)
			{
				float fInvNorm = 1.0f / fNorm;
				return Quaternion(w * fInvNorm, -x * fInvNorm, -y * fInvNorm, -z * fInvNorm);
			}
			else
			{
				return Quaternion(0, 0, 0, 0);
			}
		}

		/*!
		Returns the dot product of 2 quaternions
		\param rkQ is a reference to a Quaternion
		*/
		float Dot(const Quaternion& rkQ) const
		{
			return w * rkQ.w + x * rkQ.x + y * rkQ.y + z * rkQ.z;
		}

		/*!
		Calculates the spherical linear interpolation on the quaternion
		\param fT is the interpolation parameter between 0 and 1
		\param rkP and rkQ are the 2 quaternions between which the interpolation will be calculated
		\param shortestPath determines whether to calculate the shortest path
		*/
		static Quaternion Slerp(float fT, const Quaternion& rkP,
		                        const Quaternion& rkQ, bool shortestPath)
		{
			float fCos = rkP.Dot(rkQ);
			Quaternion rkT;
			if (fCos < 0.0f && shortestPath)
			{
				fCos = -fCos;
				rkT = -rkQ;
			}
			else
			{
				rkT = rkQ;
			}

			if (abs(fCos) < 1 - 1e-03)
			{
				float fSin = std::sqrt(1 - std::pow(fCos, 2));
				Radian fAngle = std::atan2(fSin, fCos);
				float fInvSin = 1.0f / fSin;
				float fCoeff0 = std::sin((1.0f - fT) * fAngle.radian) * fInvSin;
				float fCoeff1 = std::sin(fT * fAngle.radian) * fInvSin;
				return Quaternion(fCoeff0 * rkP.w, fCoeff0 * rkP.x, fCoeff0 * rkP.y, fCoeff0 * rkP.z) + Quaternion(fCoeff1 * rkT.w, fCoeff1 * rkT.x, fCoeff1 * rkT.y, fCoeff1 * rkT.z);
			}
			else
			{
				float fScalar0 = (1.0f - fT);
				Quaternion t = Quaternion(fScalar0 * rkP.w, fScalar0 * rkP.x, fScalar0 * rkP.y, fScalar0 * rkP.z) + Quaternion(fT * rkT.w, fT * rkT.x, fT * rkT.y, fT * rkT.z);
				t.normalise();
				return t;
			}
		}

		/*!
		Converts the quaternion into a 3*3 matrix
		\param kRot is an ape::Matrix3 reference, the quaternion will be converted into this
		*/
		void ToRotationMatrix(ape::Matrix3& kRot) const
		{
			float fTx = x + x;
			float fTy = y + y;
			float fTz = z + z;
			float fTwx = fTx * w;
			float fTwy = fTy * w;
			float fTwz = fTz * w;
			float fTxx = fTx * x;
			float fTxy = fTy * x;
			float fTxz = fTz * x;
			float fTyy = fTy * y;
			float fTyz = fTz * y;
			float fTzz = fTz * z;

			kRot[0][0] = 1.0f - (fTyy + fTzz);
			kRot[0][1] = fTxy - fTwz;
			kRot[0][2] = fTxz + fTwy;
			kRot[1][0] = fTxy + fTwz;
			kRot[1][1] = 1.0f - (fTxx + fTzz);
			kRot[1][2] = fTyz - fTwx;
			kRot[2][0] = fTxz - fTwy;
			kRot[2][1] = fTyz + fTwx;
			kRot[2][2] = 1.0f - (fTxx + fTyy);
		}

		//! Returns w
		float getW() { return w; }
		//! Returns x
		float getX() { return x; }
		//! Returns y
		float getY() { return y; }
		//! Returns z
		float getZ() { return z; }

		//! Retruns the quaternion converted to string fromat
		std::string toString() const
		{
			std::ostringstream buff;
			buff << w << ", " << x << ", " << y << ", " << z;
			return buff.str();
		}

		//! Retruns the quaternion converted to json format
		std::string toJsonString() const
		{
			std::ostringstream buff;
			buff << "{ \"w\": " << w << ", \"x\": " << x << ", \"y\": " << y << ", \"z\": " << z << " }";
			return buff.str();
		}

		//! Retruns the quaternion converted to std::vector<float>
		std::vector<float> toVector() const
		{
			std::vector<float> vec{ w, x, y, z };
			return vec;
		}

		/*!
		Writes the quaternion's data into the given file
		\param fileStreamOut is a reference to the file
		\param writeSize determines whether the size should be written too
		*/
		void write(std::ofstream& fileStreamOut, bool writeSize = true)
		{
			if (writeSize)
			{
				long sizeInBytes = 16;
				fileStreamOut.write(reinterpret_cast<char*>(&sizeInBytes), sizeof(long));
			}
			fileStreamOut.write(reinterpret_cast<char*>(&w), sizeof(float));
			fileStreamOut.write(reinterpret_cast<char*>(&x), sizeof(float));
			fileStreamOut.write(reinterpret_cast<char*>(&y), sizeof(float));
			fileStreamOut.write(reinterpret_cast<char*>(&z), sizeof(float));
		}

		/*!
		Reads the quaternion's data from the given file
		\param fileStreamIn is a reference to the file
		*/
		void read(std::ifstream& fileStreamIn)
		{
			fileStreamIn.read(reinterpret_cast<char*>(&w), sizeof(float));
			fileStreamIn.read(reinterpret_cast<char*>(&x), sizeof(float));
			fileStreamIn.read(reinterpret_cast<char*>(&y), sizeof(float));
			fileStreamIn.read(reinterpret_cast<char*>(&z), sizeof(float));
		}
	};
}

#endif

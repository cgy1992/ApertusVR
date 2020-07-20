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

#ifndef APE_VECTOR3_H
#define APE_VECTOR3_H

#include <cmath>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

namespace ape
{
	/*!
	A struct for handling vector of 3 floats
	*/
	struct Vector3
	{
		/*!
		3 floats for stroing the x,y,z coordinate data
		*/
		float x, y, z;

		//! Default constructor
		/*!
		Creates a vector with x=y=z=0
		*/
		Vector3() :
			x(0.0f), y(0.0f), z(0.0f) 
		{}

		//!Constructor
		/*!
		For creating a vector with any float value
		\param _x is a float that will be the value of x
		\param _y is a float that will be the value of y
		\param _z is a float that will be the value of z
		*/
		Vector3(float _x, float _y, float _z) :
			x(_x), y(_y), z(_z)
		{}

		//!Constructor
		/*!
		For creating a vector with the same value in x, y, z
		\param _d is a float that will be the value of x,y,z
		*/
		Vector3(float _d) :
			x(_d), y(_d), z(_d)
		{}

		/*!
		A void function that writes the vectors data into a file, 
		the file will contain optionally the size, after the the x,y,z values
		\param fileStreamOut is a reference to an std::ofstream, the data will be written
			into the file this points to
		\param writeSize is a bool, with true as a default value, it determines if the function
			should write the size into the file
		*/
		void write(std::ofstream& fileStreamOut, bool writeSize = true)
		{
			if (writeSize)
			{
				long sizeInBytes = 12;
				fileStreamOut.write(reinterpret_cast<char*>(&sizeInBytes), sizeof(long));
			}
			fileStreamOut.write(reinterpret_cast<char*>(&x), sizeof(float));
			fileStreamOut.write(reinterpret_cast<char*>(&y), sizeof(float));
			fileStreamOut.write(reinterpret_cast<char*>(&z), sizeof(float));
		}

		/*!
		A void function that reads x,y,z from a file
		\param fileStreamOut is a reference to an std::ofstream, the data will be read
			from the file this points to
		*/
		void read(std::ifstream& fileStreamIn)
		{
			fileStreamIn.read(reinterpret_cast<char*>(&x), sizeof(float));
			fileStreamIn.read(reinterpret_cast<char*>(&y), sizeof(float));
			fileStreamIn.read(reinterpret_cast<char*>(&z), sizeof(float));
		}
		/*!
		A float function that returns every coordinate's squared value's sum: x*x+y*y+z*z
		*/
		float squaredLength() const
		{
			return x * x + y * y + z * z;
		}

		/*!
		A float function that returns the vector's length, it is the root of the sum of
		every coordinates's squared value 
		*/
		float length() const
		{
			return std::sqrt(x * x + y * y + z * z);
		}


		/*!
		A float function that returns the length of the difference of two vectors.
		\param rkVector a constant reference to a Vector3
		*/
		float distance(const Vector3& rkVector) const
		{
			return (*this - rkVector).length();
		}

		/*!
		A Vector3 function that returns the cross product of the vectors.
		It returns a vector3.
		\param rkVector is a vector3 reference, the cross product will be calculated with this
		*/
		Vector3 crossProduct(const Vector3& rkVector) const
		{
			return Vector3(
			           y * rkVector.z - z * rkVector.y,
			           z * rkVector.x - x * rkVector.z,
			           x * rkVector.y - y * rkVector.x);
		}

		/*!
		A float function that returns the dot product.
		\param vec is a vector3 reference, the dot product will be calculated with this
		*/
		float dotProduct(const Vector3& vec) const
		{
			return x * vec.x + y * vec.y + z * vec.z;
		}

		/*!
		Overloading the = operator so it puts each of the other vector's data (x,y, z) into
		this vector.
		It returns a vector3.
		\param rkVector is a vector3 reference, this is the other vector that data data comes from
		*/
		Vector3& operator = (const Vector3& rkVector)
		{
			x = rkVector.x;
			y = rkVector.y;
			z = rkVector.z;

			return *this;
		}
		/*!
		Overloading the = operator so it puts the float into all 3 (x,y,z) places.
		It returns a vector3.
		\param fScaler is a float, this will be the value of x,y,z
		*/
		Vector3& operator = (const float fScaler)
		{
			x = fScaler;
			y = fScaler;
			z = fScaler;

			return *this;
		}

		/*!
		Overloading the == operator so it returns true if the 2 vectors
		are equal in all corresponding coordinates.
		\param rkVector is a vector3 reference, this is the vector we check the equality againts
		*/
		bool operator == (const Vector3& rkVector) const
		{
			return equalTo(rkVector);
		}

		/*!
		Overloading the < operator so it returns true only if all 3 coordinates of the vector are
		less then the other vector's corresponding coordinates.
		\param rkVector is a vector3 reference, this is the vector we check if it is bigger
		*/
		bool operator < (const Vector3& rkVector) const
		{
			return (x < rkVector.x && y < rkVector.y && z < rkVector.z);
		}

		/*!
		Overloading the > operator so it returns true only if all 3 coordinates of the vector are
		bigger then the other vector's corresponding coordinates.
		\param rkVector is a vector3 reference, this is the vector we check if it is smaller
		*/
		bool operator > (const Vector3& rkVector) const
		{
			return (x > rkVector.x && y > rkVector.y && z > rkVector.z);
		}

		/*!
		Overloading the != operator so it returns true only if at least one of the 3 
		corresponding coordinate pairs of the vectors are not equal.
		\param rkVector is a vector3 reference, this is the vector we check the inequality againts
		*/
		bool operator != (const Vector3& rkVector) const
		{
			return !equalTo(rkVector);
		}

		/*!
		A bool function that returns true if the 2 vectors
		are equal in all corresponding coordinates.
		\param rkVector is a vector3 reference, this is the vector we check the equality againts
		*/
		bool equalTo(const Vector3& rkVector) const
		{
			return (x == rkVector.x && y == rkVector.y && z == rkVector.z);
		}

		/*!
		Overloading the * operator so it multiplies all 3 coordinates with the given value.
		It returns the resulting vector3.
		\param fScalaer is a float, this is the value that we multiply with
		*/
		Vector3 operator * (const float fScalar) const
		{
			return Vector3(
			           x * fScalar,
			           y * fScalar,
			           z * fScalar);
		}

		/*!
		Overloading the / operator so it divides all 3 coordinates by the given value.
		It returns the resulting vector3.
		\param fScalaer is a float, this is the value that we divide with
		*/
		Vector3 operator / (const float fScalar) const
		{
			return Vector3(
			           x / fScalar,
			           y / fScalar,
			           z / fScalar);
		}


		/*!
		Overloading the / operator so it divides all the coordinates by the other vector's corresponding
		coordinates.
		It returns the resulting vector3.
		\param rhs is a vector3 reference, this is the vector that we divide by
		*/
		Vector3 operator / (const Vector3& rhs) const
		{
			return Vector3(
			           x / rhs.x,
			           y / rhs.y,
			           z / rhs.z);
		}

		/*!
		Overloading the * operator so it multiplies all the coordinates with the other vector's
		corresponding coordinates.
		It returns the resulting vector3.
		\param rhs is a vector3 reference, this is the vector that we multiply with
		*/
		Vector3 operator * (const Vector3& rhs) const
		{
			return Vector3(
			           x * rhs.x,
			           y * rhs.y,
			           z * rhs.z);
		}

		/*!
		Overloading the + operator so it adds all the coordinates to the other vector's
		corresponding coordinates.
		It returns the resulting vector3.
		\param rkVector is a vector3 reference, this is the vector that we add
		*/
		Vector3 operator + (const Vector3& rkVector) const
		{
			return Vector3(
			           x + rkVector.x,
			           y + rkVector.y,
			           z + rkVector.z);
		}

		/*!
		Overloading the - operator so it subtracts all the coordinates of the other vector
		from this vector's corresponding coordinates .
		It returns the resulting vector3.
		\param rkVector is a vector3 reference, this is the vector that we subtract
		*/
		Vector3 operator - (const Vector3& rkVector) const
		{
			return Vector3(
			           x - rkVector.x,
			           y - rkVector.y,
			           z - rkVector.z);
		}

		/*!
		Overloading the - operator so it multiplies all coordinates with -1
		It returns the resulting vector3.
		*/
		Vector3 operator - () const
		{
			return Vector3(-x, -y, -z);
		}

		/*!
		Overloading the += operator so it adds all the coordinates of the other vector to the
		corresponding coordinate of this vector.
		*/
		void operator += (const Vector3& rkVector)
		{
			x += rkVector.x;
			y += rkVector.y;
			z += rkVector.z;
		}


		/*!
		Overloading the += operator so it subtracts all the coordinates of the other vector from
		the corresponding coordinate of this vector.
		*/
		void operator -= (const Vector3& rkVector)
		{		
			x -= rkVector.x;
			y -= rkVector.y;
			z -= rkVector.z;
		}

		/*!
		A bool function that returns true only if all 3 coordinates are NaN.
		*/
		bool isNaN() const
		{
			return std::isnan(x) && std::isnan(y) && std::isnan(z);
		}

		/*!
		A float function that returns the length of the vector, and normalises it:
		it divides all coordinates by the length of the vector.
		*/
		float normalise()
		{
			float fLength = sqrt(x * x + y * y + z * z);
			if (fLength > 1e-08)
			{
				float fInvLength = 1.0f / fLength;
				x *= fInvLength;
				y *= fInvLength;
				z *= fInvLength;
			}
			return fLength;
		}

		/*!
		A float function that returns the vector's x value.
		*/
		float getX()
		{
			return x;
		}

		/*!
		A float function that returns the vector's y value.
		*/
		float getY()
		{
			return y;
		}

		/*!
		A float function that returns the vector's z value.
		*/
		float getZ()
		{
			return z;
		}

		/*!
		A std::string function that returns the vector in string format.
		*/
		std::string toString() const
		{
			std::ostringstream buff;
			buff << x << ", " << y << ", " << z;
			return buff.str();
		}

		/*!
		A std::string function that returns the vector in json format.
		*/
		std::string toJsonString() const
		{
			std::ostringstream buff;
			buff << "{ ";
			buff << "\"x\": " << x << ", ";
			buff << "\"y\": " << y << ", ";
			buff << "\"z\": " << z;
			buff << " }";
			return buff.str();
		}

		/*!
		A function that returns the vector converted to std::vector<float>.
		*/
		std::vector<float> toVector() const
		{
			std::vector<float> vec{ x, y, z };
			return vec;
		}
	};
}

#endif

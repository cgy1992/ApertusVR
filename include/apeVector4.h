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

#ifndef APE_VECTOR4_H
#define APE_VECTOR4_H

#include <vector>

namespace ape
{
	struct Vector4
	{
		/*!
		3 floats for stroing the x,y,z, w coordinate data
		*/
		float x, y, z, w;


		//! Default constructor
		/*!
		Creates a vector with x=y=z=w=0
		*/
		Vector4() :
			x(0.0f), y(0.0f), z(0.0f), w(0.0f)
		{}

		//!Constructor
		/*!
		For creating a vector with any float value
		\param _x is a float that will be the value of x
		\param _y is a float that will be the value of y
		\param _z is a float that will be the value of z
		\param _w is a float that will be the value of w
		*/
		Vector4(float _x, float _y, float _z, float _w) :
			x(_x), y(_y), z(_z), w(_w)
		{}

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
		A float function that returns the vector's w value.
		*/
		float getW()
		{
			return w;
		}

		/*!
		A std::string function that returns the vector in string format.
		*/
		std::string toString() const
		{
			std::ostringstream buff;
			buff << x << ", " << y << ", " << z << ", " << w << std::endl;
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
			buff << "\"z\": " << z << ", ";
			buff << "\"w\": " << w;
			buff << " }";
			return buff.str();
		}

		/*!
		A function that returns the vector converted to std::vector<float>.
		*/
		std::vector<float> toVector() const
		{
			std::vector<float> vec{ x, y, z, w};
			return vec;
		}
	};
}

#endif

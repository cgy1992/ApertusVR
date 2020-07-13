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

#ifndef APE_RADIAN_H
#define APE_RADIAN_H

#define ape_PI       3.14159265358979323846

namespace ape
{
	/*!
	A struct for storing degrees in radian
	*/
	struct Radian
	{
		/*!
		A float for storing the radian
		*/
		float radian;

		//! Default constructor
		/*!
		The default constructor creates a radian with 0 as value
		*/
		Radian() :
			radian(0.0f)
		{}

		//!Constructor
		/*!
		A constructor for creating radian with any value
		\param _radian a float that will be the value of the radian
		*/
		Radian(float _radian) :
			radian(_radian)
		{}

		/*!
		A float function that returns the degree of the radian
		*/
		float toDegree() const
		{
			return float(radian * 180 / ape_PI);
		};

		/*!
		A float function that returns the radian
		*/
		float getRadian()
		{
			return radian;
		}
	};
}

#endif

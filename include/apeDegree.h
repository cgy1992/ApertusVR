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

#ifndef APE_DEGREE_H
#define APE_DEGREE_H

#define ape_PI		3.14159265358979323846

namespace ape
{
	/*!
		A struct for storing and handling degrees.
	*/
	struct Degree
	{
		//! A float for storing and handling the degrees
		float degree;

		//! Default constructor
		/*!
		  The default constructor creates a 0 degree
		*/
		Degree() :
			degree(0.0f)
		{}


		//! Constructor
		/*!
			A constructor for creating a degree with any value
			\param _degree the value of the degree, must be given
		*/
		Degree(float _degree) :
			degree(_degree)
		{}

		//! A function that returns the radian of the degree in float
		float toRadian() const
		{
			return float(degree * ape_PI / 180);
		};

		//! A function that return the degree
		float getDegree()
		{
			return degree;
		}
	};
}

#endif

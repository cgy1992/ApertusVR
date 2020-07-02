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

#ifndef APE_COLOR_H
#define APE_COLOR_H

#include <sstream>
#include <vector>
#include <fstream>

namespace ape
{
	//! A struct
	/*!
		A struct for storing and handling colors.
	*/
	struct Color
	{
		//! Four floats
		/*!
			Four floats for storing the data of the colors: r for red, g for green, b for blue and
			a for alpha
		*/
		float r, g, b, a;

		//! Default constructor
		/*!
		  The default constructor creates black color, so r=g=b=0 and a = 1
		*/
		Color() :
			r(0.0f), g(0.0f), b(0.0f), a(1.0f)
		{}

		//! Constructor
		/*!
		  Constructor for creating colors with any given value.
		  \param r a float for red, must be provided
		  \param g a float for green, must be provided
		  \param b a float for blue, must be provided
		  \param a a float for alpha, optional, default value: 1.0
		*/
		Color(float _r, float _g, float _b, float _a = 1.0f) :
			r(_r), g(_g), b(_b), a(_a)
		{}

		//! A function to get the color in string format
		/*!
		 It returns a string which contains: "Color( r: value_of_r, g: value_of_g, b: value_of_b,
			a: value_of_a )"
		*/
		std::string toString() const
		{
			std::ostringstream buff;
			buff << "Color(" << r << ", " << g << ", " << b << ", " << a << ")";
			return buff.str();
		}

		//! A function to get the color in json format
		/*!
		 It returns a string which contains: "{ "r": value_of_r, "g": value_of_g, "b": value_of_b,
			"a": value_of_a }"
		*/
		std::string toJsonString() const
		{
			std::ostringstream buff;
			buff << "{ ";
			buff << "\"r\": " << r << ", ";
			buff << "\"g\": " << g << ", ";
			buff << "\"b\": " << b << ", ";
			buff << "\"a\": " << a;
			buff << " }";
			return buff.str();
		}

		//! A function that return the r float
		float getR()
		{
			return r;
		}

		//! A function that return the G float
		float getG()
		{
			return g;
		}

		//! A function that return the B float
		float getB()
		{
			return b;
		}

		//! A function that return the A float
		float getA()
		{
			return a;
		}

		//! A function for writing the color into a file
		/*!
		  It writes the size optionally into the file, after that it writes the value of r, b, g, a respectively
		  \param fileStreamOut an std::ofstream, which points to the file the color should be written in
		  \param writeSize a bool, if true the size will be written in the beginning of the file
		*/
		void write(std::ofstream& fileStreamOut, bool writeSize = true)
		{
			if (writeSize)
			{
				long sizeInBytes = 16;
				fileStreamOut.write(reinterpret_cast<char*>(&sizeInBytes), sizeof(long));
			}
			fileStreamOut.write(reinterpret_cast<char*>(&r), sizeof(float));
			fileStreamOut.write(reinterpret_cast<char*>(&g), sizeof(float));
			fileStreamOut.write(reinterpret_cast<char*>(&b), sizeof(float));
			fileStreamOut.write(reinterpret_cast<char*>(&a), sizeof(float));
		}

		//! A function for reading the color from a file
		/*!
		  It reads the  the value of r, b, g, a respectively from a file
		  \param fileStreamOut an std::ifstream, which points to the file that we want to read from
		*/
		void read(std::ifstream& fileStreamIn)
		{
			fileStreamIn.read(reinterpret_cast<char*>(&r), sizeof(float));
			fileStreamIn.read(reinterpret_cast<char*>(&g), sizeof(float));
			fileStreamIn.read(reinterpret_cast<char*>(&b), sizeof(float));
			fileStreamIn.read(reinterpret_cast<char*>(&a), sizeof(float));
		}

	};

	//! An alias for creating vectors of color
	typedef std::vector < ape::Color > ColorVector;
}

#endif

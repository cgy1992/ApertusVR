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

#ifndef APE_JSBIND_MATRIX4_H
#define APE_JSBIND_MATRIX4_H

#include "apeMatrix4.h"
#include "nbind/nbind.h"
#include "nbind/api.h"

using namespace ape;

#ifdef NBIND_CLASS

NBIND_CLASS(Matrix4)
{
	construct<>();
	construct<float, float, float, float,
			  float, float, float, float,
			  float, float, float, float,
			  float, float, float, float>();

	method(swap);
	method(concatenate);
	method(transpose);
	method(inverse);
	method(makeTransform);
	method(extract3x3Matrix);
	method(decomposition);

	method(toString);
	method(toJsonString);
	method(toVector);
}

#endif

#endif

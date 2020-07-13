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

#ifndef APE_DOUBLEQUEUE_H
#define APE_DOUBLEQUEUE_H

#include <algorithm>
#include <mutex>
#include <set>
#include <vector>

namespace ape
{
	//! A class
	/*!
	  A class that creates a doublequeue for any T type
	*/
	template<typename T>
	class DoubleQueue
	{
	private:

		/*!
		  A T type vector for push operations
		*/
		std::vector<T> mPush;

		/*!
		  A T type vector for pop operations
		*/
		std::vector<T> mPop;

		/*!
		  A mutex for protecting the data in the doublequeue
		*/
		std::mutex mPushMutex;

	public:

		//! Default constructor
		/*!
		  The default constructor creates an empty doublequeue
		*/
		DoubleQueue() : mPush(std::vector<T>()), mPop(std::vector<T>())
		{
		}

		//! Destructor
		/*!
		  The destructor clears both mPush and mPop
		*/
		~DoubleQueue()
		{
			mPush.clear();
			mPop.clear();
		}

		/*!
		  A void function for swapping the content of mPush and mPop
		*/
		void swap()
		{
			std::lock_guard<std::mutex> lock(mPushMutex);
			mPush.swap(mPop);
		}

		/*!
		  A bool function that returns true only if both mPop and mPush are empty
		*/
		bool empty()
		{
			return emptyPop() && emptyPush();
		}

		/*!
		  A bool function that returns true only if mPop is empty
		*/
		bool emptyPop()
		{
			return mPop.empty();
		}

		/*!
		  A bool function that returns true only if mPush is empty
		*/
		bool emptyPush()
		{
			std::lock_guard<std::mutex> lock(mPushMutex);
			return mPush.empty();
		}

		/*!
		  A T type function that return the first element from mPop if it is not empty 
		*/
		T front()
		{
			return mPop.empty() ? T() : (*mPop.begin());
		}

		/*!
		  A void function that pushes an element at the end of mPush, if APE_DOUBLEQUEUE_UNIQUE
		  is defined than it only pushes the element if the queue does not already contain it
		*/
		void push(T elem)
		{
			std::lock_guard<std::mutex> lock(mPushMutex);
#ifdef APE_DOUBLEQUEUE_UNIQUE
			if (std::find(mPush.begin(), mPush.end(), elem) == mPush.end())
			{
				mPush.push_back(elem);
			}
#else
			mPush.push_back(elem);
#endif
		}

		/*!
		  A void function that erases the first element of mPop, if it is not empty
		*/
		void pop()
		{
			if (!mPop.empty())
			{
				mPop.erase(mPop.begin());
			}
		}

		/*!
		  A size_t type function that return the size of mPop plus the size of mPush
		*/
		size_t size()
		{
			return mPop.size() + mPush.size();
		}

		/*!
		  A size_t type function that return the size of mPop
		*/
		size_t sizePop()
		{
			return mPop.size();
		}

		/*!
		  A size_t type function that return the size of mPush
		*/
		size_t sizePush()
		{
			return mPush.size();
		}

		/*!
		  Overloading the = operator so it puts the content of the other doublequeue into this
		  dequeue
		  \param other a reference to a doublequeue
		*/
		DoubleQueue& operator =(const DoubleQueue& other)
		{
			mPush = other.mPush;
			mPop = other.mPop;
			return *this;
		}
	};
}

#endif

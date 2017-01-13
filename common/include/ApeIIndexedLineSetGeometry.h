/*MIT License

Copyright (c) 2016 MTA SZTAKI

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

#ifndef APE_IINDEXEDLINESETGEOMETRY_H
#define APE_IINDEXEDLINESETGEOMETRY_H

#include <string>
#include <vector>
#include "ApeGeometry.h"

namespace Ape
{	

	struct GeometryIndexedLineSetParameters
	{
		Ape::GeometryCoordinates coordinates;
		Ape::GeometryIndices indices;
		
		GeometryIndexedLineSetParameters()
		{
			this->coordinates = Ape::GeometryCoordinates();
			this->indices = Ape::GeometryIndices();
		}

		GeometryIndexedLineSetParameters(
			Ape::GeometryCoordinates coordinates,
			Ape::GeometryIndices indices)
		{
			this->coordinates = coordinates;
			this->indices = indices;
		}
	};
	
	class IIndexedLineSetGeometry : public Geometry
	{
	protected:
		IIndexedLineSetGeometry(std::string name) : Geometry(name, Entity::GEOMETRY_INDEXEDLINESET) {}

		virtual ~IIndexedLineSetGeometry() {};
		
	public:
		virtual void setParameters(Ape::GeometryCoordinates coordinates, Ape::GeometryIndices indices) = 0;
		
		virtual Ape::GeometryIndexedLineSetParameters getParameters() = 0;

		virtual void setParentNode(Ape::NodeWeakPtr parentNode) = 0;

		virtual void setMaterial(Ape::MaterialWeakPtr material) = 0;

		virtual Ape::MaterialWeakPtr getMaterial() = 0;
	};
}

#endif

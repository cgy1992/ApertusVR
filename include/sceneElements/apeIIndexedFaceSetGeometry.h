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

#ifndef APE_IINDEXEDFACESETGEOMETRY_H
#define APE_IINDEXEDFACESETGEOMETRY_H

#include <string>
#include <vector>
#include "datatypes/apeGeometry.h"

namespace ape
{	
	struct GeometryIndexedFaceSetParameters
	{
		std::string groupName;
		ape::GeometryCoordinates coordinates;
		ape::GeometryIndices indices;
		ape::GeometryNormals normals;
		ape::GeometryTangents tangents;
		bool generateNormals;
		ape::GeometryColors colors;
		ape::GeometryTextureCoordinates textureCoordinates;
		ape::MaterialWeakPtr material;
		std::string materialName;
		ape::GeometryFaces faces;
		
		GeometryIndexedFaceSetParameters()
		{
			this->groupName = std::string();
			this->coordinates = ape::GeometryCoordinates();
			this->indices = ape::GeometryIndices();
			this->normals = ape::GeometryNormals();
			this->generateNormals = true;
			this->colors = ape::GeometryColors();
			this->textureCoordinates = ape::GeometryTextureCoordinates();
			this->material = ape::MaterialWeakPtr();
			this->materialName = std::string();
			this->tangents = ape::GeometryTangents();
			this->faces = ape::GeometryFaces();
		}

		GeometryIndexedFaceSetParameters(std::string groupName, ape::GeometryCoordinates coordinates, ape::GeometryIndices indices, ape::GeometryNormals normals, ape::GeometryTangents tangents, bool generateNormals, ape::GeometryColors colors, ape::GeometryTextureCoordinates textureCoordinates, ape::MaterialWeakPtr material , ape::GeometryFaces faces)
		{
			this->groupName = groupName;
			this->coordinates = coordinates;
			this->indices = indices;
			this->normals = normals;
			this->tangents = tangents;
			this->generateNormals = generateNormals;
			this->colors = colors;
			this->textureCoordinates = textureCoordinates;
			this->material = material;
			if (auto materialPtr = this->material.lock())
				this->materialName = materialPtr->getName();
			else
				this->materialName = std::string();
			this->faces = faces;
		}

		ape::GeometryCoordinates getCoordinates()
		{
			return coordinates;
		}

		ape::GeometryIndices getIndices()
		{
			return indices;
		}

		ape::GeometryNormals getNormals()
		{
			return normals;
		}

		ape::GeometryTangents getTangents()
		{
			return tangents;
		}

		ape::GeometryColors getColors()
		{
			return colors;
		}

		ape::GeometryTextureCoordinates getTextureCoordinates()
		{
			return textureCoordinates;
		}

		ape::GeometryFaces getFaces()
		{
			return faces;
		}

		std::string toString() const
		{
			std::ostringstream buff;

			buff << "Coordinates(";
			for (auto const &item : coordinates) buff << item << ", ";
			buff << ")" << std::endl;

			buff << "Indices(";
			for (auto const &item : indices) buff << item << ", ";
			buff << ")" << std::endl;

			buff << "Normals(";
			for (auto const &item : normals) buff << item << ", ";
			buff << ")" << std::endl;

			buff << "Tangents(";
			for (auto const &item : tangents) buff << item << ", ";
			buff << ")" << std::endl;

			buff << "Colors(";
			for (auto const &item : colors) buff << item << ", ";
			buff << ")" << std::endl;

			buff << "TextureCoordinates(";
			for (auto const &item : textureCoordinates) buff << item << ", ";
			buff << ")" << std::endl;

			return buff.str();
		}
	};
	
	class IIndexedFaceSetGeometry : public Geometry
	{
	protected:
		IIndexedFaceSetGeometry(std::string name) : Geometry(name, Entity::GEOMETRY_INDEXEDFACESET) {}

		virtual ~IIndexedFaceSetGeometry() {};
		
	public:
		virtual void setParameters(std::string groupName, ape::GeometryCoordinates coordinates, ape::GeometryIndices indices, ape::GeometryNormals normals, ape::GeometryTangents tangents, bool generateNormals, ape::GeometryColors colors, ape::GeometryTextureCoordinates textureCoordinates, ape::MaterialWeakPtr material , ape::GeometryFaces faces) = 0;
		
		virtual ape::GeometryIndexedFaceSetParameters getParameters() = 0;

		virtual void setParentNode(ape::NodeWeakPtr parentNode) = 0;

		virtual ape::MaterialWeakPtr getMaterial() = 0;

		virtual bool getHasNormals() = 0;

		virtual bool getHasTextureCoords() = 0;

		virtual bool getHasVertexColors() = 0;

		virtual void setHasNormals(bool hasnormas) = 0;

		virtual void setHasTextureCoords(bool hasTC) = 0;

		virtual void setHasVertexColors(bool hasVC) = 0;

		virtual bool getHasTangents() = 0;

		virtual void setHasTangents(bool hastangents) = 0;

		virtual void setUvs(std::vector<ape::Vector3> &Uvs) = 0;

		virtual std::vector<ape::Vector3> getUvs() = 0;

		virtual void setCols(ape::Vector4* &s) = 0;

		virtual ape::Vector4* getCols() = 0;

		virtual void setIndex(int indx) = 0;

		virtual int getIndex() = 0;

		virtual void attachDataBlock() = 0;
	};
}

#endif

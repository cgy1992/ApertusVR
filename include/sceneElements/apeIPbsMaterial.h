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

#ifndef APE_IPBSPASS_H
#define APE_IPBSPASS_H

#include <string>
#include <vector>
#include "ape.h"
#include "datatypes/apeColor.h"
#include "datatypes/apeEntity.h"
#include "datatypes/apeMaterial.h"
#include "datatypes/apeTexture.h"

namespace ape
{
	class	IPbsMaterial : public Material
	{
	protected:
		IPbsMaterial(std::string name) : Material(name, Entity::MATERIAL_PBS) {}

		virtual ~IPbsMaterial() {};

		ape::Color mDiffuseColor;

		ape::Color mEmissiveColor;

		ape::Color mSpecularColor;

		float mMetalness;

		float mBaseColor;

	public:
		//virtual void setAlbedo(ape::Color albedo) = 0;

		virtual void setRoughness(float roughness) = 0;

		//virtual void setLightRoughnessOffset(float lightRoughnessOffset) = 0;

		//virtual void setF0(ape::Color f0) = 0;

		//virtual ape::Color getAlbedo() = 0;

		virtual float getRoughness() = 0;

		//virtual float getLightRoughnessOffset() = 0;

		//virtual ape::Color getF0() = 0;

		virtual void setDiffuseColor(Color diffuse) = 0;

		virtual ape::Color getDiffuseColor() = 0;

		virtual void setSpecularColor(Color specular) = 0;

		//virtual void setAmbientColor(Color ambient) = 0;

		virtual void setEmissiveColor(Color emissive) = 0;

		virtual ape::Color getEmissiveColor() = 0;

		virtual void setAlphaMode(std::string alphaMode) = 0;

		virtual std::string getAlphaMode() = 0;

		virtual void setAlphaCutoff(float alphaCutoff) = 0;

		virtual float getAlphaCutoff() = 0;

		virtual void setMetallicRoughnessTexture(std::string path) = 0;

		virtual std::string getMetallicRoughnessTexture() = 0;

		virtual void setBaseColorTexture(std::string path) = 0;

		virtual std::string getBaseColorTexture() = 0;

		virtual void setNormalTexture(std::string path) = 0;

		virtual std::string getNormalTexture() = 0;


		//virtual void setShininess(float shininess) = 0;

		virtual void setMetalness(float MetallicRoughness) = 0;

		virtual float getMetalness() = 0;

		virtual void setBaseColor(float MetallicRoughness) = 0;

		virtual float getBaseColor() = 0;
	};
}

#endif

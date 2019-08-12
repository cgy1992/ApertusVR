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

#ifndef APE_PBSMATERIALIMPL_H
#define APE_PBSMATERIALIMPL_H

#include "managers/apeISceneManager.h"
#include "sceneelements/apeINode.h"
#include "sceneelements/apeIPbsMaterial.h"
#include "apeEventManagerImpl.h"
#include "apeReplica.h"

namespace ape
{
	class PbsMaterialImpl : public ape::IPbsMaterial, public ape::Replica
	{
	public:
		PbsMaterialImpl(std::string name, bool isHostCreated);

		~PbsMaterialImpl();

		void setShadingMode(std::string shadingMode) override;

		std::string getShadingMode() override;

		/*void setAlbedo(ape::Color albedo) override;*/

		void setRoughness(float roughness) override;

		/*void setLightRoughnessOffset(float lightRoughnessOffset) override;

		void setF0(ape::Color f0) override;

		ape::Color getAlbedo() override;*/

		float getRoughness() override;

		/*float getLightRoughnessOffset() override;

		ape::Color getF0() override;*/

		void setDiffuseColor(ape::Color diffuse) override;

		ape::Color getDiffuseColor() override;

		void setSpecularColor(ape::Color specular) override;

		void setAmbientColor(ape::Color ambient) override;

		void setEmissiveColor(ape::Color emissive) override;

		ape::Color getSpecularColor() override;

		ape::Color getAmbientColor() override;

		ape::Color getEmissiveColor() override;

		void setPath(std::string path) override;

		std::string getPath() override;

		void setShininess(float shininess) override;

		float getShininess() override;

		virtual void setAlphaMode(std::string alphaMode)override;

		virtual std::string getAlphaMode() override;

		virtual void setAlphaCutoff(float alphaCutoff) override;

		virtual float getAlphaCutoff() override;

		void setMetalness(float Metalness) override;

		float getMetalness() override;

		void setBaseColor(float MetallicRoughness) override;

		float getBaseColor() override;

		void setMetallicRoughnessTexture(std::string path) override;

		std::string getMetallicRoughnessTexture() override;

		void setBaseColorTexture(std::string path) override;

		std::string getBaseColorTexture() override;

		void setNormalTexture(std::string path) override;

		std::string getNormalTexture() override;

		void WriteAllocationID(RakNet::Connection_RM3 *destinationConnection, RakNet::BitStream *allocationIdBitstream) const override;

		RakNet::RM3SerializationResult Serialize(RakNet::SerializeParameters *serializeParameters) override;

		void Deserialize(RakNet::DeserializeParameters *deserializeParameters) override;



	private:
		ape::EventManagerImpl* mpEventManagerImpl;

		ape::ISceneManager* mpSceneManager;

		ape::Color mAlbedo;

		float mRoughness;

		float mLightRoughnessOffset;

		float mAlphaCutoff;

		ape::Color mF0;

		std::string mAlphaMode;

		std::string mMetallicRoughnessTexture;

		std::string mBaseColorTexture;

		std::string mNormalTexture;

		std::string mShadingMode;

		ape::Color mAmbientColor;

		float mShininess;

		std::string mPath;
	};
}

#endif

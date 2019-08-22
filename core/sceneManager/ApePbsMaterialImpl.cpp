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

#include "apePbsMaterialImpl.h"

ape::PbsMaterialImpl::PbsMaterialImpl(std::string name, bool isHostCreated) : ape::IPbsMaterial(name), ape::Replica("PbsPass", isHostCreated)
{
	mpEventManagerImpl = ((ape::EventManagerImpl*)ape::IEventManager::getSingletonPtr());
	mpSceneManager = ape::ISceneManager::getSingletonPtr();
	mAlbedo = ape::Color();
	mRoughness = 0.0f;
	mLightRoughnessOffset = 0.0f;
	mF0 = ape::Color();
	mMetalness = 0.0f;
	mBaseColor = 0.0f;
}

ape::PbsMaterialImpl::~PbsMaterialImpl()
{
	
}

void ape::PbsMaterialImpl::setDiffuseColor(ape::Color diffuse)
{
	mDiffuseColor = diffuse;
	mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_DIFFUSE));
}
ape::Color ape::PbsMaterialImpl::getDiffuseColor()
{
	return mDiffuseColor;
}

void ape::PbsMaterialImpl::setSpecularColor(ape::Color specular) 
{
	mSpecularColor = specular;
	mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_SPECULAR));
}

void ape::PbsMaterialImpl::setAmbientColor(ape::Color ambient) // ninics
{
	mAmbientColor = ambient;
	mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_AMBIENT));
}

void ape::PbsMaterialImpl::setEmissiveColor(ape::Color emissive) // not color ()
{
	mEmissiveColor = emissive;
	mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_EMISSIVE));
}

ape::Color ape::PbsMaterialImpl::getEmissiveColor() // not color ()
{
	return mEmissiveColor;
}

void ape::PbsMaterialImpl::setAlphaMode(std::string alphaMode)
{
	mAlphaMode = alphaMode;
	mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_ALPHAMODE));
}
std::string ape::PbsMaterialImpl::getAlphaMode()
{
	return mAlphaMode;
}

void ape::PbsMaterialImpl::setAlphaCutoff(float alphaCutoff)
{
	mAlphaCutoff = alphaCutoff;
	mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_ALPHACUTOFF));
}
float ape::PbsMaterialImpl::getAlphaCutoff()
{
	return mAlphaCutoff;
}

void ape::PbsMaterialImpl::setMetallicRoughnessTexture(std::string path)
{
	mMetallicRoughnessTexture = path;
	mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_METALLICROUGHNESS_TEXTURE));
}

std::string ape::PbsMaterialImpl::getMetallicRoughnessTexture()
{
	return mMetallicRoughnessTexture;
}

void ape::PbsMaterialImpl::setBaseColorTexture(std::string path)
{
	mBaseColorTexture = path;
	mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_BASECOLOR_TEXTURE));
}

std::string ape::PbsMaterialImpl::getBaseColorTexture()
{
	return mBaseColorTexture;
}

void ape::PbsMaterialImpl::setNormalTexture(std::string path)
{
	mNormalTexture = path;
	mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_NORMAL_TEXTURE));
}

std::string ape::PbsMaterialImpl::getNormalTexture()
{
	return mNormalTexture;
}

void ape::PbsMaterialImpl::setEmissiveTexture(std::string path)
{
	mEmissiveTexture = path;
	mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_EMISSIVE_TEXTURE));
}

std::string ape::PbsMaterialImpl::getEmissiveTexture()
{
	return mEmissiveTexture;
}

void ape::PbsMaterialImpl::setShininess(float shininess)
{
	mShininess = shininess;
	mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_SHININESS));
}

float ape::PbsMaterialImpl::getShininess()
{
	return mShininess;
}

ape::Color ape::PbsMaterialImpl::getSpecularColor()
{
	return mSpecularColor;
}

ape::Color ape::PbsMaterialImpl::getAmbientColor()
{
	return mAmbientColor;
}

void ape::PbsMaterialImpl::setPath(std::string path)
{
	mPath = path;
}

std::string ape::PbsMaterialImpl::getPath()
{
	return mPath;
}

void ape::PbsMaterialImpl::setReflection(std::string ref)
{
	mReflection = ref;
	mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_REFLECTION));
}

std::string ape::PbsMaterialImpl::getReflection()
{
	return mReflection;
}

//void ape::PbsMaterialImpl::setAlbedo(ape::Color albedo) // nincs
//{
//	mAlbedo = albedo;
//	mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_ALBEDO));
//}
//
void ape::PbsMaterialImpl::setRoughness(float roughness)
{
	mRoughness = roughness;
	mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_ROUGHNESS));
}
//
//void ape::PbsMaterialImpl::setLightRoughnessOffset(float lightRoughnessOffset) // nincs
//{
//	mLightRoughnessOffset = lightRoughnessOffset;
//	mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_LIGHTROUGHNESSOFFSET));
//}
//
void ape::PbsMaterialImpl::setF0(ape::Color f0)
{
	mF0 = f0;
	mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_F0));
}
//
//
//ape::Color ape::PbsMaterialImpl::getAlbedo() // nincs
//{
//	return mAlbedo;
//}
//
float ape::PbsMaterialImpl::getRoughness()
{
	return mRoughness;
}
//
//float ape::PbsMaterialImpl::getLightRoughnessOffset()//nincs
//{
//	return mLightRoughnessOffset;
//}
//
ape::Color ape::PbsMaterialImpl::getF0()
{
	return mF0;
}

void ape::PbsMaterialImpl::setShadingMode(std::string shadingMode)
{
	mShadingMode = shadingMode;
	mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_SHADINGMODE));
}

std::string ape::PbsMaterialImpl::getShadingMode()
{
	return mShadingMode;
}


void ape::PbsMaterialImpl::setMetalness(float metalness)
{
	mMetalness = metalness;
	mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_METALNESS));
}

float ape::PbsMaterialImpl::getMetalness()
{
	return mMetalness;
}
void ape::PbsMaterialImpl::setBaseColor(float basecolor)
{
	mBaseColor = basecolor;
	mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_BASECOLOR));
}

float ape::PbsMaterialImpl::getBaseColor()
{
	return mBaseColor;
}


void ape::PbsMaterialImpl::WriteAllocationID(RakNet::Connection_RM3 *destinationConnection, RakNet::BitStream *allocationIdBitstream) const
{
	allocationIdBitstream->Write(mObjectType);
	allocationIdBitstream->Write(RakNet::RakString(mName.c_str()));
}

RakNet::RM3SerializationResult ape::PbsMaterialImpl::Serialize(RakNet::SerializeParameters *serializeParameters)
{
	RakNet::VariableDeltaSerializer::SerializationContext serializationContext;
	serializeParameters->pro[0].reliability = RELIABLE_ORDERED;
	mVariableDeltaSerializer.BeginIdenticalSerialize(&serializationContext, serializeParameters->whenLastSerialized == 0, &serializeParameters->outputBitstream[0]);
	mVariableDeltaSerializer.SerializeVariable(&serializationContext, mAmbientColor);
	mVariableDeltaSerializer.SerializeVariable(&serializationContext, mDiffuseColor);
	mVariableDeltaSerializer.SerializeVariable(&serializationContext, mSpecularColor);
	mVariableDeltaSerializer.SerializeVariable(&serializationContext, mEmissiveColor);
	mVariableDeltaSerializer.SerializeVariable(&serializationContext, mShininess);
	mVariableDeltaSerializer.SerializeVariable(&serializationContext, mAlbedo);
	mVariableDeltaSerializer.SerializeVariable(&serializationContext, mRoughness);
	mVariableDeltaSerializer.SerializeVariable(&serializationContext, mLightRoughnessOffset);
	mVariableDeltaSerializer.SerializeVariable(&serializationContext, mF0);
	mVariableDeltaSerializer.EndSerialize(&serializationContext);
	return RakNet::RM3SR_BROADCAST_IDENTICALLY_FORCE_SERIALIZATION;
}

void ape::PbsMaterialImpl::Deserialize(RakNet::DeserializeParameters *deserializeParameters)
{
	RakNet::VariableDeltaSerializer::DeserializationContext deserializationContext;
	mVariableDeltaSerializer.BeginDeserialize(&deserializationContext, &deserializeParameters->serializationBitstream[0]);
	if (mVariableDeltaSerializer.DeserializeVariable(&deserializationContext, mAmbientColor))
		mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_AMBIENT));
	if (mVariableDeltaSerializer.DeserializeVariable(&deserializationContext, mDiffuseColor))
		mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_DIFFUSE));
	if (mVariableDeltaSerializer.DeserializeVariable(&deserializationContext, mSpecularColor))
		mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_SPECULAR));
	if (mVariableDeltaSerializer.DeserializeVariable(&deserializationContext, mEmissiveColor))
		mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_EMISSIVE));
	if (mVariableDeltaSerializer.DeserializeVariable(&deserializationContext, mShininess))
		mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_SHININESS));
	if (mVariableDeltaSerializer.DeserializeVariable(&deserializationContext, mAlbedo))
		mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_ALBEDO));
	if (mVariableDeltaSerializer.DeserializeVariable(&deserializationContext, mRoughness))
		mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_ROUGHNESS));
	if (mVariableDeltaSerializer.DeserializeVariable(&deserializationContext, mLightRoughnessOffset))
		mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_LIGHTROUGHNESSOFFSET));
	if (mVariableDeltaSerializer.DeserializeVariable(&deserializationContext, mF0))
		mpEventManagerImpl->fireEvent(ape::Event(mName, ape::Event::Type::MATERIAL_PBS_F0));
	mVariableDeltaSerializer.EndDeserialize(&deserializationContext);
}



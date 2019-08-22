#include "apeAssimpAssetLoaderPlugin.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

ape::AssimpAssetLoaderPlugin::AssimpAssetLoaderPlugin()
{
	APE_LOG_FUNC_ENTER();
	mpSceneManager = ape::ISceneManager::getSingletonPtr();
	mpEventManager = ape::IEventManager::getSingletonPtr();
	mpCoreConfig = ape::ICoreConfig::getSingletonPtr();
	mpAssimpImporter = nullptr;
	mAssimpScenes = std::vector<const aiScene*>();
	mAssimpAssetConfigs = std::vector<AssetConfig>();
	std::srand(std::time(0));
	mObjectCount = 0;
	mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_FILE, std::bind(&AssimpAssetLoaderPlugin::eventCallBack, this, std::placeholders::_1));
	mAssetCount = 0;
	APE_LOG_FUNC_LEAVE();
}

ape::AssimpAssetLoaderPlugin::~AssimpAssetLoaderPlugin()
{
	APE_LOG_FUNC_ENTER();
	mpEventManager->disconnectEvent(ape::Event::Group::GEOMETRY_FILE, std::bind(&AssimpAssetLoaderPlugin::eventCallBack, this, std::placeholders::_1));
	APE_LOG_FUNC_LEAVE();
}

void ape::AssimpAssetLoaderPlugin::Init()
{
	APE_LOG_FUNC_ENTER();
	mpAssimpImporter = new Assimp::Importer();
	APE_LOG_FUNC_LEAVE();
}

void ape::AssimpAssetLoaderPlugin::Run()
{
	APE_LOG_FUNC_ENTER();
	loadConfig();
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	APE_LOG_FUNC_LEAVE();
}

void ape::AssimpAssetLoaderPlugin::Step()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

void ape::AssimpAssetLoaderPlugin::Stop()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

void ape::AssimpAssetLoaderPlugin::Suspend()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

void ape::AssimpAssetLoaderPlugin::Restart()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

void ape::AssimpAssetLoaderPlugin::eventCallBack(const ape::Event & event)
{
	if (event.type == ape::Event::Type::GEOMETRY_FILE_FILENAME)
	{
		if (auto fileGeometry = std::static_pointer_cast<ape::IFileGeometry>(mpSceneManager->getEntity(event.subjectName).lock()))
		{
			APE_LOG_DEBUG("GEOMETRY_FILE_FILENAME: subjectName: " << event.subjectName);
			APE_LOG_DEBUG("GEOMETRY_FILE_FILENAME: fileName: " << fileGeometry->getFileName());
			AssetConfig assetConfig;
			assetConfig.mergeAndExportMeshes = false;
			assetConfig.regenerateNormals = false;
			if (auto rootNode = fileGeometry->getParentNode().lock())
			{
				assetConfig.rootNodeName = rootNode->getName();
				APE_LOG_DEBUG("rootNodeName " << assetConfig.rootNodeName);
				assetConfig.scale = rootNode->getScale();
				assetConfig.position = rootNode->getPosition();
				assetConfig.orientation = rootNode->getOrientation();
			}
			assetConfig.file = fileGeometry->getFileName();
			mAssimpAssetConfigs.push_back(assetConfig);
			readFile(fileGeometry->getFileName());
		}
	}
}

void ape::AssimpAssetLoaderPlugin::createNode(int assimpSceneID, aiNode* assimpNode)
{
	APE_LOG_FUNC_ENTER();
	mObjectCount++;
	aiMatrix4x4 nodeTransformation = assimpNode->mTransformation;
	aiVector3t<float> scaling;
	aiQuaterniont<float> rotation;
	aiVector3t<float> position;
	nodeTransformation.Decompose(scaling, rotation, position);
	std::stringstream nodeUniqueName;
	std::string assimpNodeOriginalName = assimpNode->mName.C_Str();
	nodeUniqueName << assimpNode->mName.C_Str() << "_" << mObjectCount;
	std::string escapedNodeName = nodeUniqueName.str();
	escapedNodeName.erase(std::remove(escapedNodeName.begin(), escapedNodeName.end(), '<'), escapedNodeName.end());
	escapedNodeName.erase(std::remove(escapedNodeName.begin(), escapedNodeName.end(), '>'), escapedNodeName.end());
	assimpNode->mName = escapedNodeName;
	computeNodesDerivedTransform(mAssimpScenes[assimpSceneID], mAssimpScenes[assimpSceneID]->mRootNode, mAssimpScenes[assimpSceneID]->mRootNode->mTransformation);
	if (auto node = mpSceneManager->createNode(escapedNodeName).lock())
	{
		auto parentNode = ape::NodeWeakPtr();
		if (assimpNode->mParent)
		{
			parentNode = mpSceneManager->getNode(assimpNode->mParent->mName.C_Str());
			if (parentNode.lock())
				node->setParentNode(parentNode);
		}
		node->setPosition(ape::Vector3(position.x, position.y, position.z));
		node->setOrientation(ape::Quaternion(rotation.w, rotation.x, rotation.y, rotation.z));
		node->setScale(ape::Vector3(scaling.x, scaling.y, scaling.z));

		//APE_LOG_DEBUG("nodeName: " << node->getName());
		for (int i = 0; i < assimpNode->mNumMeshes; i++)
		{

			int indx = i;
			mObjectCount++;
			aiMesh* assimpMesh = mAssimpScenes[assimpSceneID]->mMeshes[assimpNode->mMeshes[i]];
			std::stringstream meshUniqueName;
			meshUniqueName << assimpNodeOriginalName << "_" << mObjectCount;
			assimpMesh->mName = meshUniqueName.str();
			//			
			const aiMaterial *pAIMaterial = mAssimpScenes[assimpSceneID]->mMaterials[assimpMesh->mMaterialIndex];
			//
			if (auto mesh = std::static_pointer_cast<ape::IIndexedFaceSetGeometry>(mpSceneManager->createEntity(meshUniqueName.str(), ape::Entity::GEOMETRY_INDEXEDFACESET).lock()))
			{
				ape::GeometryFaces faces = ape::GeometryFaces();
				faces.faceVectors.resize(assimpMesh->mNumVertices);
				ape::GeometryCoordinates coordinates = ape::GeometryCoordinates();
				for (int i = 0; i < assimpMesh->mNumVertices; i++)
				{
					aiVector3D assimpVertex = assimpMesh->mVertices[i];
					ape::Vector3 vertexPosition(assimpVertex.x, assimpVertex.y, assimpVertex.z);
					faces.faceVectors[i].x = assimpVertex.x;
					faces.faceVectors[i].y = assimpVertex.y;
					faces.faceVectors[i].z = assimpVertex.z;
					if (mAssimpAssetConfigs[assimpSceneID].mergeAndExportMeshes)
						vertexPosition = (node->getDerivedPosition() + (node->getDerivedOrientation() * vertexPosition)) * mAssimpAssetConfigs[assimpSceneID].scale;
					coordinates.push_back(vertexPosition.x);
					coordinates.push_back(vertexPosition.y);
					coordinates.push_back(vertexPosition.z);
				}
				ape::GeometryIndices indices = ape::GeometryIndices();
				for (int i = 0; i < assimpMesh->mNumFaces; i++)
				{
					aiFace assimpFace = assimpMesh->mFaces[i];
					for (int i = 0; i < assimpFace.mNumIndices; i++)
						indices.push_back(assimpFace.mIndices[i]); 
				//	indices.push_back(-1);
				}


				faces.face.resize(assimpMesh->mNumFaces);
				for (int i = 0; i < assimpMesh->mNumFaces; i++)
				{
					aiFace assimpFace = assimpMesh->mFaces[i];
					faces.face[i].resize(assimpFace.mNumIndices);
					for (int j = 0; j < assimpFace.mNumIndices; j++)
					{
						
						faces.face[i][j] = assimpFace.mIndices[j];
					}
						
					//indices.push_back(-1);
				}

				mesh->setIndex(indx);

				mesh->setHasNormals(assimpMesh->HasNormals());

				mesh->setHasTextureCoords(assimpMesh->HasTextureCoords(0));

				mesh->setHasVertexColors(assimpMesh->HasVertexColors(0));

				mesh->setHasTangents(assimpMesh->HasTangentsAndBitangents());

				if (assimpMesh->HasTextureCoords(0))
				{
					aiVector3D *uv = assimpMesh->mTextureCoords[0];
					std::vector<ape::Vector3> Vec;
					Vec.resize(assimpMesh->mNumVertices);
					
					//for (int i = 0; i < Vec.size(); i+=4)
					//{
					//	if (i % 8 == 0)
					//	{
					//		Vec[i + 0].x = 0;
					//		Vec[i + 0].y = 1;
					//		Vec[i + 1].x = 1;
					//		Vec[i + 1].y = 0;
					//		Vec[i + 2].x = 1;
					//		Vec[i + 2].y = 1;
					//		Vec[i + 3].x = 0;
					//		Vec[i + 3].y = 0;
					//	}
					//	else
					//	{
					//		Vec[i + 0].x = 0;
					//		Vec[i + 0].y = -1;
					//		Vec[i + 1].x = -1;
					//		Vec[i + 1].y = 0;
					//		Vec[i + 2].x = -1;
					//		Vec[i + 2].y = -1;
					//		Vec[i + 3].x = 0;
					//		Vec[i + 3].y = 0;
					//	}
					//	
					//}
					
					for (int i = 0; i < assimpMesh->mNumVertices; i++)
					{
						//uv[i].NormalizeSafe();
						//Vec[i] = new ape::Vector3(uv[i].x,uv[i].y,uv[i].z);
						//Vec[i].x = uv[i].x;
						//Vec[i].y = uv[i].y;
						//Vec[i].z = uv[i].z;
						Vec[i].x = assimpMesh->mTextureCoords[0][i].x;
						Vec[i].y = assimpMesh->mTextureCoords[0][i].y;
						Vec[i].z = assimpMesh->mTextureCoords[0][i].z;
					}
					//apeuv = Vec[0];
					//ape::Vector3 *apeuv = Vec[0];
					mesh->setUvs(Vec);
				}


				
				if (assimpMesh->HasVertexColors(0))
				{
					aiColor4D *col = assimpMesh->mColors[0];
					std::vector<ape::Vector4*> Col;
					Col.resize(assimpMesh->mNumVertices);
					for (int i = 0; i < Col.size(); i++)
					{
						Col[i] = new ape::Vector4();
					}
					ape::Vector4 *apeCol = Col[0];
					for (int i = 0; i < assimpMesh->mNumVertices; i++)
					{
						apeCol[i].x = col[i].r;
						apeCol[i].y = col[i].g;
						apeCol[i].z = col[i].b;
					}
					mesh->setCols(apeCol);
				}







				aiMaterial* asssimpMaterial = mAssimpScenes[assimpSceneID]->mMaterials[assimpMesh->mMaterialIndex];
				aiString materialName;
				asssimpMaterial->Get(AI_MATKEY_NAME, materialName);
				std::string modifiedMaterialName = materialName.C_Str();
				modifiedMaterialName += mAssimpAssetConfigs[assimpSceneID].file.substr(mAssimpAssetConfigs[assimpSceneID].file.find_last_of("/\\"));
				modifiedMaterialName.erase(std::remove(modifiedMaterialName.begin(), modifiedMaterialName.end(), '/'), modifiedMaterialName.end());
				modifiedMaterialName.erase(std::remove(modifiedMaterialName.begin(), modifiedMaterialName.end(), '/\\'), modifiedMaterialName.end());
				modifiedMaterialName.erase(std::remove(modifiedMaterialName.begin(), modifiedMaterialName.end(), ':'), modifiedMaterialName.end());
				modifiedMaterialName.erase(std::remove(modifiedMaterialName.begin(), modifiedMaterialName.end(), ','), modifiedMaterialName.end());
				modifiedMaterialName.erase(std::remove(modifiedMaterialName.begin(), modifiedMaterialName.end(), '<'), modifiedMaterialName.end());
				modifiedMaterialName.erase(std::remove(modifiedMaterialName.begin(), modifiedMaterialName.end(), '>'), modifiedMaterialName.end());

				auto material = std::static_pointer_cast<ape::IPbsMaterial>(mpSceneManager->getEntity(modifiedMaterialName).lock());
				std::string diffuseTextureFileName = std::string();
				if (!material)
				{
					material = std::static_pointer_cast<ape::IPbsMaterial>(mpSceneManager->createEntity(modifiedMaterialName, ape::Entity::MATERIAL_PBS).lock());
					aiColor3D colorDiffuse(0.0f, 0.0f, 0.0f);
					asssimpMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, colorDiffuse);
					float opacity = 1.0f;
					asssimpMaterial->Get(AI_MATKEY_OPACITY, opacity);
					aiColor3D colorSpecular(0.0f, 0.0f, 0.0f);
					asssimpMaterial->Get(AI_MATKEY_COLOR_SPECULAR, colorSpecular);
					aiColor3D colorAmbient(0.0f, 0.0f, 0.0f);
					asssimpMaterial->Get(AI_MATKEY_COLOR_AMBIENT, colorAmbient);
					aiColor3D colorEmissive(0.0f, 0.0f, 0.0f);
					asssimpMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, colorEmissive);
					aiColor3D colorTransparent(0.0f, 0.0f, 0.0f);
					asssimpMaterial->Get(AI_MATKEY_COLOR_TRANSPARENT, colorTransparent);
					int sceneBlendingType = 0;
					asssimpMaterial->Get(AI_MATKEY_BLEND_FUNC, sceneBlendingType);
					float metalness = 0.0;
					asssimpMaterial->Get(AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_METALLIC_FACTOR, metalness);
					float roughness = 0.0;
					asssimpMaterial->Get(AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_ROUGHNESS_FACTOR, roughness);	
					//float baseColor = 0.0;
					//asssimpMaterial->Get(AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_BASE_COLOR_FACTOR, baseColor);//nemtom
					aiString alphaMode;
					asssimpMaterial->Get(AI_MATKEY_GLTF_ALPHAMODE, alphaMode);

					//material->setBaseColorTexture(fileBaseColor.C_Str());
					//material->setMetallicRoughnessTexture(fileMetallicRoughness.C_Str());

					material->setMetalness(metalness);
					material->setRoughness(roughness);
					//material->setBaseColor(baseColor);
					material->setAlphaMode(alphaMode.C_Str());

					


					if (asssimpMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
					{
						aiString path;
						asssimpMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path);
						diffuseTextureFileName = path.data;
					}
					if (!colorDiffuse.IsBlack())
						material->setDiffuseColor(ape::Color(colorDiffuse.r, colorDiffuse.g, colorDiffuse.b, opacity));
					if (!colorSpecular.IsBlack())
						material->setSpecularColor(ape::Color(colorSpecular.r, colorSpecular.g, colorSpecular.b, opacity));
					//if (!colorAmbient.IsBlack())
					//	material->setAmbientColor(ape::Color(colorAmbient.r, colorAmbient.g, colorAmbient.b));
					if (!colorEmissive.IsBlack())
						material->setEmissiveColor(ape::Color(colorEmissive.r, colorEmissive.g, colorEmissive.b));


					if (sceneBlendingType == aiBlendMode_Additive)
					{
						//material->setSceneBlending(ape::Pass::SceneBlendingType::ADD);
						////APE_LOG_DEBUG("blending ADD: " << opacity);
					}
					else if (sceneBlendingType == aiBlendMode_Default)
					{
						if (opacity < 0.99)
						{
							//material->setSceneBlending(ape::Pass::SceneBlendingType::TRANSPARENT_ALPHA);
							////APE_LOG_DEBUG("blending TRANSPARENT_ALPHA: " << opacity);
						}
						else
						{
							//material->setSceneBlending(ape::Pass::SceneBlendingType::REPLACE);
							////APE_LOG_DEBUG("blending REPLACE: " << opacity);
						}
					}
					//material->setBaseColor(baseColor);
					aiString MetRough;
					/*asssimpMaterial->GetTexture(aiTextureType_UNKNOWN, 0, &MetRough);fölös
					material->setMetallicRoughnessTexture(MetRough.C_Str());*/
					aiString fileBaseColor, fileMetallicRoughness;
					asssimpMaterial->GetTexture(AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_METALLICROUGHNESS_TEXTURE, &fileMetallicRoughness);
					//std::cout <<fileMetallicRoughness.C_Str() << std::endl;
					asssimpMaterial->GetTexture(AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_BASE_COLOR_TEXTURE, &fileBaseColor);
					//asssimpMaterial->GetTexture(AI_MATKEY_TEXTURE_NORMALS, &fileNormalTex);
					/*enum aiTextureType type = aiTextureType_DIFFUSE;
					aiString path;
					asssimpMaterial->GetTexture(type, 0, &path);
					material->setPath(path.C_Str());*/
					aiString reflection;
					asssimpMaterial->GetTexture(aiTextureType_REFLECTION, 0, &reflection);
					material->setReflection(reflection.C_Str());
					aiString emissiveTex;
					asssimpMaterial->GetTexture(aiTextureType_EMISSIVE, 0, &emissiveTex);
					aiString normalTex;
					asssimpMaterial->GetTexture(aiTextureType_EMISSIVE, 0, &normalTex);
					/*aiString emissiveTex;
					asssimpMaterial->GetTexture(aiTextureType_EMISSIVE, 0, &emissiveTex);*/

					if (fileBaseColor.length > 0)
						material->setBaseColorTexture(fileBaseColor.C_Str());
					if (fileMetallicRoughness.length > 0)
						material->setMetallicRoughnessTexture(fileMetallicRoughness.C_Str());
					if (normalTex.length > 0)
						material->setNormalTexture(normalTex.C_Str());
					if (emissiveTex.length > 0)
						material->setEmissiveTexture(emissiveTex.C_Str());
					


					//APE_LOG_DEBUG("createManualMaterial: " << material->getName());
				}
				ape::GeometryNormals normals = ape::GeometryNormals();
				if (assimpMesh->HasNormals() && !mAssimpAssetConfigs[assimpSceneID].regenerateNormals)
				{
					for (int i = 0; i < assimpMesh->mNumVertices; i++)
					{
						aiVector3D assimpNormal = assimpMesh->mNormals[i];
						
						normals.push_back(assimpNormal.x);
						normals.push_back(assimpNormal.y);
						normals.push_back(assimpNormal.z);
					}
					//APE_LOG_DEBUG("hasNormal: " << assimpMesh->mName.C_Str());
				}
				ape::GeometryTangents tangents = ape::GeometryTangents();
				if (assimpMesh->HasTangentsAndBitangents()) //assume that we have corretc tangents in file
				{
					for (int i = 0; i < assimpMesh->mNumVertices; i++)
					{
						aiVector3D assimpTangent = assimpMesh->mTangents[i];
						
						tangents.push_back(assimpTangent.x);
						tangents.push_back(assimpTangent.y);
						tangents.push_back(assimpTangent.z);
					}
					//APE_LOG_DEBUG("hasNormal: " << assimpMesh->mName.C_Str());
				}
				ape::GeometryColors colors = ape::GeometryColors();
				for (int colorSetIndex = 0; colorSetIndex < AI_MAX_NUMBER_OF_COLOR_SETS; colorSetIndex++)
				{
					if (assimpMesh->HasVertexColors(colorSetIndex))
					{
						for (int vertexIndex = 0; vertexIndex < assimpMesh->mNumVertices; vertexIndex++)
						{
							aiColor4D assimpColor = assimpMesh->mColors[colorSetIndex][vertexIndex];
							colors.push_back(assimpColor.r);
							colors.push_back(assimpColor.g);
							colors.push_back(assimpColor.b);
							colors.push_back(assimpColor.a);
						}
						//APE_LOG_DEBUG("hasVertexColors: " << assimpMesh->mName.C_Str());
					}
				}
				ape::GeometryTextureCoordinates textureCoordinates = ape::GeometryTextureCoordinates();
				for (int textureCoordinatesSetIndex = 0; textureCoordinatesSetIndex < AI_MAX_NUMBER_OF_TEXTURECOORDS; textureCoordinatesSetIndex++)
				{
					if (assimpMesh->HasTextureCoords(textureCoordinatesSetIndex))
					{
						for (int textureCoordinatesIndex = 0; textureCoordinatesIndex < assimpMesh->mNumVertices; textureCoordinatesIndex++)
						{
							aiVector3D assimpTerxtureCoordinates = assimpMesh->mTextureCoords[textureCoordinatesSetIndex][textureCoordinatesIndex];
							textureCoordinates.push_back(assimpTerxtureCoordinates.x);
							textureCoordinates.push_back(1.0f - assimpTerxtureCoordinates.y);
						}
						//APE_LOG_DEBUG("HasTextureCoords: " << assimpMesh->mName.C_Str());
					}
				}
				std::string groupName = std::string();
				if (mAssimpAssetConfigs[assimpSceneID].mergeAndExportMeshes)
					groupName = mAssimpAssetConfigs[assimpSceneID].file;
				mesh->setParameters(groupName, coordinates, indices, normals, tangents, mAssimpAssetConfigs[assimpSceneID].regenerateNormals, colors, textureCoordinates, material, faces);
				if (textureCoordinates.size() && diffuseTextureFileName.length())
				{
					if (auto fileTexture = std::static_pointer_cast<ape::IFileTexture>(mpSceneManager->createEntity(diffuseTextureFileName, ape::Entity::Type::TEXTURE_FILE).lock()))
					{
						//fileTexture->setFileName(diffuseTextureFileName);
						//material->setNormalTexture(diffuseTextureFileName);
						//material->setPassTexture(fileTexture);
					}
				}
				/*//------ create the material ?
				std::ostringstream texname;
				aiString szPath;
				aiGetMaterialString(asssimpMaterial, AI_MATKEY_TEXTURE_DIFFUSE(0), &szPath);

				aiColor4D clr(1.0f, 1.0f, 1.0f, 1.0);
				aiGetMaterialColor(asssimpMaterial, AI_MATKEY_COLOR_AMBIENT, &clr);
				ape::Color ambient = ape::Color(clr.r, clr.g, clr.b);
				material->setAmbientColor(ambient);

				// diffuse
				clr = aiColor4D(1.0f, 1.0f, 1.0f, 1.0f);
				if (AI_SUCCESS == aiGetMaterialColor(asssimpMaterial, AI_MATKEY_COLOR_DIFFUSE, &clr))
				{
					ape::Color diffuse = ape::Color(clr.r, clr.g, clr.b, clr.a);
					material->setDiffuseColor(diffuse);
				}

				// specular
				clr = aiColor4D(1.0f, 1.0f, 1.0f, 1.0f);
				if (AI_SUCCESS == aiGetMaterialColor(asssimpMaterial, AI_MATKEY_COLOR_SPECULAR, &clr))
				{
					ape::Color specular = ape::Color(clr.r, clr.g, clr.b, clr.a);
					material->setSpecularColor(specular);
				}

				// emissive
				clr = aiColor4D(1.0f, 1.0f, 1.0f, 1.0f);
				if (AI_SUCCESS == aiGetMaterialColor(asssimpMaterial, AI_MATKEY_COLOR_EMISSIVE, &clr))
				{
					ape::Color emissive = ape::Color(clr.r, clr.g, clr.b);
					material->setEmissiveColor(emissive);
				}

				float fShininess;
				if (AI_SUCCESS == aiGetMaterialFloat(asssimpMaterial, AI_MATKEY_SHININESS, &fShininess))
				{
					material->setShininess(fShininess);
				}

				int shade = aiShadingMode_NoShading;
				if (AI_SUCCESS == asssimpMaterial->Get(AI_MATKEY_SHADING_MODEL, shade) && shade != aiShadingMode_NoShading)
				{
					switch (shade) {
					case aiShadingMode_Phong: // Phong shading mode was added to opengl and directx years ago to be ready for gpus to support it (in fixed function pipeline), but no gpus ever did, so it has never done anything. From directx 10 onwards it was removed again.
					case aiShadingMode_Gouraud:
						material->setShadingMode("SO_GOURAUD");
						break;
					case aiShadingMode_Flat:
						material->setShadingMode("SO_FLAT");
						break;
					default:
						break;
					}
				}
				*/
				//------
				

				mesh->attachDataBlock();
				if (!mAssimpAssetConfigs[assimpSceneID].mergeAndExportMeshes)
					mesh->setParentNode(node);
				APE_LOG_DEBUG("createIndexedFaceSetGeometry: " << mesh->getName());
				
			}
		}
	}
	for (int i = 0; i < assimpNode->mNumChildren; i++)
		createNode(assimpSceneID, assimpNode->mChildren[i]);
	APE_LOG_FUNC_LEAVE();
}

void ape::AssimpAssetLoaderPlugin::loadConfig()
{
	APE_LOG_FUNC_ENTER();
	std::stringstream fileFullPath;
	fileFullPath << mpCoreConfig->getConfigFolderPath() << "\\apeAssimpAssetLoaderPlugin.json";
	FILE* apeAssimpAssetLoaderConfigFile = std::fopen(fileFullPath.str().c_str(), "r");
	char readBuffer[65536];
	if (apeAssimpAssetLoaderConfigFile)
	{
		rapidjson::FileReadStream jsonFileReaderStream(apeAssimpAssetLoaderConfigFile, readBuffer, sizeof(readBuffer));
		rapidjson::Document jsonDocument;
		jsonDocument.ParseStream(jsonFileReaderStream);
		if (jsonDocument.IsObject())
		{
			rapidjson::Value& assets = jsonDocument["assets"];
			for (auto& asset : assets.GetArray())
			{
				AssetConfig assetConfig;
				for (rapidjson::Value::MemberIterator assetMemberIterator = asset.MemberBegin(); assetMemberIterator != asset.MemberEnd(); ++assetMemberIterator)
				{
					if (assetMemberIterator->name == "mergeAndExportMeshes")
						assetConfig.mergeAndExportMeshes = assetMemberIterator->value.GetBool();
					if (assetMemberIterator->name == "regenerateNormals")
						assetConfig.regenerateNormals = assetMemberIterator->value.GetBool();
					if (assetMemberIterator->name == "rootNodeName")
					{
						assetConfig.rootNodeName = assetMemberIterator->value.GetString();
						mpSceneManager->createNode(assetConfig.rootNodeName);
						APE_LOG_DEBUG("rootNodeName " << assetConfig.rootNodeName);
					}
					if (assetMemberIterator->name == "scale")
					{
						rapidjson::Value& scale = assetMemberIterator->value;
						assetConfig.scale.x = scale.GetArray()[0].GetFloat();
						assetConfig.scale.y = scale.GetArray()[1].GetFloat();
						assetConfig.scale.z = scale.GetArray()[2].GetFloat();
					}
					if (assetMemberIterator->name == "position")
					{
						rapidjson::Value& position = assetMemberIterator->value;
						assetConfig.position.x = position.GetArray()[0].GetFloat();
						assetConfig.position.y = position.GetArray()[1].GetFloat();
						assetConfig.position.z = position.GetArray()[2].GetFloat();
					}
					if (assetMemberIterator->name == "orientation")
					{
						rapidjson::Value& orientation = assetMemberIterator->value;
						assetConfig.orientation.w = orientation.GetArray()[0].GetFloat();
						assetConfig.orientation.x = orientation.GetArray()[1].GetFloat();
						assetConfig.orientation.y = orientation.GetArray()[2].GetFloat();
						assetConfig.orientation.z = orientation.GetArray()[3].GetFloat();
					}
					if (assetMemberIterator->name == "file")
					{
						std::stringstream assimpAssetFileNamePath;
						std::string resourceLocationStr = assetMemberIterator->value.GetString();
						std::size_t found = resourceLocationStr.find(":");
						if (found != std::string::npos)
						{
							assimpAssetFileNamePath << resourceLocationStr;
						}
						else
						{
							std::stringstream resourceLocationPath;
							resourceLocationPath << APE_SOURCE_DIR << resourceLocationStr;
							assimpAssetFileNamePath << resourceLocationPath.str();
						}
						assetConfig.file = assimpAssetFileNamePath.str();
						APE_LOG_DEBUG("assetConfig.file " << assetConfig.file);
						std::string fileName = assimpAssetFileNamePath.str().substr(assimpAssetFileNamePath.str().find_last_of("/\\") + 1);
						std::string fileExtension = assimpAssetFileNamePath.str().substr(assimpAssetFileNamePath.str().find_last_of("."));
						if (fileExtension == ".mesh")
						{
							if (auto node = mpSceneManager->createNode("node").lock())
							{
								if (auto meshFile = std::static_pointer_cast<ape::IFileGeometry>(mpSceneManager->createEntity(fileName, ape::Entity::GEOMETRY_FILE).lock()))
								{
									meshFile->setFileName(fileName);
									//meshFile->mergeSubMeshes();
									//TODO_apeAssimpAssetLoaderPlugin how to use it when static geomtery is created?
									meshFile->setParentNode(node);
									//TODO_apeAssimpAssetLoaderPlugin how to export the optimized mesh when static geomtery is created?
									//std::this_thread::sleep_for(std::chrono::milliseconds(20000));
									//meshFile->exportMesh();
								}
							}
						}
					}
				}
				mAssimpAssetConfigs.push_back(assetConfig);
				readFile(assetConfig.file);
			}
		}
		fclose(apeAssimpAssetLoaderConfigFile);
	}
	APE_LOG_FUNC_LEAVE();
}

void ape::AssimpAssetLoaderPlugin::readFile(std::string fileName)
{
	APE_LOG_FUNC_ENTER();
	std::lock_guard<std::mutex> guard(mMutex);
	if (mpAssimpImporter)
	{
		const aiScene* assimpScene = mpAssimpImporter->ReadFile(fileName, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType | aiProcess_FlipUVs | aiProcess_OptimizeMeshes | aiProcess_GenUVCoords | aiProcess_TransformUVCoords | aiProcess_GenSmoothNormals );
		if (!assimpScene)
		{
			APE_LOG_ERROR("Loading the asset " << fileName << " was failed due to: " << mpAssimpImporter->GetErrorString());
		}
		else
		{
			APE_LOG_DEBUG("Loading the asset " << fileName << " was started");
			mAssimpScenes.push_back(assimpScene);
			loadScene(assimpScene, mAssetCount);
			mAssetCount++;
		}
	}
	APE_LOG_FUNC_LEAVE();
}

void ape::AssimpAssetLoaderPlugin::loadScene(const aiScene* assimpScene, int ID)
{
	APE_LOG_FUNC_ENTER();
	if (assimpScene->mRootNode)
	{
		//APE_LOG_DEBUG("mNumMeshes: " << assimpScene->mNumMeshes);
		createNode(ID, assimpScene->mRootNode);
		if (auto assimpSceneRootNode = mpSceneManager->getNode(assimpScene->mRootNode->mName.C_Str()).lock())
		{
			APE_LOG_DEBUG("assimpSceneRootNode: " << assimpSceneRootNode->getName());
			if (mAssimpAssetConfigs[ID].mergeAndExportMeshes)
			{
				if (auto meshFile = std::static_pointer_cast<ape::IFileGeometry>(mpSceneManager->createEntity(mAssimpAssetConfigs[ID].file, ape::Entity::GEOMETRY_FILE).lock()))
				{
					meshFile->exportMesh();
					meshFile->setParentNode(assimpSceneRootNode);
					assimpSceneRootNode->setOrientation(ape::Quaternion(1, 0, 0, 0));
					APE_LOG_DEBUG("mergeAndExportMeshes: " << mAssimpAssetConfigs[ID].file);
				}
			}
			else
			{
				if (auto rootNode = mpSceneManager->getNode(mAssimpAssetConfigs[ID].rootNodeName).lock())
				{
					APE_LOG_DEBUG("setScale to " << mAssimpAssetConfigs[ID].scale.toString() << " setPosition to " << mAssimpAssetConfigs[ID].position.toString()
						<< " setOrientation to " << mAssimpAssetConfigs[ID].orientation.toString());
					rootNode->setScale(mAssimpAssetConfigs[ID].scale);
					rootNode->setOrientation(mAssimpAssetConfigs[ID].orientation);
					rootNode->setPosition(mAssimpAssetConfigs[ID].position);
					assimpSceneRootNode->setParentNode(rootNode);
				}
				else
				{
					APE_LOG_DEBUG("rootNode was not found by name: " << mAssimpAssetConfigs[ID].rootNodeName);
				}
			}
		}
	}
	APE_LOG_FUNC_LEAVE();
}

void ape::AssimpAssetLoaderPlugin::computeNodesDerivedTransform(const aiScene* scene, const aiNode *node, const aiMatrix4x4 accTransf)
{
	if (mDerivedTransformsByName.find(node->mName.data) == mDerivedTransformsByName.end())
	{
		mDerivedTransformsByName[node->mName.data] = accTransf;
	}
	for (unsigned int childIdx = 0; childIdx < node->mNumChildren; ++childIdx)
	{
		const aiNode *pChildNode = node->mChildren[childIdx];
		computeNodesDerivedTransform(scene, pChildNode, accTransf * pChildNode->mTransformation);
	}
}

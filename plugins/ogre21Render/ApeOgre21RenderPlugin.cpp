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

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filewritestream.h"
#include "ApeOgre21RenderPlugin.h"
//#include "apeOgreUtilities.h"


ape::Ogre21RenderPlugin::Ogre21RenderPlugin() //constructor
{

	APE_LOG_FUNC_ENTER();
	mpSceneManager = ape::ISceneManager::getSingletonPtr();
	mpCoreConfig = ape::ICoreConfig::getSingletonPtr();
	//mpMainWindow = ape::IMainWindow::getSingletonPtr(); -> itt is mást kell
	mEventDoubleQueue = ape::DoubleQueue<Event>();
	mpEventManager = ape::IEventManager::getSingletonPtr();
	mpEventManager->connectEvent(ape::Event::Group::NODE, std::bind(&Ogre21RenderPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(ape::Event::Group::LIGHT, std::bind(&Ogre21RenderPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(ape::Event::Group::CAMERA, std::bind(&Ogre21RenderPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_FILE, std::bind(&Ogre21RenderPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_TEXT, std::bind(&Ogre21RenderPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_PLANE, std::bind(&Ogre21RenderPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_BOX, std::bind(&Ogre21RenderPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_CYLINDER, std::bind(&Ogre21RenderPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_CONE, std::bind(&Ogre21RenderPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_TUBE, std::bind(&Ogre21RenderPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_SPHERE, std::bind(&Ogre21RenderPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_TORUS, std::bind(&Ogre21RenderPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_INDEXEDFACESET, std::bind(&Ogre21RenderPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_INDEXEDLINESET, std::bind(&Ogre21RenderPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(ape::Event::Group::MATERIAL_FILE, std::bind(&Ogre21RenderPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(ape::Event::Group::MATERIAL_MANUAL, std::bind(&Ogre21RenderPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(ape::Event::Group::PASS_PBS, std::bind(&Ogre21RenderPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(ape::Event::Group::PASS_MANUAL, std::bind(&Ogre21RenderPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(ape::Event::Group::TEXTURE_MANUAL, std::bind(&Ogre21RenderPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(ape::Event::Group::TEXTURE_UNIT, std::bind(&Ogre21RenderPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_RAY, std::bind(&Ogre21RenderPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(ape::Event::Group::SKY, std::bind(&Ogre21RenderPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(ape::Event::Group::WATER, std::bind(&Ogre21RenderPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(ape::Event::Group::POINT_CLOUD, std::bind(&Ogre21RenderPlugin::eventCallBack, this, std::placeholders::_1));
	mpRoot = nullptr;
	mpSceneMgr = nullptr;
	mRenderWindows = std::map<std::string, Ogre::RenderWindow*>();
	mpHlmsPbsManager = nullptr;
	mOgreRenderPluginConfig = ape::Ogre21RenderPluginConfig();
	mOgreCameras = std::vector<Ogre::Camera*>();
	mCameraCountFromConfig = 0;
	APE_LOG_FUNC_LEAVE();
}

ape::Ogre21RenderPlugin::~Ogre21RenderPlugin() //destructor
{
	std::cout << "OgreRenderPlugin dtor" << std::endl;

	delete mpRoot;
}

void ape::Ogre21RenderPlugin::eventCallBack(const ape::Event& event)
{
	mEventDoubleQueue.push(event);
}



void ape::Ogre21RenderPlugin::processEventDoubleQueue()
{
	mEventDoubleQueue.swap();
	while (!mEventDoubleQueue.emptyPop())
	{
		ape::Event event = mEventDoubleQueue.front();
		if (event.group == ape::Event::Group::NODE)
		{
			if (auto node = mpSceneManager->getNode(event.subjectName).lock())
			{
				std::string nodeName = node->getName();
				if (event.type == ape::Event::Type::NODE_CREATE)
				{
					auto ogreNode = mpSceneMgr->getRootSceneNode()->createChildSceneNode();
					ogreNode->setName(nodeName);
				}
				else
				{
					Ogre::SceneNode* ogreNode = nullptr;
					auto &ogreNodeList = mpSceneMgr->findSceneNodes(nodeName);
					if (!ogreNodeList.empty())
					{
						ogreNode = mpSceneMgr->getSceneNode(ogreNodeList[0]->getId());
					}
					if (ogreNode)
					{
						switch (event.type)
						{
						case ape::Event::Type::NODE_PARENTNODE:
						{
							if (auto parentNode = node->getParentNode().lock())
							{
								auto ogreOldParentNode = ogreNode->getParentSceneNode();
								if (ogreOldParentNode)
								{
									ogreOldParentNode->removeChild(ogreNode);
								}

								if (mpSceneMgr->getSceneNode(ogreOldParentNode->getId()))
								{
									auto &ogreNodeList = mpSceneMgr->findSceneNodes(parentNode->getName());
									auto ogreNewParentNode = mpSceneMgr->getSceneNode(ogreNodeList[0]->getId());
									ogreNewParentNode->addChild(ogreNode);

								}
							}
						}
						break;
						case ape::Event::Type::NODE_DELETE:
							;
							break;
						case ape::Event::Type::NODE_POSITION:
							ogreNode->setPosition(ape::ConversionToOgre21(node->getPosition()));
							break;
						case ape::Event::Type::NODE_ORIENTATION:
							ogreNode->setOrientation(ape::ConversionToOgre21(node->getOrientation()));
							break;
						case ape::Event::Type::NODE_SCALE:
							ogreNode->setScale(ape::ConversionToOgre21(node->getScale()));
							break;
						case ape::Event::Type::NODE_CHILDVISIBILITY:
							ogreNode->setVisible(node->getChildrenVisibility());
							break;
						case ape::Event::Type::NODE_FIXEDYAW:
							ogreNode->setFixedYawAxis(node->isInheritOrientation());
							break;
						case ape::Event::Type::NODE_INITIALSTATE:
							;//ilyen nincs az ogre2.1ben
							break;
						case ape::Event::Type::NODE_SHOWBOUNDINGBOX:
							;
							//ogreNode->showBoundingBox(true); ilyensincs
							break;
						case ape::Event::Type::NODE_HIDEBOUNDINGBOX:
							;
							//ogreNode->showBoundingBox(false); ilyen sincs
							break;
						}
					}
				}

			}
		}
		else if (event.group == ape::Event::Group::GEOMETRY_FILE)
		{
			if (auto geometryFile = std::static_pointer_cast<ape::IFileGeometry>(mpSceneManager->getEntity(event.subjectName).lock()))
			{
				std::string geometryName = geometryFile->getName();
				std::string fileName = geometryFile->getFileName();
				std::string parentNodeName = "";
				if (auto parentNode = geometryFile->getParentNode().lock())
				{
					parentNodeName = parentNode->getName();
				}
				switch (event.type)
				{
				case ape::Event::Type::GEOMETRY_FILE_CREATE:
					;
					break;
				case ape::Event::Type::GEOMETRY_FILE_PARENTNODE:
				{
					//auto geomList = mpSceneMgr->findMovableObjects(, gemetryName);
					/*if (mpSceneMgr->)
					{

					}*/
				}



				}
			}
			mEventDoubleQueue.pop();
		}
	}
}


bool ape::Ogre21RenderPlugin::frameStarted(const Ogre::FrameEvent& evt)
{
	return Ogre::FrameListener::frameStarted(evt);
}

bool ape::Ogre21RenderPlugin::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	processEventDoubleQueue();
	return Ogre::FrameListener::frameRenderingQueued(evt);
}


bool ape::Ogre21RenderPlugin::frameEnded(const Ogre::FrameEvent& evt)
{
	return Ogre::FrameListener::frameEnded(evt);
}


void ape::Ogre21RenderPlugin::Stop()
{

}


void ape::Ogre21RenderPlugin::Suspend()
{

}


void ape::Ogre21RenderPlugin::Restart()
{

}


void ape::Ogre21RenderPlugin::Run()
{
	APE_LOG_FUNC_ENTER();
	try
	{
		mpRoot->renderOneFrame();
		mpRoot->startRendering();
	}
	catch (const Ogre::RenderingAPIException& ex)
	{
		std::cout << ex.getFullDescription() << std::endl;
		APE_LOG_ERROR(ex.getFullDescription());
	}
	catch (const Ogre::Exception& ex)
	{
		std::cout << ex.getFullDescription() << std::endl;
		APE_LOG_ERROR(ex.getFullDescription());
	}
	APE_LOG_FUNC_LEAVE();
}


void ape::Ogre21RenderPlugin::Step()
{
	try
	{
		mpRoot->renderOneFrame();
#ifndef __APPLE__
		Ogre::WindowEventUtilities::messagePump();
#endif
	}
	catch (const Ogre::RenderingAPIException& ex)
	{
		std::cout << ex.getFullDescription() << std::endl;
		APE_LOG_ERROR(ex.getFullDescription());
	}
	catch (const Ogre::Exception& ex)
	{
		std::cout << ex.getFullDescription() << std::endl;
		APE_LOG_ERROR(ex.getFullDescription());
	}
}









void ape::Ogre21RenderPlugin::Init()
{
	std::cout << "Init started" << std::endl;
	/*if (auto userNode = mpSceneManager->getNode(mpSystemConfig->getSceneSessionConfig().generatedUniqueUserNodeName).lock())
		mUserNode = userNode;
	if (mpSystemConfig->getSceneSessionConfig().participantType == ape::SceneSession::ParticipantType::HOST || mpSystemConfig->getSceneSessionConfig().participantType == ape::SceneSession::ParticipantType::GUEST)
	{
		if (auto userNode = mUserNode.lock())
		{
			if (auto userNameText = std::static_pointer_cast<ape::ITextGeometry>(mpSceneManager->createEntity(userNode->getName(), ape::Entity::GEOMETRY_TEXT).lock()))
			{
				userNameText->setCaption(userNode->getName());
				userNameText->setOffset(ape::Vector3(0.0f, 1.0f, 0.0f));
				userNameText->setParentNode(userNode);
			}
		}
	}*/



	APE_LOG_FUNC_ENTER();
	/*mpUserInputMacro = ape::UserInputMacro::getSingletonPtr();
	mUserInputMacroPose = ape::UserInputMacro::ViewPose();*/
	std::stringstream fileFullPath;
	fileFullPath << mpCoreConfig->getConfigFolderPath() << "\\apeOgre21RenderPlugin.json";
	FILE* apeOgreRenderPluginConfigFile = std::fopen(fileFullPath.str().c_str(), "r");
	char readBuffer[65536];
	if (apeOgreRenderPluginConfigFile)
	{
		rapidjson::FileReadStream jsonFileReaderStream(apeOgreRenderPluginConfigFile, readBuffer, sizeof(readBuffer));
		rapidjson::Document jsonDocument;
		jsonDocument.ParseStream(jsonFileReaderStream);
		if (jsonDocument.IsObject())
		{
			rapidjson::Value& renderSystem = jsonDocument["renderSystem"];
			mOgreRenderPluginConfig.renderSystem = renderSystem.GetString();
			rapidjson::Value& lodLevels = jsonDocument["lodLevels"];
			for (rapidjson::Value::MemberIterator lodLevelsMemberIterator =
				lodLevels.MemberBegin(); lodLevelsMemberIterator != lodLevels.MemberEnd(); ++lodLevelsMemberIterator)
			{
				if (lodLevelsMemberIterator->name == "autoGenerateAndSave")
					mOgreRenderPluginConfig.ogreLodLevelsConfig.autoGenerateAndSave = lodLevelsMemberIterator->value.GetBool();
				else if (lodLevelsMemberIterator->name == "bias")
					mOgreRenderPluginConfig.ogreLodLevelsConfig.bias = lodLevelsMemberIterator->value.GetFloat();
			}
			if (jsonDocument.HasMember("shading"))
			{
				rapidjson::Value& shading = jsonDocument["shading"];
				mOgreRenderPluginConfig.shading = shading.GetString();
			}
			rapidjson::Value& renderWindows = jsonDocument["renderWindows"];
			for (auto& renderWindow : renderWindows.GetArray())
			{
				ape::OgreRenderWindowConfig ogreRenderWindowConfig;
				for (rapidjson::Value::MemberIterator renderWindowMemberIterator =
					renderWindow.MemberBegin(); renderWindowMemberIterator != renderWindow.MemberEnd(); ++renderWindowMemberIterator)
				{
					if (renderWindowMemberIterator->name == "enable")
						ogreRenderWindowConfig.enable = renderWindowMemberIterator->value.GetBool();
					else if (renderWindowMemberIterator->name == "name")
						ogreRenderWindowConfig.name = renderWindowMemberIterator->value.GetString();
					else if (renderWindowMemberIterator->name == "monitorIndex")
						ogreRenderWindowConfig.monitorIndex = renderWindowMemberIterator->value.GetInt();
					else if (renderWindowMemberIterator->name == "resolution")
					{
						for (rapidjson::Value::MemberIterator resolutionMemberIterator =
							renderWindow[renderWindowMemberIterator->name].MemberBegin();
							resolutionMemberIterator != renderWindow[renderWindowMemberIterator->name].MemberEnd(); ++resolutionMemberIterator)
						{
							if (resolutionMemberIterator->name == "width")
								ogreRenderWindowConfig.width = resolutionMemberIterator->value.GetInt();
							else if (resolutionMemberIterator->name == "height")
								ogreRenderWindowConfig.height = resolutionMemberIterator->value.GetInt();
							else if (resolutionMemberIterator->name == "fullScreen")
								ogreRenderWindowConfig.fullScreen = resolutionMemberIterator->value.GetBool();
						}
					}
					else if (renderWindowMemberIterator->name == "miscParams")
					{
						for (rapidjson::Value::MemberIterator miscParamsMemberIterator =
							renderWindow[renderWindowMemberIterator->name].MemberBegin();
							miscParamsMemberIterator != renderWindow[renderWindowMemberIterator->name].MemberEnd(); ++miscParamsMemberIterator)
						{
							if (miscParamsMemberIterator->name == "vSync")
								ogreRenderWindowConfig.vSync = miscParamsMemberIterator->value.GetBool();
							else if (miscParamsMemberIterator->name == "vSyncInterval")
								ogreRenderWindowConfig.vSyncInterval = miscParamsMemberIterator->value.GetInt();
							else if (miscParamsMemberIterator->name == "colorDepth")
								ogreRenderWindowConfig.colorDepth = miscParamsMemberIterator->value.GetInt();
							else if (miscParamsMemberIterator->name == "FSAA")
								ogreRenderWindowConfig.fsaa = miscParamsMemberIterator->value.GetInt();
							else if (miscParamsMemberIterator->name == "FSAAHint")
								ogreRenderWindowConfig.fsaaHint = miscParamsMemberIterator->value.GetString();
						}
					}
					else if (renderWindowMemberIterator->name == "viewports")
					{
						rapidjson::Value& viewports = renderWindow[renderWindowMemberIterator->name];
						for (auto& viewport : viewports.GetArray())
						{
							ape::OgreViewPortConfig ogreViewPortConfig;
							for (rapidjson::Value::MemberIterator viewportMemberIterator =
								viewport.MemberBegin();
								viewportMemberIterator != viewport.MemberEnd(); ++viewportMemberIterator)
							{
								if (viewportMemberIterator->name == "zOrder")
									ogreViewPortConfig.zOrder = viewportMemberIterator->value.GetInt();
								else if (viewportMemberIterator->name == "left")
									ogreViewPortConfig.left = viewportMemberIterator->value.GetInt();
								else if (viewportMemberIterator->name == "top")
									ogreViewPortConfig.top = viewportMemberIterator->value.GetInt();
								else if (viewportMemberIterator->name == "width")
									ogreViewPortConfig.width = viewportMemberIterator->value.GetInt();
								else if (viewportMemberIterator->name == "height")
									ogreViewPortConfig.height = viewportMemberIterator->value.GetInt();
								else if (viewportMemberIterator->name == "camera")
								{
									for (rapidjson::Value::MemberIterator cameraMemberIterator =
										viewport[viewportMemberIterator->name].MemberBegin();
										cameraMemberIterator != viewport[viewportMemberIterator->name].MemberEnd(); ++cameraMemberIterator)
									{
										if (cameraMemberIterator->name == "name")
											ogreViewPortConfig.camera.name = cameraMemberIterator->value.GetString();
										else if (cameraMemberIterator->name == "nearClip")
											ogreViewPortConfig.camera.nearClip = cameraMemberIterator->value.GetFloat();
										else if (cameraMemberIterator->name == "farClip")
											ogreViewPortConfig.camera.farClip = cameraMemberIterator->value.GetFloat();
										else if (cameraMemberIterator->name == "fovY")
											ogreViewPortConfig.camera.fovY = cameraMemberIterator->value.GetFloat();
										else if (cameraMemberIterator->name == "positionOffset")
										{
											for (rapidjson::Value::MemberIterator elementMemberIterator =
												viewport[viewportMemberIterator->name][cameraMemberIterator->name].MemberBegin();
												elementMemberIterator != viewport[viewportMemberIterator->name][cameraMemberIterator->name].MemberEnd(); ++elementMemberIterator)
											{
												if (elementMemberIterator->name == "x")
													ogreViewPortConfig.camera.positionOffset.x = elementMemberIterator->value.GetFloat();
												else if (elementMemberIterator->name == "y")
													ogreViewPortConfig.camera.positionOffset.y = elementMemberIterator->value.GetFloat();
												else if (elementMemberIterator->name == "z")
													ogreViewPortConfig.camera.positionOffset.z = elementMemberIterator->value.GetFloat();
											}
										}
										else if (cameraMemberIterator->name == "orientationOffset")
										{
											Ogre::Quaternion orientationOffset;
											Ogre::Degree angle;
											Ogre::Vector3 axis;
											for (rapidjson::Value::MemberIterator elementMemberIterator =
												viewport[viewportMemberIterator->name][cameraMemberIterator->name].MemberBegin();
												elementMemberIterator != viewport[viewportMemberIterator->name][cameraMemberIterator->name].MemberEnd(); ++elementMemberIterator)
											{
												if (elementMemberIterator->name == "angle")
													angle = elementMemberIterator->value.GetFloat();
												else if (elementMemberIterator->name == "x")
													axis.x = elementMemberIterator->value.GetFloat();
												else if (elementMemberIterator->name == "y")
													axis.y = elementMemberIterator->value.GetFloat();
												else if (elementMemberIterator->name == "z")
													axis.z = elementMemberIterator->value.GetFloat();
											}
											orientationOffset.FromAngleAxis(angle, axis);
											ogreViewPortConfig.camera.orientationOffset = ape::ConversionFromOgre21(orientationOffset);
										}
									}
									mCameraCountFromConfig++;
								}
							}
							ogreRenderWindowConfig.viewportList.push_back(ogreViewPortConfig);
						}
					}
				}
				mOgreRenderPluginConfig.ogreRenderWindowConfigList.push_back(ogreRenderWindowConfig);
			}
		}
		fclose(apeOgreRenderPluginConfigFile);
	}

	mpRoot = OGRE_NEW Ogre::Root("", "", "apeOgre21RenderPlugin.log");

	Ogre::LogManager::getSingleton().createLog("apeOgre21RenderPlugin.log", true, false, false);

#if defined (_DEBUG)
	Ogre::LogManager::getSingleton().setLogDetail(Ogre::LL_BOREME);
	if (mOgreRenderPluginConfig.renderSystem == "DX11")
		mpRoot->loadPlugin("RenderSystem_Direct3D11_d");
	else
		mpRoot->loadPlugin("RenderSystem_GL3Plus_d");
#else
	Ogre::LogManager::getSingleton().setLogDetail(Ogre::LL_NORMAL);
	if (mOgreRenderPluginConfig.renderSystem == "DX11")
		mpRoot->loadPlugin("RenderSystem_Direct3D11");
	else
		mpRoot->loadPlugin("RenderSystem_GL3Plus");
#endif




	Ogre::RenderSystem* renderSystem = nullptr;
	if (mOgreRenderPluginConfig.renderSystem == "DX11")
		renderSystem = mpRoot->getRenderSystemByName("Direct3D11 Rendering Subsystem");
	else
		renderSystem = mpRoot->getRenderSystemByName("Open_GL3Plus Rendering Subsystem");

	if (renderSystem == NULL)
		std::cout << "WTF" << std::endl;

	std::stringstream mediaFolder;
	mediaFolder << APE_SOURCE_DIR << "/plugins/ogre21Render/media";

	mpRoot->setRenderSystem(renderSystem);

	if (mOgreRenderPluginConfig.renderSystem == "DX9")
	{
		renderSystem->setConfigOption("Resource Creation Policy", "Create on all devices");
		renderSystem->setConfigOption("Multi device memory hint", "Auto hardware buffers management");
	}

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mediaFolder.str() + "/fonts", "FileSystem");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mediaFolder.str() + "/materials", "FileSystem");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mediaFolder.str() + "/pbs", "FileSystem");

	for (auto resourceLocation : mpCoreConfig->getNetworkConfig().resourceLocations)
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(resourceLocation, "FileSystem");

	mpRoot->showConfigDialog();

	mpRoot->initialise(true, "ape");

	Ogre::InstancingThreadedCullingMethod instancingThreadedCullingMethod = Ogre::INSTANCING_CULLING_SINGLETHREAD; //-> új miatt

#if OGRE_DEBUG_MODE
	const size_t numThreads = 1;
#else
	const size_t numThreads = std::max<size_t>(1, Ogre::PlatformInformation::getNumLogicalCores());
	if (numThreads > 1)
		instancingThreadedCullingMethod = Ogre::INSTANCING_CULLING_THREADED;
#endif

	mpSceneMgr = mpRoot->createSceneManager(Ogre::ST_GENERIC, numThreads, instancingThreadedCullingMethod);// ->új miatt

	mpRoot->addFrameListener(this);

	Ogre::RenderWindowList renderWindowList;
	Ogre::RenderWindowDescriptionList winDescList;
	int enabledWindowCount = 0;
	void* mainWindowHnd = 0;
	for (int i = 0; i < mOgreRenderPluginConfig.ogreRenderWindowConfigList.size(); i++)
	{
		if (mOgreRenderPluginConfig.ogreRenderWindowConfigList[i].enable)
		{
			enabledWindowCount++;
			Ogre::RenderWindowDescription winDesc;
			std::stringstream ss;
			ss << mOgreRenderPluginConfig.ogreRenderWindowConfigList[i].name;
			winDesc.name = ss.str();
			winDesc.height = mOgreRenderPluginConfig.ogreRenderWindowConfigList[i].height;
			winDesc.width = mOgreRenderPluginConfig.ogreRenderWindowConfigList[i].width;
			winDesc.useFullScreen = mOgreRenderPluginConfig.ogreRenderWindowConfigList[i].fullScreen;
			std::stringstream colourDepthSS;
			colourDepthSS << mOgreRenderPluginConfig.ogreRenderWindowConfigList[i].colorDepth;
			winDesc.miscParams["colourDepth"] = colourDepthSS.str().c_str();
			winDesc.miscParams["vsync"] = mOgreRenderPluginConfig.ogreRenderWindowConfigList[i].vSync ? "Yes" : "No";
			std::stringstream vsyncIntervalSS;
			vsyncIntervalSS << mOgreRenderPluginConfig.ogreRenderWindowConfigList[i].vSyncInterval;
			winDesc.miscParams["vsyncInterval"] = vsyncIntervalSS.str().c_str();
			std::stringstream fsaaSS;
			fsaaSS << mOgreRenderPluginConfig.ogreRenderWindowConfigList[i].fsaa;
			winDesc.miscParams["FSAA"] = fsaaSS.str().c_str();
			winDesc.miscParams["FSAAHint"] = mOgreRenderPluginConfig.ogreRenderWindowConfigList[i].fsaaHint;
			std::stringstream monitorIndexSS;
			monitorIndexSS << mOgreRenderPluginConfig.ogreRenderWindowConfigList[i].monitorIndex;
			winDesc.miscParams["monitorIndex"] = monitorIndexSS.str().c_str();
			winDescList.push_back(winDesc);
			APE_LOG_DEBUG("winDesc:" << " name=" << winDesc.name << " width=" << winDesc.width << " height=" << winDesc.height << " fullScreen=" << winDesc.useFullScreen);
			mRenderWindows[winDesc.name] = mpRoot->createRenderWindow(winDesc.name, winDesc.width, winDesc.height, winDesc.useFullScreen, &winDesc.miscParams);
			mRenderWindows[winDesc.name]->setDeactivateOnFocusChange(false);
			mRenderWindows[winDesc.name]->setHidden(mOgreRenderPluginConfig.ogreRenderWindowConfigList[i].enable);

			if (mpCoreConfig->getWindowConfig().name == THIS_PLUGINNAME)
			{

				if (enabledWindowCount == 1)
				{
					std::cout << winDesc.width << std::endl;
					mRenderWindows[winDesc.name] = mpRoot->createRenderWindow(winDesc.name, winDesc.width, winDesc.height, winDesc.useFullScreen, &winDesc.miscParams);
					mRenderWindows[winDesc.name]->setDeactivateOnFocusChange(false);
					for (int j = 0; j < mOgreRenderPluginConfig.ogreRenderWindowConfigList[i].viewportList.size(); j++)
					{
						auto camera = std::static_pointer_cast<ape::ICamera>(mpSceneManager->createEntity(mOgreRenderPluginConfig.ogreRenderWindowConfigList[i].viewportList[j].camera.name, ape::Entity::Type::CAMERA).lock());
						if (camera)
						{
							//TODO why it is not ok
							//camera->setAspectRatio((float)mOgreRenderWindowConfigList[i].width / (float)mOgreRenderWindowConfigList[i].height);
							camera->setWindow(winDesc.name);
							camera->setFocalLength(1.0f);
							camera->setNearClipDistance(mOgreRenderPluginConfig.ogreRenderWindowConfigList[i].viewportList[j].camera.nearClip);
							camera->setFarClipDistance(mOgreRenderPluginConfig.ogreRenderWindowConfigList[i].viewportList[j].camera.farClip);
							camera->setFOVy(mOgreRenderPluginConfig.ogreRenderWindowConfigList[i].viewportList[j].camera.fovY.toRadian());
							if (auto userNode = mUserNode.lock())
								camera->setParentNode(mUserNode);
						}
					}

					mRenderWindows[winDesc.name]->getCustomAttribute("WINDOW", &mainWindowHnd);
					std::ostringstream windowHndStr;
					windowHndStr << mainWindowHnd;
					mOgreRenderPluginConfig.ogreRenderWindowConfigList[i].windowHandler = windowHndStr.str();
					//mpMainWindow->setName(winDesc.name);
					//mpMainWindow->setWidth(mOgreRenderPluginConfig.ogreRenderWindowConfigList[i].width);
					//mpMainWindow->setHeight(mOgreRenderPluginConfig.ogreRenderWindowConfigList[i].height);

					//Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();


					//pHlmsPbsManager = new Ogre::HlmsPbsManager;


					//Has to be the last call because of the sync if needed
					//mpMainWindow->setHandle(mainWindowHnd);
				}
			}
		}
	}
	APE_LOG_FUNC_ENTER();
	int mainWindowID = 0; //first window will be the main window
	Ogre::RenderWindowDescription mainWindowDesc = winDescList[mainWindowID];
	mRenderWindows[mainWindowDesc.name]->getCustomAttribute("WINDOW", &mainWindowHnd);
	std::ostringstream windowHndStr;
	windowHndStr << mainWindowHnd;
	mOgreRenderPluginConfig.ogreRenderWindowConfigList[mainWindowID].windowHandler = windowHndStr.str();
	ape::WindowConfig windowConfig(mainWindowDesc.name, mOgreRenderPluginConfig.renderSystem, mainWindowHnd, mOgreRenderPluginConfig.ogreRenderWindowConfigList[mainWindowID].width,
		mOgreRenderPluginConfig.ogreRenderWindowConfigList[mainWindowID].height);
	mpCoreConfig->setWindowConfig(windowConfig);

	APE_LOG_FUNC_LEAVE();

}
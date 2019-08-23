#include "apePhotorealisticScenePlugin.h"

ape::apePhotorealisticScenePlugin::apePhotorealisticScenePlugin()
{
	APE_LOG_FUNC_ENTER();
	mpCoreConfig = ape::ICoreConfig::getSingletonPtr();
	mpEventManager = ape::IEventManager::getSingletonPtr();
	mpEventManager->connectEvent(ape::Event::Group::CAMERA, std::bind(&apePhotorealisticScenePlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(ape::Event::Group::NODE, std::bind(&apePhotorealisticScenePlugin::eventCallBack, this, std::placeholders::_1));
	mpSceneManager = ape::ISceneManager::getSingletonPtr();
	mpSceneMakerMacro = new ape::SceneMakerMacro();
	APE_LOG_FUNC_LEAVE();
}

ape::apePhotorealisticScenePlugin::~apePhotorealisticScenePlugin()
{
	APE_LOG_FUNC_ENTER();
	mpEventManager->disconnectEvent(ape::Event::Group::CAMERA, std::bind(&apePhotorealisticScenePlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->disconnectEvent(ape::Event::Group::NODE, std::bind(&apePhotorealisticScenePlugin::eventCallBack, this, std::placeholders::_1));
	APE_LOG_FUNC_LEAVE();
}

void ape::apePhotorealisticScenePlugin::eventCallBack(const ape::Event& event)
{

}

void ape::apePhotorealisticScenePlugin::Init()
{
	APE_LOG_FUNC_ENTER();
	//mpSceneMakerMacro->makeLit();
	if (auto light = std::static_pointer_cast<ape::ILight>(mpSceneManager->createEntity("light", ape::Entity::LIGHT).lock()))
	{
		light->setLightType(ape::Light::Type::DIRECTIONAL);
		light->setLightDirection(ape::Vector3(1, -1, 0));
		light->setDiffuseColor(ape::Color(0.6f, 0.6f, 0.6f));
		light->setSpecularColor(ape::Color(0.6f, 0.6f, 0.6f));
	}
	if (auto light = std::static_pointer_cast<ape::ILight>(mpSceneManager->createEntity("light2", ape::Entity::LIGHT).lock()))
	{
		light->setLightType(ape::Light::Type::DIRECTIONAL);
		light->setLightDirection(ape::Vector3(0, -1, 1));
		light->setDiffuseColor(ape::Color(0.6f, 0.6f, 0.6f));
		light->setSpecularColor(ape::Color(0.6f, 0.6f, 0.6f));
	}
	//--
	if (auto light = std::static_pointer_cast<ape::ILight>(mpSceneManager->createEntity("light3", ape::Entity::LIGHT).lock()))
	{
		light->setLightType(ape::Light::Type::DIRECTIONAL);
		light->setLightDirection(ape::Vector3(0, 1, -1));
		light->setDiffuseColor(ape::Color(0.6f, 0.6f, 0.6f));
		light->setSpecularColor(ape::Color(0.6f, 0.6f, 0.6f));
	}
	if (auto light = std::static_pointer_cast<ape::ILight>(mpSceneManager->createEntity("light4", ape::Entity::LIGHT).lock()))
	{
		light->setLightType(ape::Light::Type::DIRECTIONAL);
		light->setLightDirection(ape::Vector3(-1, 1, 0));
		light->setDiffuseColor(ape::Color(0.6f, 0.6f, 0.6f));
		light->setSpecularColor(ape::Color(0.6f, 0.6f, 0.6f));
	}
	//--
	
	std::size_t found = mpCoreConfig->getConfigFolderPath().find("ogre_mesh");
	if (found != std::string::npos)
		mpSceneMakerMacro->makeModel("mycube.mesh");
	//mpSceneMakerMacro->makeCoordinateSystem();
	//mpSceneMakerMacro->makeBackground();
	
	//mpSceneMakerMacro->makeGround();
	APE_LOG_FUNC_LEAVE();
}

void ape::apePhotorealisticScenePlugin::Run()
{
	APE_LOG_FUNC_ENTER();
	if (auto skyBoxMaterial = std::static_pointer_cast<ape::IFileMaterial>(mpSceneManager->createEntity("SkyPostprocess", ape::Entity::MATERIAL_FILE).lock()))
	{
		skyBoxMaterial->setFileName("SkyPostprocess");
		skyBoxMaterial->setAsSkyBox();
	}
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	APE_LOG_FUNC_LEAVE();
}

void ape::apePhotorealisticScenePlugin::Step()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

void ape::apePhotorealisticScenePlugin::Stop()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

void ape::apePhotorealisticScenePlugin::Suspend()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

void ape::apePhotorealisticScenePlugin::Restart()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

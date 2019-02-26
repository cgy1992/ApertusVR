#include "ApeCoreSyncTestPlugin.h"
#include <chrono>
#include <thread>

Ape::ApeCoreSyncTestPlugin::ApeCoreSyncTestPlugin()
{
	APE_LOG_FUNC_ENTER();
	mpEventManager = Ape::IEventManager::getSingletonPtr();
	mpEventManager->connectEvent(Ape::Event::Group::NODE,				std::bind(&ApeCoreSyncTestPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(Ape::Event::Group::GEOMETRY_TEXT,		std::bind(&ApeCoreSyncTestPlugin::eventCallBack, this, std::placeholders::_1));
	mpSystemConfigManager = Ape::ISystemConfig::getSingletonPtr();
	mpSceneManager = Ape::ISceneManager::getSingletonPtr();
	APE_LOG_FUNC_LEAVE();
}

Ape::ApeCoreSyncTestPlugin::~ApeCoreSyncTestPlugin()
{
	APE_LOG_FUNC_ENTER();
	mpEventManager->disconnectEvent(Ape::Event::Group::NODE,			std::bind(&ApeCoreSyncTestPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->disconnectEvent(Ape::Event::Group::GEOMETRY_TEXT,	std::bind(&ApeCoreSyncTestPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager = nullptr;
	mpSceneManager = nullptr;
	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeCoreSyncTestPlugin::eventCallBack(const Ape::Event& e)
{
	APE_LOG_DEBUG("EventCallback> " << e.toString());

	if (e.type == Ape::Event::Type::GEOMETRY_TEXT_CAPTION)
	{
		auto entityWeakPtr = mpSceneManager->getEntity(e.subjectName);
		if (auto entity = entityWeakPtr.lock())
		{
			if (auto textGeometry = std::dynamic_pointer_cast<Ape::ITextGeometry>(entity))
			{
				APE_LOG_DEBUG("EventCallback> statusText caption changed to: " << textGeometry->getCaption());
			}
		}
	}
}

std::string Ape::ApeCoreSyncTestPlugin::getSystemDateTime()
{
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	char buf[100] = { 0 };
	std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
	return std::string(buf);
}

void Ape::ApeCoreSyncTestPlugin::changeStatusText(std::string caption)
{
	if (auto entity = mStatusText.lock())
	{
		if (auto textGeometry = std::dynamic_pointer_cast<Ape::ITextGeometry>(entity))
		{
			textGeometry->setCaption(caption);
		}
	}
}

void Ape::ApeCoreSyncTestPlugin::Init()
{
	APE_LOG_FUNC_ENTER();

	mUniqueUserNamePrefix = mpSystemConfigManager->getSceneSessionConfig().uniqueUserNamePrefix;
	APE_LOG_DEBUG("mUniqueUserNamePrefix: " << mUniqueUserNamePrefix);

	std::stringstream entityName;
	entityName << mUniqueUserNamePrefix << " - statusText";
	mStatusText = mpSceneManager->createEntity(entityName.str(), Ape::Entity::GEOMETRY_TEXT);

	mpSceneManager->createNode("planetNode");

	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeCoreSyncTestPlugin::Run()
{
	APE_LOG_FUNC_ENTER();
	while (true)
	{
		std::stringstream ss;
		ss << mUniqueUserNamePrefix << " - " << getSystemDateTime();
		changeStatusText(ss.str());

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeCoreSyncTestPlugin::Step()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeCoreSyncTestPlugin::Stop()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeCoreSyncTestPlugin::Suspend()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeCoreSyncTestPlugin::Restart()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

#include "ApeCoreSyncTestPlugin.h"
#include <chrono>
#include <thread>

Ape::ApeCoreSyncTestPlugin::ApeCoreSyncTestPlugin()
{
	APE_LOG_FUNC_ENTER();
	mpEventManager = Ape::IEventManager::getSingletonPtr();
	mpEventManager->connectEvent(Ape::Event::Group::GEOMETRY_TEXT, std::bind(&ApeCoreSyncTestPlugin::eventCallBack, this, std::placeholders::_1));
	mpSystemConfigManager = Ape::ISystemConfig::getSingletonPtr();
	mpSceneManager = Ape::ISceneManager::getSingletonPtr();
	APE_LOG_FUNC_LEAVE();
}

Ape::ApeCoreSyncTestPlugin::~ApeCoreSyncTestPlugin()
{
	APE_LOG_FUNC_ENTER();
	mpEventManager->disconnectEvent(Ape::Event::Group::NODE, std::bind(&ApeCoreSyncTestPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager = nullptr;
	mpSceneManager = nullptr;
	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeCoreSyncTestPlugin::eventCallBack(const Ape::Event& event)
{
	if (event.subjectName == "statusText")
	{
		if (event.type == Ape::Event::Type::GEOMETRY_TEXT_CAPTION)
		{
			auto entityWeakPtr = mpSceneManager->getEntity(event.subjectName);
			if (auto entity = entityWeakPtr.lock())
			{
				if (auto textGeometry = std::dynamic_pointer_cast<Ape::ITextGeometry>(entity))
				{
					APE_LOG_DEBUG("EventCallback> statusText caption changed to: " << textGeometry->getCaption());
				}
			}
		}
	}
}

void Ape::ApeCoreSyncTestPlugin::Init()
{
	APE_LOG_FUNC_ENTER();

	uniqueUserNamePrefix = mpSystemConfigManager->getSceneSessionConfig().uniqueUserNamePrefix;
	APE_LOG_DEBUG("uniqueUserNamePrefix: " << uniqueUserNamePrefix);
	mStatusText = mpSceneManager->createEntity("statusText", Ape::Entity::GEOMETRY_TEXT);

	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeCoreSyncTestPlugin::Run()
{
	APE_LOG_FUNC_ENTER();
	while (true)
	{
		if (auto statusText = std::static_pointer_cast<Ape::ITextGeometry>(mStatusText.lock()))
		{
			std::stringstream ss;
			std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			char buf[100] = {0};
			std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

			ss << uniqueUserNamePrefix << " - " << buf;
			statusText->setCaption(ss.str());
		}
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

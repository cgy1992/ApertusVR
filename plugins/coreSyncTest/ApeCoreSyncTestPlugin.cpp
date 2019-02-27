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

	mUniqueUserNamePrefix = mpSystemConfigManager->getSceneSessionConfig().uniqueUserNamePrefix;
	mParticipantType = mpSystemConfigManager->getSceneSessionConfig().participantType;
	switch (mParticipantType)
	{
	case SceneSession::ParticipantType::INVALID:
		mUniqueUserNamePrefix += " INVALID";
		break;
	case Ape::SceneSession::ParticipantType::HOST:
		mUniqueUserNamePrefix += " HOST";
		break;
	case Ape::SceneSession::ParticipantType::GUEST:
		mUniqueUserNamePrefix += " GUEST";
	default:
		break;
	}
	APE_LOG_DEBUG("UniqueUserNamePrefix: " << mUniqueUserNamePrefix);

	APE_LOG_FUNC_LEAVE();
}

Ape::ApeCoreSyncTestPlugin::~ApeCoreSyncTestPlugin()
{
	APE_LOG_FUNC_ENTER();
	mpEventManager->disconnectEvent(Ape::Event::Group::NODE,			std::bind(&ApeCoreSyncTestPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->disconnectEvent(Ape::Event::Group::GEOMETRY_TEXT,	std::bind(&ApeCoreSyncTestPlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager = nullptr;
	mpSystemConfigManager = nullptr;
	mpSceneManager = nullptr;
	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeCoreSyncTestPlugin::eventCallBack(const Ape::Event& e)
{
	APE_LOG_DEBUG("EventCallback> " << e.toString());

	if (e.type == Ape::Event::Type::GEOMETRY_TEXT_CAPTION)
	{
		if (auto textGeometry = std::dynamic_pointer_cast<Ape::ITextGeometry>(mpSceneManager->getEntity(e.subjectName).lock()))
		{
			APE_LOG_DEBUG("EventCallback> statusText caption changed to: " << textGeometry->getCaption());
		}
	}
}

void Ape::ApeCoreSyncTestPlugin::Init()
{
	APE_LOG_FUNC_ENTER();
	if (mParticipantType == Ape::SceneSession::ParticipantType::GUEST)
	{
		if (auto testNode = mpSceneManager->createNode("testNode").lock())
		{
			mStatusText = mpSceneManager->createEntity("testTextGeometry", Ape::Entity::GEOMETRY_TEXT);
			if (auto textGeometry = std::dynamic_pointer_cast<Ape::ITextGeometry>(mStatusText.lock()))
			{
				textGeometry->setParentNode(testNode);
				textGeometry->setCaption(mUniqueUserNamePrefix + " - " + Ape::DateTime::getSystemDateTime());
			}
		}
	}
	APE_LOG_FUNC_LEAVE();
}

void Ape::ApeCoreSyncTestPlugin::Run()
{
	APE_LOG_FUNC_ENTER();
	if (mParticipantType == Ape::SceneSession::ParticipantType::HOST)
	{
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
	}
	else if (mParticipantType == Ape::SceneSession::ParticipantType::GUEST)
	{
		while (true)
		{
			if (auto textGeometry = std::dynamic_pointer_cast<Ape::ITextGeometry>(mpSceneManager->getEntity("testTextGeometry").lock()))
			{
				textGeometry->setCaption(mUniqueUserNamePrefix + " - " + Ape::DateTime::getSystemDateTime());
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		}
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

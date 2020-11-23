#include "apeFilamentMacScenePlugin.h"

ape::apeFilamentMacScenePlugin::apeFilamentMacScenePlugin()
{
	APE_LOG_FUNC_ENTER();
	mpCoreConfig = ape::ICoreConfig::getSingletonPtr();
	mpEventManager = ape::IEventManager::getSingletonPtr();
	mpEventManager->connectEvent(ape::Event::Group::CAMERA, std::bind(&apeFilamentMacScenePlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->connectEvent(ape::Event::Group::NODE, std::bind(&apeFilamentMacScenePlugin::eventCallBack, this, std::placeholders::_1));
	mpSceneManager = ape::ISceneManager::getSingletonPtr();
	mpSceneMakerMacro = new ape::SceneMakerMacro();
	APE_LOG_FUNC_LEAVE();
}

ape::apeFilamentMacScenePlugin::~apeFilamentMacScenePlugin()
{
	APE_LOG_FUNC_ENTER();
	mpEventManager->disconnectEvent(ape::Event::Group::CAMERA, std::bind(&apeFilamentMacScenePlugin::eventCallBack, this, std::placeholders::_1));
	mpEventManager->disconnectEvent(ape::Event::Group::NODE, std::bind(&apeFilamentMacScenePlugin::eventCallBack, this, std::placeholders::_1));
	APE_LOG_FUNC_LEAVE();
}

void ape::apeFilamentMacScenePlugin::eventCallBack(const ape::Event& event)
{

}

void ape::apeFilamentMacScenePlugin::Init()
{
    
    ape::NodeWeakPtr mNode;
    /*ape::ISceneManager* mpSceneManager;
    ape::ICoreConfig* mpCoreConfig;
    
   
    Engine* engine = Engine::create();
    SwapChain* swapChain = engine->createSwapChain(nsView);
    Renderer* renderer = engine->createRenderer();

    filament::Camera* camera = engine->createCamera(utils::EntityManager::get().create());
    View* view = engine->createView();
    Scene* scene = engine->createScene();

    view->setCamera(camera);
    view->setScene(scene);
    
    VertexBuffer* vb;
    IndexBuffer* ib;
    
   
    
    vb = VertexBuffer::Builder()
                    .vertexCount(3).bufferCount(1)
                    .attribute(VertexAttribute::POSITION, 0, VertexBuffer::AttributeType::FLOAT2, 0, 12)
                    .attribute(VertexAttribute::COLOR, 0, VertexBuffer::AttributeType::UBYTE4, 8, 12)
                    .normalized(VertexAttribute::COLOR).build(*engine);
    vb->setBufferAt(*engine, 0,
                    VertexBuffer::BufferDescriptor(TRIANGLE_VERTICES, 36, nullptr));
    
    
    ib = IndexBuffer::Builder().indexCount(3).bufferType(IndexBuffer::IndexType::USHORT).build(*engine);

    ib->setBuffer(*engine,
                    IndexBuffer::BufferDescriptor(TRIANGLE_INDICES, 6, nullptr));
    
   
    
    view->setViewport({0, 0, (uint32_t)nsView.frame.size.width*2, (uint32_t)nsView.frame.size.height*2});
    const double aspect = (double) nsView.frame.size.width / nsView.frame.size.height;

    const double left   = -2.0 * aspect;
    const double right  =  2.0 * aspect;
    const double bottom = -2.0;
    const double top    =  2.0;
    const double near   =  0.0;
    const double far    =  1.0;
    camera->setProjection(filament::Camera::Projection::ORTHO, left, right, bottom, top, near, far);
    
    
    
    
    utils::Entity renderable = utils::EntityManager::get().create();
    
    RenderableManager::Builder(1)
                .boundingBox({{ -1, -1, -1 }, { 1, 1, 1 }})
                .geometry(0, RenderableManager::PrimitiveType::TRIANGLES, vb, ib, 0, 3)
                .build(*engine, renderable);
   
    scene->addEntity(renderable);
    
    if(renderer->beginFrame(swapChain)){
        renderer->render(view);
        renderer->endFrame();
    }*/
   //[self.view addSubview:aView]; //(NSView*)swapChain->getNativeWindow()
    
	APE_LOG_FUNC_ENTER();
    
    if (auto node = mNode.lock())
        {
            node->setScale(ape::Vector3(10, 10, 10));
            node->setOrientation(ape::Quaternion(0, 0, 1, 0));
            node->setPosition(ape::Vector3(0, 0, -50));
            if (auto gltfMeshFile = std::static_pointer_cast<ape::IFileGeometry>(mpSceneManager->createEntity("cube", ape::Entity::GEOMETRY_FILE, true, mpCoreConfig->getNetworkGUID()).lock()))
            {
                gltfMeshFile->setParentNode(node);
                gltfMeshFile->setFileName("cube.gltf");
               
                
            }
            
        }
    /*
	if (auto universeSkyBoxMaterial = std::static_pointer_cast<ape::IFileMaterial>(mpSceneManager->createEntity("universe", ape::Entity::MATERIAL_FILE, true, mpCoreConfig->getNetworkGUID()).lock()))
	{
		universeSkyBoxMaterial->setFileName("universe");
		universeSkyBoxMaterial->setAsSkyBox();
	}
	if (auto light = std::static_pointer_cast<ape::ILight>(mpSceneManager->createEntity("light", ape::Entity::LIGHT, true, mpCoreConfig->getNetworkGUID()).lock()))
	{
		light->setLightType(ape::Light::Type::DIRECTIONAL);
		light->setLightDirection(ape::Vector3(1, 0, 0));
		light->setDiffuseColor(ape::Color(0.8f, 0.8f, 0.8f));
		light->setSpecularColor(ape::Color(0.8f, 0.8f, 0.8f));
	}
	mPlanetNode = mpSceneManager->createNode("planetNode", true, mpCoreConfig->getNetworkGUID());
	if (auto planetNode = mPlanetNode.lock())
	{
		//planetNode->setScale(ape::Vector3(10, 10, 10));
		planetNode->setPosition(ape::Vector3(0, 150, 0));
		if (auto planetMeshFile = std::static_pointer_cast<ape::IFileGeometry>(mpSceneManager->createEntity("planet.mesh", ape::Entity::GEOMETRY_FILE, true, mpCoreConfig->getNetworkGUID()).lock()))
		{
			planetMeshFile->setFileName("planet.mesh");
			planetMeshFile->setParentNode(planetNode);
		}
		if (auto textNode = mpSceneManager->createNode("helloWorldText_Node", true, mpCoreConfig->getNetworkGUID()).lock())
		{
			textNode->setParentNode(planetNode);
			textNode->setPosition(ape::Vector3(0.0f, 10.0f, 0.0f));
			if (auto userNameText = std::static_pointer_cast<ape::ITextGeometry>(mpSceneManager->createEntity("helloWorldText", ape::Entity::GEOMETRY_TEXT, true, mpCoreConfig->getNetworkGUID()).lock()))
			{
				userNameText->setCaption("helloWorld");
				userNameText->setParentNode(textNode);
			}
		}
	}*/
	APE_LOG_FUNC_LEAVE();
}

void ape::apeFilamentMacScenePlugin::Run()
{
	APE_LOG_FUNC_ENTER();
	/*while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		if (auto planetNode = mPlanetNode.lock())
			planetNode->rotate(0.0017f, ape::Vector3(0, 1, 0), ape::Node::TransformationSpace::LOCAL);
	}*/
	APE_LOG_FUNC_LEAVE();
}

void ape::apeFilamentMacScenePlugin::Step()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

void ape::apeFilamentMacScenePlugin::Stop()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

void ape::apeFilamentMacScenePlugin::Suspend()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

void ape::apeFilamentMacScenePlugin::Restart()
{
	APE_LOG_FUNC_ENTER();
	APE_LOG_FUNC_LEAVE();
}

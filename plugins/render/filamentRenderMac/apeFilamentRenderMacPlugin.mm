//
//  apeFilamentRenderMacPlugin.m
//  apertusVR
//
//  Created by Erik Toth on 2020. 11. 13..
//

#include <utils/EntityManager.h>

#import "apeFilamentRenderMacPlugin.h"
#include "generated/resources/gltf_viewer.h"
#include "generated/resources/resources.h"
#include <sys/stat.h>



struct Vertex {
    filament::math::float2 position;
    uint32_t color;
};

static Vertex TRIANGLE_VERTICES[3] = {
    {{1, 0}, 0xffff0000u},
    {{cos(M_PI * 2 / 3), sin(M_PI * 2 / 3)}, 0xff00ff00u},
    {{cos(M_PI * 4 / 3), sin(M_PI * 4 / 3)}, 0xff0000ffu},
};


static constexpr uint16_t TRIANGLE_INDICES[3] = { 0, 1, 2 };


static std::ifstream::pos_type getFileSize(const char* filename) {
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}


ape::FilamentRenderMacPlugin::FilamentRenderMacPlugin(NSView* nsView)
{
    engine = filament::Engine::create(filament::Engine::Backend::METAL);
    swapChain = engine->createSwapChain(nsView);
    renderer = engine->createRenderer();
    
    
    
    filament::Camera* camera = engine->createCamera(utils::EntityManager::get().create());
    viewer = engine->createView();
    scene = engine->createScene();
    
    viewer->setCamera(camera);
    viewer->setScene(scene);
    
    /*VertexBuffer* vb;
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
    
    
    APE_LOG_FUNC_ENTER();
    mpSceneManager = ape::ISceneManager::getSingletonPtr();
    mpCoreConfig = ape::ICoreConfig::getSingletonPtr();
    mEventDoubleQueue = ape::DoubleQueue<Event>();
    mpEventManager = ape::IEventManager::getSingletonPtr();
    mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_FILE, std::bind(&FilamentRenderMacPlugin::eventCallBack, this, std::placeholders::_1));
    //mpEventManager->connectEvent(ape::Event::Group::NODE, std::bind(&ape::FilamentRenderMacPlugin::eventCallBack, this, std::placeholders::_1));
    /* mpEventManager->connectEvent(ape::Event::Group::LIGHT, std::bind(&FilamentRenderMacPlugin::eventCallBack, this, std::placeholders::_1));
    mpEventManager->connectEvent(ape::Event::Group::CAMERA, std::bind(&FilamentRenderMacPlugin::eventCallBack, this, std::placeholders::_1));
    
    mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_TEXT, std::bind(&FilamentRenderMacPlugin::eventCallBack, this, std::placeholders::_1));
    mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_PLANE, std::bind(&FilamentRenderMacPlugin::eventCallBack, this, std::placeholders::_1));
    mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_BOX, std::bind(&FilamentRenderMacPlugin::eventCallBack, this, std::placeholders::_1));
    mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_CYLINDER, std::bind(&FilamentRenderMacPlugin::eventCallBack, this, std::placeholders::_1));
    mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_CONE, std::bind(&FilamentRenderMacPlugin::eventCallBack, this, std::placeholders::_1));
    mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_TUBE, std::bind(&FilamentRenderMacPlugin::eventCallBack, this, std::placeholders::_1));
    mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_SPHERE, std::bind(&FilamentRenderMacPlugin::eventCallBack, this, std::placeholders::_1));
    mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_TORUS, std::bind(&FilamentRenderMacPlugin::eventCallBack, this, std::placeholders::_1));
    mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_INDEXEDFACESET, std::bind(&FilamentRenderMacPlugin::eventCallBack, this, std::placeholders::_1));
    mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_INDEXEDLINESET, std::bind(&FilamentRenderMacPlugin::eventCallBack, this, std::placeholders::_1));
    mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_CLONE, std::bind(&FilamentRenderMacPlugin::eventCallBack, this, std::placeholders::_1));
    mpEventManager->connectEvent(ape::Event::Group::MATERIAL_FILE, std::bind(&FilamentRenderMacPlugin::eventCallBack, this, std::placeholders::_1));
    mpEventManager->connectEvent(ape::Event::Group::MATERIAL_MANUAL, std::bind(&FilamentRenderMacPlugin::eventCallBack, this, std::placeholders::_1));
    mpEventManager->connectEvent(ape::Event::Group::TEXTURE_MANUAL, std::bind(&FilamentRenderMacPlugin::eventCallBack, this, std::placeholders::_1));
    mpEventManager->connectEvent(ape::Event::Group::TEXTURE_FILE, std::bind(&FilamentRenderMacPlugin::eventCallBack, this, std::placeholders::_1));
    mpEventManager->connectEvent(ape::Event::Group::TEXTURE_UNIT, std::bind(&FilamentRenderMacPlugin::eventCallBack, this, std::placeholders::_1));
    mpEventManager->connectEvent(ape::Event::Group::GEOMETRY_RAY, std::bind(&FilamentRenderMacPlugin::eventCallBack, this, std::placeholders::_1));
    mpEventManager->connectEvent(ape::Event::Group::SKY, std::bind(&FilamentRenderMacPlugin::eventCallBack, this, std::placeholders::_1));
    mpEventManager->connectEvent(ape::Event::Group::WATER, std::bind(&FilamentRenderMacPlugin::eventCallBack, this, std::placeholders::_1));
    mpEventManager->connectEvent(ape::Event::Group::POINT_CLOUD, std::bind(&FilamentRenderMacPlugin::eventCallBack, this, std::placeholders::_1));*/
    /*mpRoot = nullptr;
    mpOgreSceneManager = nullptr;
    mRenderWindows = std::map<std::string, Ogre::RenderWindow*>();
    mGltfLoader = std::unique_ptr<Ogre_glTF::glTFLoader>();
    mFilamentRenderMacPluginConfig = ape::FilamentRenderMacPluginConfig();
    mOgreCameras = std::vector<Ogre::Camera*>();
    mpWindowEventUtilities = nullptr;*/
    mRttList = std::vector<ape::ManualTextureWeakPtr>();
    mpCoreConfig = ape::ICoreConfig::getSingletonPtr();
    APE_LOG_FUNC_LEAVE();
}

ape::FilamentRenderMacPlugin::~FilamentRenderMacPlugin()
{
    APE_LOG_FUNC_ENTER();
    //delete mpRoot;
    APE_LOG_FUNC_LEAVE();
}

void ape::FilamentRenderMacPlugin::eventCallBack(const ape::Event& event)
{
    mEventDoubleQueue.push(event);
}


void ape::FilamentRenderMacPlugin::processEventDoubleQueue()
{
    mEventDoubleQueue.swap();
    while (!mEventDoubleQueue.emptyPop())
    {
        ape::Event event = mEventDoubleQueue.front();
        try
        {
        if (event.group == ape::Event::Group::GEOMETRY_FILE)
        {
            if (auto geometryFile = std::static_pointer_cast<ape::IFileGeometry>(mpSceneManager->getEntity(event.subjectName).lock()))
            {
                std::string geometryName = geometryFile->getName();
                std::string fileName = geometryFile->getFileName();
                std::string parentNodeName = "";
                if (auto parentNode = geometryFile->getParentNode().lock())
                    parentNodeName = parentNode->getName();
                switch (event.type)
                {
                case ape::Event::Type::GEOMETRY_FILE_CREATE:
                    ;
                    break;
                case ape::Event::Type::GEOMETRY_FILE_PARENTNODE:
                {
                   /* auto movableObjectList = mpOgreSceneManager->findMovableObjects("Item", geometryName);
                    if (!movableObjectList.empty())
                    {
                        auto ogreItem = (Ogre::Item*)movableObjectList[0];
                        Ogre::SceneNode* ogreParentNode = nullptr;
                        auto ogreNodeList = mpOgreSceneManager->findSceneNodes(parentNodeName);
                        if (!ogreNodeList.empty())
                        {
                            ogreParentNode = mpOgreSceneManager->getSceneNode(ogreNodeList[0]->getId());
                        }
                        if (ogreParentNode)
                        {
                            ogreParentNode->attachObject(ogreItem);
                        }
                    }*/
                }
                    break;
                case ape::Event::Type::GEOMETRY_FILE_FILENAME:
                {
                    if (fileName.find_first_of(".") != std::string::npos)
                    {
                        std::string fileExtension = fileName.substr(fileName.find_last_of("."));
                        if (fileExtension == ".mesh")
                        {
                            /*Ogre::MeshPtr v2Mesh = Ogre::MeshManager::getSingleton().load(fileName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
                            Ogre::Item* item = mpOgreSceneManager->createItem(fileName, Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME, Ogre::SCENE_DYNAMIC);*/
                        }
                        if (fileExtension == ".glb")
                        {
                            //auto adapter = mGltfLoader->loadGlbResource(fileName);
                            //auto ogreNode = adapter.getFirstSceneNode(mpOgreSceneManager);
                        }
                        if (fileExtension == ".gltf")
                        {
                            std::stringstream filePath;
                            std::size_t found = fileName.find(":");
                            if (found != std::string::npos)
                            {
                                filePath << fileName;
                            }
                            else
                            {
                                std::string separator = "../";
                                found = fileName.find(separator);
                                if (found != std::string::npos)
                                {
                                    struct stat info;
                                    if (stat(fileName.c_str(), &info) == -1)
                                    {
                                        auto found_it = std::find_end(fileName.begin(), fileName.end(), separator.begin(), separator.end());
                                        size_t foundPos = found_it - fileName.begin();
                                        std::stringstream resourceLocationPath;
                                        resourceLocationPath << APE_SOURCE_DIR << fileName.substr(foundPos + 2);
                                        filePath << resourceLocationPath.str();
                                    }
                                    else
                                    {
                                        filePath << fileName;
                                    }
                                }
                                else
                                {
                                    std::stringstream resourceLocationPath;
                                    resourceLocationPath << APE_SOURCE_DIR << fileName;
                                    filePath << resourceLocationPath.str();
                                }
                            }
                            long contentSize = static_cast<long>(getFileSize(filePath.str().c_str()));
                            if (contentSize <= 0) {
                                std::cerr << "Unable to open " << filePath.str() << std::endl;
                            }
                            std::ifstream in(filePath.str().c_str(), std::ifstream::binary | std::ifstream::in);
                            
                            std::vector<uint8_t> buffer(static_cast<unsigned long>(contentSize));
                            if (!in.read((char*) buffer.data(), contentSize)) {
                                std::cerr << "Unable to read " << filePath.str() << std::endl;
                                exit(1);
                            }

                            asset = assetLoader->createInstancedAsset(buffer.data(), buffer.size(), instances.data(), instances.size());
                            
                            buffer.clear();
                            buffer.shrink_to_fit();
                            if (!asset) {
                                std::cerr << "Unable to parse " << filePath.str() << std::endl;
                                exit(1);
                            }
                            std::string gltfPath = filePath.str();
                            ResourceConfiguration configuration;
                            configuration.engine = engine;
                            configuration.gltfPath = gltfPath.c_str();
                            configuration.normalizeSkinningWeights = true;
                            configuration.recomputeBoundingBoxes = false;
                            
                            if (resourceLoader) {
                                resourceLoader = new gltfio::ResourceLoader(configuration);
                            }
                            resourceLoader->asyncBeginLoad(asset);
                            asset->getAnimator();
                            if (instanceToAnimate > -1) {
                                instances[instanceToAnimate]->getAnimator();
                            }
                            
                            engine = engine;
                            names = new utils::NameComponentManager(EntityManager::get());
                            viewer = new SimpleViewer(engine, scene, view, app.instanceToAnimate);
                            app.materials = (app.materialSource == GENERATE_SHADERS) ?
                                    createMaterialGenerator(engine) : createUbershaderLoader(engine);
                            app.loader = AssetLoader::create({engine, app.materials, app.names });
                            if (filename.isEmpty()) {
                                app.asset = app.loader->createInstancedAsset(
                                        GLTF_VIEWER_DAMAGEDHELMET_DATA, GLTF_VIEWER_DAMAGEDHELMET_SIZE,
                                        app.instances.data(), app.instances.size());
                            } else {
                                loadAsset(filename);
                            }

                            arrangeIntoCircle();
                            loadResources(filename);
                            
                            /*auto adapter = mGltfLoader->loadFromFileSystem(filePath.str());
                            auto ogreNode = adapter.getFirstSceneNode(mpOgreSceneManager);
                            Ogre::SceneNode* newOgreParentNode = nullptr;
                            auto ogreNodeList = mpOgreSceneManager->findSceneNodes(parentNodeName);
                            if (!ogreNodeList.empty())
                            {
                                newOgreParentNode = mpOgreSceneManager->getSceneNode(ogreNodeList[0]->getId());
                            }
                            if (newOgreParentNode)
                            {
                                auto oldOgreParentNode = ogreNode->getParentSceneNode();
                                if (newOgreParentNode != oldOgreParentNode)
                                {
                                    oldOgreParentNode->removeChild(ogreNode);
                                    newOgreParentNode->addChild(ogreNode);
                                }
                            }*/
                        }
                    }
                }
                    break;
                case ape::Event::Type::GEOMETRY_FILE_MERGESUBMESHES:
                {
                    ;
                }
                break;
                case ape::Event::Type::GEOMETRY_FILE_EXPORT:
                {
                    ;
                }
                break;
                case ape::Event::Type::GEOMETRY_FILE_MATERIAL:
                {
                    ;
                }
                break;
                case ape::Event::Type::GEOMETRY_FILE_VISIBILITY:
                {
                    ;
                }
                break;
                    default:
                        break;
                }
                
            }
            else if (event.type == ape::Event::Type::GEOMETRY_FILE_DELETE)
            {
                //APE_LOG_DEBUG("GEOMETRY_FILE_DELETE: " << event.subjectName);
                /*auto movableObjectList = mpOgreSceneManager->findMovableObjects("Item", event.subjectName);
                if (!movableObjectList.empty())
                {
                    auto ogreItem = (Ogre::Item*)movableObjectList[0];
                    ogreItem->detachFromParent();
                    mpOgreSceneManager->destroyMovableObject(ogreItem);
                }*/
            }
        }
        }
        catch (std::string err)
        {
            APE_LOG_DEBUG(err);
        }
        mEventDoubleQueue.pop();
    }
}
void ape::FilamentRenderMacPlugin::Stop()
{
    
}

void ape::FilamentRenderMacPlugin::Suspend()
{
    
}

void ape::FilamentRenderMacPlugin::Restart()
{
    
}

void ape::FilamentRenderMacPlugin::Run()
{
   
}

void ape::FilamentRenderMacPlugin::Step()
{
    
}

void ape::FilamentRenderMacPlugin::Init()
{
    
}

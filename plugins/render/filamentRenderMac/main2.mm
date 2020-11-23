#import <Cocoa/Cocoa.h>
#include "apeIFileGeometry.h"
#include <filament/FilamentAPI.h>
#include <filament/Engine.h>
#include <filament/Material.h>
#include <filament/View.h>
#include <filament/Camera.h>
#include <filament/Scene.h>
#include <filament/SwapChain.h>
#include <filament/Renderer.h>
#include <filament/RenderableManager.h>
#include <utils/EntityManager.h>
#include <filament/MaterialInstance.h>
#include <filament/IndexBuffer.h>
#include <filament/VertexBuffer.h>

using namespace filament;

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

int main(int argc, char** argv)
{
    //NSView* myView = [[NSView alloc] initWithFrame:NSMakeRect(0, 0, 100, 100)];
    
    
    
    /*Engine* engine = Engine::create();
    SwapChain* swapChain = engine->createSwapChain(myView);
    Renderer* renderer = engine->createRenderer();

    Camera* camera = engine->createCamera(utils::EntityManager::get().create());
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
    
    utils::Entity renderable = utils::EntityManager::get().create();
    */
}

#include "RigidFrame.h"

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>


using namespace gl;

RigidFrame::RigidFrame() : Mesh("/home/henry/dev/QtProject/OpenGL/models/narrowarrow.obj")
{
}

RigidFrame::~RigidFrame()
{
}

void RigidFrame::draw() const
{
    this->drawInstanced(3);
}

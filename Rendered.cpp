#include "Rendered.h"

#include "Camera.h"
#include "Framebuffer.h"
#include "GLFWApplication.h"
#include "Message.h"
#include "Node.h"
#include "Scene.h"
#include "Viewport.h"
#include "Visitor.h"
#include "VisualManager.h"

using namespace gl;

static Viewport defaultViewport(0,0,1,1);
static DrawVisitor defaultVisitor;

Rendered::Rendered() :
    scene(nullptr),
    camera(nullptr),
    viewport(nullptr),
    framebuffer(nullptr),
    visitor(nullptr),
    singleShot(false),
    count(0)
{

}

bool Rendered::isComplete() const
{
    return (scene != nullptr && camera != nullptr);
}

void Rendered::draw() const
{
    if (!isComplete())
        return;

    unsigned int fwidth = GLFWApplication::ScreenWidth;
    unsigned int fheight = GLFWApplication::ScreenHeight;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    if (framebuffer != nullptr) {
        framebuffer->bind();
        fwidth = framebuffer->width();
        fheight = framebuffer->height();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            msg_warning("Rendered") << "Framebuffer is incomplete";
            return;
        }
    }

    VisualManager::UpdateUniformBufferCamera(*camera);

    Viewport* viewport = (this->viewport != nullptr ? this->viewport : &defaultViewport);
    Visitor* visitor = (this->visitor != nullptr ? this->visitor : &defaultVisitor);

    int x = int(viewport->x() * fwidth);
    int y = int(viewport->y() * fheight);
    int width = int(viewport->rw() * fwidth);
    int height = int(viewport->rh() * fheight);

    glViewport(x, y, width, height);

    Node* node = scene->root();
    node->executeVisitor(visitor);

    if (framebuffer != nullptr)
        framebuffer->unbind();
}

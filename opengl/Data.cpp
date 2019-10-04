#include <opengl/Data.h>

using namespace gl;

BaseData::BaseData(int dataLocation) :
    m_dataLocation(dataLocation),
    m_dirty(true)
{

}

BaseData::~BaseData()
{

}

bool BaseData::isDirty() const
{
    return this->m_dirty;
}

void BaseData::updateIfDirty()
{
    if (!this->m_dirty)
        return;

    update();

    this->m_dirty = false;
}

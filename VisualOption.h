#ifndef VISUALOPTION_H
#define VISUALOPTION_H

// OpenGL
#include <GL/glew.h>


namespace gl {

/**
 * @brief The VisualOption class
 */
class VisualOption
{

public:
    // Specifies how polygons are rendered
    enum PolygonMode {
        POINT,
        LINE,
        FILL
    };

public:
    VisualOption();
    virtual ~VisualOption();

public:

    void push() const;
    void pop() const;

public:

    PolygonMode getPolygonMode() const;
    void setPolygonMode(PolygonMode polygonMode);

private:
    PolygonMode m_polygonMode;

};

}   // namespace gl

#endif

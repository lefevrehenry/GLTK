#ifndef VISUALOPTION_H
#define VISUALOPTION_H

// Glad
#include <glad/glad.h>


namespace gl {

/**
 * @brief The VisualOption class
 */
class VisualOption
{

public:
    // Specifies how polygons are rendered
    enum FillMode {
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
    FillMode fillMode() const;
    void setFillMode(FillMode polygonMode);

private:
    FillMode m_polygonMode;

};

}   // namespace gl

#endif

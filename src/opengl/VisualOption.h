#ifndef GLTK_VISUALOPTION_H
#define GLTK_VISUALOPTION_H

#include <OpenGLAttribute.h>

// Glad
#include <glad/glad.h>

// Standard Library
#include <map>


namespace gl {

/**
 * @brief The VisualParam struct
 */
struct VisualParam {
//    // Specifies how primives are rendered
//    enum class PolygonMode {
//        POINT = GL_POINT,
//        LINE = GL_LINES,
//        FILL = GL_FILL
//    };

    // Specifies what type of primives are rendered
    enum class PrimitiveType {
        POINTS = GL_POINTS,
        LINES = GL_LINES,
        TRIANGLES = GL_TRIANGLES
    };

    static VisualParam DefaultInstance() {
        VisualParam param;
        param.instancing = 1;
        param.primitiveType = PrimitiveType::TRIANGLES;
        return param;
    }

    unsigned int instancing;
    PrimitiveType primitiveType;

};

/**
 * @brief The VisualOption class
 */
class VisualOption
{

public:
    VisualOption();
    virtual ~VisualOption();

public:
    template< AttributeName N >
    void set(typename OpenGL<N>::Type value)
    {
        this->m_attributeStack[N] = OpenGLAttribut<N>::Create(value);
    }

public:
    void pushAttribute() const;
    void popAttribute() const;

private:
    std::map< AttributeName, BaseOpenGLAttribut::SPtr > m_attributeStack;

};

}   // namespace gl

#endif

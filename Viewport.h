#ifndef VIEWPORT_H
#define VIEWPORT_H


namespace gl {

/**
 * @brief The Viewport class
 */
class Viewport
{

public:
    Viewport();
    Viewport(float x, float y, float rw, float rh);

public:
    float x() const;
    float y() const;
    float rw() const;
    float rh() const;

    bool contains(float x, float y) const;

public:
    void set(float x, float y, float rw, float rh);

private:
    float m_x;
    float m_y;
    float m_rw;
    float m_rh;

};

}   // namespace gl

#endif

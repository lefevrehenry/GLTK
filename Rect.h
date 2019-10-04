#ifndef RECT_H
#define RECT_H


namespace gl {

/**
 * @brief The Rect class
 */
class Rect
{

public:
    Rect();
    Rect(int x, int y, int width, int height);

public:
    int x() const;
    int y() const;
    int width() const;
    int height() const;

    bool contains(int x, int y) const;

public:
    void set(int x, int y, int width, int height);

private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;

};

}   // namespace gl

#endif

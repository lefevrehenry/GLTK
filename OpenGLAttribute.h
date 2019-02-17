#ifndef OPENGLATTRIBUTE_H
#define OPENGLATTRIBUTE_H

#include "Message.h"

// Standard Library
#include <algorithm>
#include <array>
#include <stack>


namespace gl {

/**
 * @brief The StateAttribute enum
 */
enum StateAttribute {
    ClearColor,
    CullFace,
    DepthFunc,
    DepthMask,
    DepthTest,
    Viewport
};

/**
 * @brief The BaseOpenGLAttribute class
 */
class BaseOpenGLAttribute
{
};

/**
 * @brief The OpenGLAttribute class
 */
template <typename T, int N>
class OpenGLAttribute : public BaseOpenGLAttribute
{

    static_assert( N > 0 && N < 5, "" );

public:
    OpenGLAttribute()
    {
        this->clear();
    }
    OpenGLAttribute(T data[N])
    {
        std::copy(data, data+N, this->m_data.data());
    }
    OpenGLAttribute(T args...)
    {
        set(args);
    }
    template< int NN = N, typename std::enable_if<NN==1,int>::type = 0 >
    OpenGLAttribute(const T& t1)
    {
        static_assert(N == 1, "");
        set(t1);
    }
    template< int NN = N, typename std::enable_if<NN==2,int>::type = 0 >
    OpenGLAttribute(const T& t1, const T& t2)
    {
        static_assert(N == 2, "");
        set(t1, t2);
    }
    template< int NN = N, typename std::enable_if<NN==3,int>::type = 0 >
    OpenGLAttribute(const T& t1, const T& t2, const T& t3)
    {
        static_assert(N == 3, "");
        set(t1, t2, t3);
    }
    template< int NN = N, typename std::enable_if<NN==4,int>::type = 0 >
    OpenGLAttribute(const T& t1, const T& t2, const T& t3, const T& t4)
    {
        static_assert(N == 4, "");
        set(t1, t2, t3, t4);
    }

public:
    void clear()
    {
        this->fill(T());
    }

    void fill(const T& value)
    {
        this->m_data.fill(value);
    }

public:
    template< int NN = N, typename std::enable_if<NN==1,int>::type = 0 >
    void set(const T& t1)
    {
        this->m_data[0] = t1;
    }
    template< int NN = N, typename std::enable_if<NN==2,int>::type = 0 >
    void set(const T& t1, const T& t2)
    {
        this->m_data[0] = t1;
        this->m_data[1] = t2;
    }
    template< int NN = N, typename std::enable_if<NN==3,int>::type = 0 >
    void set(const T& t1, const T& t2, const T& t3)
    {
        this->m_data[0] = t1;
        this->m_data[1] = t2;
        this->m_data[2] = t3;
    }
    template< int NN = N, typename std::enable_if<NN==4,int>::type = 0 >
    void set(const T& t1, const T& t2, const T& t3, const T& t4)
    {
        this->m_data[0] = t1;
        this->m_data[1] = t2;
        this->m_data[2] = t3;
        this->m_data[3] = t4;
    }

public:
    T* data()
    {
        return this->m_data.data();
    }

    const T* data() const
    {
        return this->m_data.data();
    }

public:
    template< int NN = N, typename std::enable_if<NN>=1,int>::type = 0 >
    T& x()
    {
        static_assert (N >= 1, "");
        return this->m_data[0];
    }
    template< int NN = N, typename std::enable_if<NN>=2,int>::type = 0 >
    T& y()
    {
        static_assert (N >= 2, "");
        return this->m_data[1];
    }
    template< int NN = N, typename std::enable_if<NN>=3,int>::type = 0 >
    T& z()
    {
        static_assert (N >= 3, "");
        return this->m_data[2];
    }
    template< int NN = N, typename std::enable_if<NN>=4,int>::type = 0 >
    T& w()
    {
        static_assert (N >= 4, "");
        return this->m_data[3];
    }
    template< int NN = N, typename std::enable_if<NN>=1,int>::type = 0 >
    const T& x() const
    {
        static_assert (N >= 1, "");
        return this->m_data[0];
    }
    template< int NN = N, typename std::enable_if<NN>=2,int>::type = 0 >
    const T& y() const
    {
        static_assert (N >= 2, "");
        return this->m_data[1];
    }
    template< int NN = N, typename std::enable_if<NN>=3,int>::type = 0 >
    const T& z() const
    {
        static_assert (N >= 3, "");
        return this->m_data[2];
    }
    template< int NN = N, typename std::enable_if<NN>=4,int>::type = 0 >
    const T& w() const
    {
        static_assert (N >= 4, "");
        return this->m_data[3];
    }

public:
    T& operator[](size_t i)
    {
        assert(i < N);
        return this->m_data[i];
    }

    const T& operator[](size_t i) const
    {
        assert(i < N);
        return this->m_data[i];
    }

private:
    std::array<T,N> m_data;

};

}  // namespace

#endif

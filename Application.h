#ifndef APPLICATION_H
#define APPLICATION_H

// Standard Library
#include <vector>


namespace gl {

class Program;

/**
 * @brief The Application class
 */
class Application
{

protected:
    Application();
    virtual ~Application();

public:

    virtual void init() = 0;

    virtual void loop() = 0;

private:
    // C++ 11
    // =======
    // We can use the better technique of deleting the methods
    // we don't want.
    Application(const Application&)     = delete;
    void operator=(const Application&)  = delete;

public:

    unsigned int getNbProgram() const;

    const gl::Program* getProgram(unsigned int i) const;

    gl::Program* addProgram();

private:

    std::vector<const gl::Program*> m_programList;

};

}   // namespace gl

#endif

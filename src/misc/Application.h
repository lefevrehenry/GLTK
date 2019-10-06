#ifndef APPLICATION_H
#define APPLICATION_H


namespace gl {

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

public:
    static unsigned int ScreenWidth;
    static unsigned int ScreenHeight;

private:
    // C++ 11
    // =======
    // We can use the better technique of deleting the methods
    // we don't want.
    Application(const Application&)     = delete;
    void operator=(const Application&)  = delete;

};

}   // namespace gl

#endif

#ifndef FRAMEGRAPH_H
#define FRAMEGRAPH_H


namespace gl {

class FrameObject;

/**
 * @brief The FrameGraph class
 */
class FrameGraph
{

public:
    FrameGraph();
    FrameGraph(FrameObject* frameObject);
    virtual ~FrameGraph();

public:
    FrameObject* root();
    void setRoot(FrameObject* frameObject);

private:
    FrameObject* m_rootNode;

};

}   // namespace gl

#endif

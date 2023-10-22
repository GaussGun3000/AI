#include "BidirectionalDFS.h"

inline uint qHash(const Node& node)
{ 
    return qHash(node.getState());
}

void DirectionalSearch::run()
{
}

void DirectionalSearch::createNodeLayer()
{
}

DirectionalSearch::DirectionalSearch(QMutex* nsp, uint32_t maxDepth):
    nextStepPermission(nsp), maxDepth(maxDepth)
{
    // connect(this, DirectionalSearch::updateStats, this->parent, )
}

BidirectionalDFS::BidirectionalDFS()
{

}

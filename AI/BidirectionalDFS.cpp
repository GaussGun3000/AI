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

DirectionalSearch::DirectionalSearch(Node* ods, Node* tds, QMutex* odm, QMutex* tdm, int32_t maxDepth)
{
}

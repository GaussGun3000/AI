#include "BidirectionalDFS.h"

inline uint qHash(const Node& node)
{ 
    return qHash(node.getState());
}

void DirectionalSearch::run()
{
}

void DirectionalSearch::createNodeLayerStart()
{
}

void DirectionalSearch::createNodeLayerTarget()
{
}

DirectionalSearch::DirectionalSearch(QMutex* nsp, uint32_t maxDepth, QVector<int>& start, QVector<int>& target):
    nextStepPermission(nsp), maxDepth(maxDepth)
{
    QScopedPointer<Node> nullparent(nullptr);
    lastStartNode = Node(start, nullparent, Node::Action::NoAction, 0, 0);
    lastTargetNode = Node(start, nullparent, Node::Action::NoAction, 0, 0);
    // connect(this, DirectionalSearch::updateStats, this->parent, )
}

BidirectionalDFS::BidirectionalDFS()
{

}

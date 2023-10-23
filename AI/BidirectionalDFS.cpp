#include "BidirectionalDFS.h"

inline uint qHash(const Node& node)
{ 
    return qHash(node.getState());
}

void DirectionalSearch::run()
{
    uint32_t depth = 0;
    while (resulting_depth == -1 && depth <= maxDepth)
    {
        createNodeLayerStart();
        createNodeLayerTarget();
        depth++;
        updateStats(depth);
        nextStepPermission->lock();
        nextStepPermission->unlock();       
    }
}

void DirectionalSearch::createNodeLayerStart()
{
    auto actions = lastStartNode.getAvailableActions();
    for (auto action : actions)
    {
        QScopedPointer<Node> parentNode(&lastStartNode);
        auto node(new Node(parentNode, action));
        if (targetDirectionSet.contains(*node))
        {
            auto tdNode = targetDirectionSet.find(*node);
            resulting_depth = node->getDepth() + tdNode->getDepth();
        }
        else
        {
            lastStartNode = *node;
            startDirectionSet.insert(*node);
        }
        delete node;
    }
}

void DirectionalSearch::createNodeLayerTarget()
{
    auto actions = lastTargetNode.getAvailableActions();
    for (auto action : actions)
    {
        QScopedPointer<Node> parentNode(&lastTargetNode);
        auto node(new Node(parentNode, action));
        if (startDirectionSet.contains(*node))
        {
            auto tdNode = startDirectionSet.find(*node);
            resulting_depth = node->getDepth() + tdNode->getDepth();
        }
        else
        {
            lastTargetNode = *node;
            targetDirectionSet.insert(*node);
        }
        delete node;
    }
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

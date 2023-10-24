#include "BidirectionalDFS.h"

inline uint qHash(const Node& node)
{ 
    return qHash(node.getState());
}

inline uint qHash(const QSharedPointer<Node>& node)
{
    return qHash(node->getState());
}

bool operator==(const QSharedPointer<Node>& left, const QSharedPointer<Node>& right)
{
    return left->getState() == right->getState();
}

void DirectionalSearch::run()
{
    uint32_t depth = 0;
    nextStepPermission->lock();
    nextStepPermission->unlock();
    while (resulting_depth == -1 && depth <= maxDepth)
    {
        createNodeLayerStart();
        createNodeLayerTarget();
        depth++;
        emit updateStats(depth);
        nextStepPermission->lock();
        nextStepPermission->unlock();       
    }
    resulting_depth = resulting_depth;
}

void DirectionalSearch::createNodeLayerStart()
{
    auto actions = lastStartNode -> getAvailableActions();
    for (auto action : actions)
    {
        Node* newNode = new Node(lastStartNode, action);
        QSharedPointer<Node> node(newNode);
        if (targetDirectionSet.contains(node))
        {
            auto tdNode = targetDirectionSet.find(node);
            resulting_depth = node->getDepth() + tdNode->data()->getDepth();
        }
        else
        {
            lastStartNode = node;
            startDirectionSet.insert(node);
            nodes.append(node);
        }
    }
}

void DirectionalSearch::createNodeLayerTarget()
{
    auto actions = lastTargetNode->getAvailableActions();
    for (auto action : actions)
    {
        QSharedPointer<Node> node(new Node(lastTargetNode, action));
        if (startDirectionSet.contains(node))
        {
            auto tdNode = startDirectionSet.find(node);
            resulting_depth = node->getDepth() + tdNode->data()->getDepth();
        }
        else
        {
            lastTargetNode = node;
            targetDirectionSet.insert(node);
            nodes.append(node);
        }
    }
}

DirectionalSearch::DirectionalSearch(QMutex* nsp, uint32_t maxDepth, QVector<int>& start, QVector<int>& target):
    nextStepPermission(nsp), maxDepth(maxDepth)
{
    QSharedPointer<Node> nullparent(nullptr);
    lastStartNode = QSharedPointer<Node>::create(start, nullptr, Node::Action::NoAction, 0, 0);
    lastTargetNode = QSharedPointer<Node>::create(target, nullptr, Node::Action::NoAction, 0, 0);
}

void DirectionalSearch::setMaxDepth(uint32_t maxDepth)
{
    this->maxDepth = maxDepth;
}

BidirectionalDFS::BidirectionalDFS()
{

}
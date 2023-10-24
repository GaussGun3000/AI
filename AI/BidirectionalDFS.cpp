#include "BidirectionalDFS.h"
#include <qdebug.h>

inline uint qHash(const Node& node)
{ 
    return qHash(node.getState());
}

/*
inline uint qHash(const QSharedPointer<Node>& node)
{
    return qHash(node->getState());
}

bool operator==(const QSharedPointer<Node>& left, const QSharedPointer<Node>& right)
{
    return left->getState() == right->getState();
}
*/

inline uint qHash(const NodePtr& wrapper)
{
    return qHash(wrapper.node->getState());
}

inline bool operator==(const NodePtr& left, const NodePtr& right)
{
    return left.node->getState() == right.node->getState();
}


void DirectionalSearch::run()
{
    currentDepth = 0;
    nextStepPermission->lock();
    nextStepPermission->unlock();
    while (resultingDepth == -1 && (!startStack.isEmpty() || !targetStack.isEmpty()))
    {
        createNodeLayerStart();
        createNodeLayerTarget();
        emit updateStats(currentDepth);
        nextStepPermission->lock();
        nextStepPermission->unlock();   
    }
    resultingDepth = resultingDepth;
}

void DirectionalSearch::createNodeLayerStart()
{
    if (startStack.isEmpty())
        return;
    lastStartNode = startStack.pop();
    if (lastStartNode->getDepth() >= maxDepth)
        return;

    auto actions = lastStartNode -> getAvailableActions();
    for (auto action : actions)
    {
        Node* newNode = new Node(lastStartNode, action);
        QSharedPointer<Node> node(newNode);
        qDebug() << targetDirectionSet;
        if (targetDirectionSet.contains(node))
        {
            auto tdNode = targetDirectionSet.find(node);
            resultingDepth = node->getDepth() + tdNode->data()->getDepth();
        }
        else
        {
            if (node->getDepth() > currentDepth) currentDepth=node -> getDepth();
            startStack.push(node);
           // lastStartNode = node;
            startDirectionSet.insert(node);
            nodes.append(node);
        }
    }
}

void DirectionalSearch::createNodeLayerTarget()
{
    if (targetStack.isEmpty())
        return;
    lastTargetNode = targetStack.pop();
    if (lastTargetNode->getDepth() >= maxDepth)
        return;

    auto actions = lastTargetNode->getAvailableActions();
    for (auto action : actions)
    {
        QSharedPointer<Node> node(new Node(lastTargetNode, action));
        if (startDirectionSet.contains(node))
        {
            auto tdNode = startDirectionSet.find(node);
            resultingDepth = node->getDepth() + tdNode->data()->getDepth();
        }
        else
        {
            if (node->getDepth() > currentDepth) currentDepth = node->getDepth();
            targetStack.push(node);
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
    startDirectionSet.insert(lastStartNode);
    targetDirectionSet.insert(lastTargetNode);
    startStack.push(lastStartNode);
    targetStack.push(lastTargetNode);
}

void DirectionalSearch::setMaxDepth(uint32_t maxDepth)
{
    this->maxDepth = maxDepth;
}

uint32_t DirectionalSearch::getResultingDepth()
{
    return this->resultingDepth;
}

BidirectionalDFS::BidirectionalDFS()
{
}


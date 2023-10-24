#include "BidirectionalDFS.h"
#include <qdebug.h>

inline uint qHash(const Node& node)
{ 
    return qHash(node.getState());
}

uint statehash(const QVector<int>& vector)
{
    uint hashValue = 0;
    uint base = 1;
    for (int i = 0; i < vector.size(); ++i) {
        hashValue += vector[i] * base;
        base *= 9;
    }
    return hashValue;
}

inline uint qHash(const NodePtr& wrapper)
{
    return statehash(wrapper.node->getState());
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
    qDebug() << nodes.size();
    nodes.clear();
}

void DirectionalSearch::createNodeLayerStart()
{
    if (startStack.isEmpty())
        return;
    lastStartNode = startStack.pop();
    if (lastStartNode.node->getDepth() >= maxDepth)
        return;

    auto actions = lastStartNode.node -> getAvailableActions();
    for (auto action : actions)
    {
        Node* newNode = new Node(lastStartNode, action);
        QSharedPointer<Node> node(newNode);
        NodePtr nodeptr(node);
        if (targetDirectionSet.contains(nodeptr))
        {
            auto tdNode = targetDirectionSet.find(nodeptr);
            resultingDepth = node->getDepth() + tdNode->node->getDepth();
        }
        else
        {
            if (node.node->getDepth() > currentDepth) currentDepth=node.node -> getDepth();
            startStack.push(node);
           // lastStartNode = node;
            startDirectionSet.insert(nodeptr);
            nodes.append(node);
        }
    }
}

void DirectionalSearch::createNodeLayerTarget()
{
    if (targetStack.isEmpty())
        return;
    lastTargetNode = targetStack.pop();
    if (lastTargetNode.node->getDepth() >= maxDepth)
        return;

    auto actions = lastTargetNode.node->getAvailableActions();
    for (auto action : actions)
    {
        QSharedPointer<Node> node(new Node(lastTargetNode, action));
        NodePtr nodeptr(node);
        if (startDirectionSet.contains(nodeptr))
        {
            auto tdNode = startDirectionSet.find(nodeptr);
            resultingDepth = node->getDepth() + tdNode->node->getDepth();
        }
        else
        {
            if (node->getDepth() > currentDepth) currentDepth = node->getDepth();
            targetStack.push(node);
            lastTargetNode = node;
            targetDirectionSet.insert(nodeptr);
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
    startDirectionSet.insert(NodePtr(lastStartNode));
    targetDirectionSet.insert(NodePtr(lastTargetNode));
    startStack.push(lastStartNode);
    targetStack.push(lastTargetNode);
}

void DirectionalSearch::setMaxDepth(uint32_t maxDepth)
{
    this->maxDepth = maxDepth;
}

int32_t DirectionalSearch::getResultingDepth()
{
    return this->resultingDepth;
}

BidirectionalDFS::BidirectionalDFS()
{
}


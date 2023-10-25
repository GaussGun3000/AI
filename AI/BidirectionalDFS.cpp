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


void BiDirectionalSearch::run()
{
    currentDepth = 0;
    nextStepPermission->lock();
    nextStepPermission->unlock();
    while (resultingDepth == -1 && (!startQueue.isEmpty() || !targetQueue.isEmpty()))
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

void BiDirectionalSearch::createNodeLayerStart()
{
    if (startQueue.isEmpty())
        return;
    lastStartNode = startQueue.dequeue();
    if (lastStartNode->getDepth() >= maxDepth)
        return;

    auto actions = lastStartNode -> getAvailableActions();
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
            if (node->getDepth() > currentDepth) currentDepth=node -> getDepth();
            startQueue.enqueue(node);
            startDirectionSet.insert(nodeptr);
            nodes.append(node);
        }
    }
}

void BiDirectionalSearch::createNodeLayerTarget()
{
    if (targetQueue.isEmpty())
        return;
    lastTargetNode = targetQueue.dequeue();
    if (lastTargetNode -> getDepth() >= maxDepth)
        return;

    auto actions = lastTargetNode -> getAvailableActions();
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
            targetQueue.enqueue(node);
            targetDirectionSet.insert(nodeptr);
            nodes.append(node);
        }
    }
}

BiDirectionalSearch::BiDirectionalSearch(QMutex* nsp, uint32_t maxDepth, QVector<int>& start, QVector<int>& target):
    nextStepPermission(nsp), maxDepth(maxDepth)
{
    QSharedPointer<Node> nullparent(nullptr);
    lastStartNode = QSharedPointer<Node>::create(start, nullptr, Node::Action::NoAction, 0, 0);
    lastTargetNode = QSharedPointer<Node>::create(target, nullptr, Node::Action::NoAction, 0, 0);
    startDirectionSet.insert(NodePtr(lastStartNode));
    targetDirectionSet.insert(NodePtr(lastTargetNode));
    startQueue.enqueue(lastStartNode);
    targetQueue.enqueue(lastTargetNode);
}

void BiDirectionalSearch::setMaxDepth(uint32_t maxDepth)
{
    this->maxDepth = maxDepth;
}

int32_t BiDirectionalSearch::getResultingDepth()
{
    return this->resultingDepth;
}

quint32 BiDirectionalSearch::getNodesNumSize()
{
    return this->nodes.size();
}

//-----------------------------------------------------------


void DFS::run()
{
    currentDepth = 0;
    nextStepPermission->lock();
    nextStepPermission->unlock();
    while (resultingDepth == -1 && (!dfsStack.isEmpty()))
    {
        createNodeLayer();
        emit updateStats(currentDepth);
        nextStepPermission->lock();
        nextStepPermission->unlock();
    }
    qDebug() << nodes.size();
    nodes.clear();
}

void DFS::createNodeLayer()
{
    if (dfsStack.isEmpty())
        return;
    lastNode = dfsStack.pop();
    if (lastNode->getDepth() >= maxDepth)
        return;

    auto actions = lastNode->getAvailableActions();
    for (auto action : actions)
    {
        Node* newNode = new Node(lastNode, action);
        QSharedPointer<Node> node(newNode);
        if (*targetNode == *node)
        {
            resultingDepth = node->getDepth();
        }
        else
        {
            if (node->getDepth() > currentDepth) currentDepth = node->getDepth();
            dfsStack.push(node);
            nodes.append(node);
        }
    }
}

DFS::DFS(QMutex* nsp, uint32_t maxDepth, QVector<int>& start, QVector<int>& target):nextStepPermission(nsp), maxDepth(maxDepth)
{
    QSharedPointer<Node> nullparent(nullptr);
    lastNode = QSharedPointer<Node>::create(start, nullptr, Node::Action::NoAction, 0, 0);
    targetNode = QSharedPointer<Node>::create(target, nullptr, Node::Action::NoAction, 0, 0);
    dfsStack.push(lastNode);
}

void DFS::setMaxDepth(uint32_t maxDepth)
{
    this->maxDepth = maxDepth;
}

int32_t DFS::getResultingDepth()
{
    return this->resultingDepth;
}

quint32 DFS::getNodesNumSize()
{
    return this->nodes.size();
}

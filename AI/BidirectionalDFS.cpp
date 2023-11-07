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
    init();
    currentDepth = 0;
    nextStepPermission->lock();
    nextStepPermission->unlock();
    while (resultingDepth == -1 && (!startQueue.isEmpty() || !targetQueue.isEmpty()))
    {
        createNodeLayerStart();
        if (resultingDepth == -1) createNodeLayerTarget();
        emit updateStats(currentDepth);
        steps++;
        nextStepPermission->lock();
        nextStepPermission->unlock();
    }
    qDebug() << nodes.size();
    cleanup();
}

void BiDirectionalSearch::createNodeLayerStart()
{
    if (startQueue.isEmpty())
        return;
    lastStartNode = startQueue.dequeue();
    //if (lastStartNode->getDepth() >= maxDepth)
    //    return;

    auto actions = lastStartNode->getAvailableActions();
    qDebug() << "start childes:";
    for (auto action : actions)
    {
        Node* newNode = new Node(lastStartNode, action);
        qDebug() << newNode->getStateString();
        QSharedPointer<Node> node(newNode);
        NodePtr nodeptr(node);
        if (targetDirectionSet.contains(nodeptr))
        {
            auto tdNode = targetDirectionSet.find(nodeptr);
            resultingDepth = node->getDepth() + tdNode->node->getDepth();
        }
        else
        {
            if (node->getDepth() > currentDepth) currentDepth = node->getDepth();
            if (!startDirectionSet.contains(nodeptr))
            {
                nodeCount++;
                startQueue.enqueue(node);
                startDirectionSet.insert(nodeptr);
            }
            nodes.append(node);
        }
    }
}

void BiDirectionalSearch::createNodeLayerTarget()
{
    if (targetQueue.isEmpty())
        return;
    lastTargetNode = targetQueue.dequeue();
    //if (lastTargetNode->getDepth() >= maxDepth)
    //    return;

    auto actions = lastTargetNode->getAvailableActions();
    qDebug() << "target childes:";
    for (auto action : actions)
    {
        QSharedPointer<Node> node(new Node(lastTargetNode, action));
        qDebug() << node->getStateString();
        NodePtr nodeptr(node);
        if (startDirectionSet.contains(nodeptr))
        {
            auto tdNode = startDirectionSet.find(nodeptr);
            resultingDepth = node->getDepth() + tdNode->node->getDepth();
        }
        else
        {
            if (node->getDepth() > currentDepth) currentDepth = node->getDepth();
            if (!targetDirectionSet.contains(nodeptr))
            {
                nodeCount++;
                targetQueue.enqueue(node);
                targetDirectionSet.insert(nodeptr);
            }
            nodes.append(node);
        }
    }
}

void BiDirectionalSearch::init()
{
    lastStartNode = QSharedPointer<Node>(startNode);
    lastTargetNode = QSharedPointer<Node>(target);
    startDirectionSet.insert(NodePtr(lastStartNode));
    targetDirectionSet.insert(NodePtr(lastTargetNode));
    startQueue.enqueue(lastStartNode);
    targetQueue.enqueue(lastTargetNode);
    resultingDepth = -1;
    nodeCount = 0;
    steps = 0;
}

void BiDirectionalSearch::cleanup()
{
    startQueue.clear();
    targetQueue.clear();
    startDirectionSet.clear();
    targetDirectionSet.clear();
    nodes.clear();
}

BiDirectionalSearch::BiDirectionalSearch(QMutex* nsp, uint32_t maxDepth, QVector<int>& start, QVector<int>& target) :
    nextStepPermission(nsp), maxDepth(maxDepth)
{
    QSharedPointer<Node> nullparent(nullptr);
    this->startNode = QSharedPointer<Node>::create(start, nullptr, Node::Action::NoAction, 0, 0);
    this->target = QSharedPointer<Node>::create(target, nullptr, Node::Action::NoAction, 0, 0);

}

void BiDirectionalSearch::setMaxDepth(uint32_t maxDepth)
{
    this->maxDepth = maxDepth;
}

int32_t BiDirectionalSearch::getResultingDepth()
{
    return this->resultingDepth;
}

quint32 BiDirectionalSearch::getNodeCount()
{
    return this->nodeCount;
}

quint32 BiDirectionalSearch::getStepCount()
{
    return this->steps;
}


QString BiDirectionalSearch::getLastStartNodeStateString() const
{
    return lastStartNode->getStateString();
}

QString BiDirectionalSearch::getLastTargetNodeStateString() const
{
    return lastTargetNode->getStateString();
}

QString BiDirectionalSearch::getParentLastStartNodeStateString() const
{
    return lastStartNode->getParent()->getStateString();
}

QString BiDirectionalSearch::getParentLastTargetNodeStateString() const
{
    return lastTargetNode->getParent()->getStateString();
}

//---------------------------------------------

void DFS::run()
{
    init();
    currentDepth = 0;
    nextStepPermission->lock();
    nextStepPermission->unlock();
    while (resultingDepth == -1 && (!dfsStack.isEmpty()))
    {
        createNodeLayer();
        emit updateStats(currentDepth);
        steps++;
        nextStepPermission->lock();
        nextStepPermission->unlock();
    }
    qDebug() << uniqueStatesSet.size();
    cleanup();
}

void DFS::createNodeLayer()
{
    if (dfsStack.isEmpty())
        return;
    lastNode = dfsStack.pop();
    /*   if (lastNode->getDepth() >= maxDepth)
           return;*/

    auto actions = lastNode->getAvailableActions();
    for (auto action : actions)
    {
        Node* newNode = new Node(lastNode, action);
        QSharedPointer<Node> node(newNode);
        NodePtr nodeptr(node);
        if (*targetNode == *node)
        {
            resultingDepth = node->getDepth();
        }
        else
        {
            if (node->getDepth() > currentDepth) currentDepth = node->getDepth();
            if (!uniqueStatesSet.contains(nodeptr))
            {
                dfsStack.push(node);
                uniqueStatesSet.insert(nodeptr);
                nodeCount++;
            }
            // nodes.append(node);
        }
    }
}

DFS::DFS(QMutex* nsp, uint32_t maxDepth, QVector<int>& start, QVector<int>& target) :nextStepPermission(nsp), maxDepth(maxDepth)
{
    QSharedPointer<Node> nullparent(nullptr);
    targetNode = QSharedPointer<Node>::create(target, nullptr, Node::Action::NoAction, 0, 0);
    startNode = QSharedPointer<Node>::create(start, nullptr, Node::Action::NoAction, 0, 0);
}

void DFS::setMaxDepth(uint32_t maxDepth)
{
    this->maxDepth = maxDepth;
}

int32_t DFS::getResultingDepth()
{
    return this->resultingDepth;
}

quint32 DFS::getNodeCount()
{
    return this->nodeCount;
}

quint32 DFS::getStepCount()
{
    return this->steps;
}

QString DFS::getLastNodeStateString() const
{
    return this->lastNode->getStateString();
}

QString DFS::getParentLastNodeStateString() const
{
    return this->lastNode->getParent()->getStateString();
}



void DFS::init()
{
    lastNode = QSharedPointer<Node>(startNode);
    dfsStack.push(lastNode);
    resultingDepth = -1;
    nodeCount = 0;
    steps = 0;
}

void DFS::cleanup()
{
    dfsStack.clear();
    uniqueStatesSet.clear();
    //lastNode.reset();
}
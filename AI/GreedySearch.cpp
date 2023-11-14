#include "GreedySearch.h"
#include <QSet>
#include <algorithm>
#include <QDebug>

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

inline uint qHash(const Node& node)
{
    return statehash(node.getState());
}

inline uint qHash(const NodePtr& wrapper)
{
    return statehash(wrapper.node->getState());
}

inline bool operator==(const NodePtr& left, const NodePtr& right)
{
    return left.node->getState() == right.node->getState();
}


GreedySearch::GreedySearch(QMutex* mutex, HFunction heuristic, const QVector<int>& startState, const QVector<int>& targetState)
    : nextStepPermission(mutex), heuristic(heuristic),
    startState(startState), targetState(targetState) {
    // Constructor implementation
    // You may initialize other members if necessary
}

GreedySearch::GreedySearch()
{
}

int GreedySearch::h(const QSharedPointer<Node>& node) {
    QVector<int> state = node->getState();
    int count = 0;
    if (this->heuristic == HFunction::h1)
    {
        for (int i = 0; i < 9; ++i) {
            if (state[i] != targetState[i]) {
                ++count;
            }
        }
    }
    else if (this->heuristic == HFunction::h2)
    {
        for (int i = 0; i < 9; ++i) {
            int targetIndex = targetState.indexOf(state[i]);
            if (i - targetIndex != 0) // if == 0: current number already is on the right position
            {
                if (h2Cost.contains(QString::number(i) + QString::number(targetIndex)))
                    count = count + h2Cost.value(QString::number(i) + QString::number(targetIndex));
                else if (h2Cost.contains(QString::number(targetIndex) + QString::number(i)))
                    count = count + h2Cost.value(QString::number(targetIndex) + QString::number(i));
            }
        }
    }
    node->setH(count);
    return count;
}

void GreedySearch::init()
{
    QSharedPointer<Node> startNode(new Node(startState, nullptr, Node::Action::NoAction, 0, 0));
    h(startNode);
    priorityQueue.push(startNode);
    uniqueStates.insert(NodePtr(startNode));
    lastNode = startNode;
    resultingDepth = -1;
    currentDepth = 0;
    steps = 0;
    nodeCount = 0;
}

void GreedySearch::cleanup()
{
    while (!priorityQueue.empty()) {
        priorityQueue.pop();
    }
    uniqueStates.clear();
}

void GreedySearch::iteration()
{
    QSharedPointer<Node> currentNode = priorityQueue.top();
    priorityQueue.pop();
    lastNode = currentNode;
    if (currentNode->getDepth() > currentDepth)
        currentDepth = currentNode->getDepth();
    // Generate and process children nodes
    QList<Node::Action> actions = currentNode->getAvailableActions();
    for (Node::Action action : actions) {
        QSharedPointer<Node> childNode(new Node(currentNode, action));
        h(childNode);

        if (childNode->getState() == targetState) {
            lastNode = childNode;
            resultingDepth = childNode->getDepth();
        }

        NodePtr wrapper(childNode);
        if (!uniqueStates.contains(wrapper)) {
            priorityQueue.push(childNode);
            uniqueStates.insert(wrapper);
            nodeCount++;
        }
    }
}

int32_t GreedySearch::getResultingDepth()
{
    return resultingDepth;
}

quint32 GreedySearch::getNodeCount()
{
    return nodeCount;
}

quint32 GreedySearch::getStepCount()
{
    return steps;
}

QString GreedySearch::getLastNodeStateString() const
{
    return this->lastNode->getStateString();
}

QString GreedySearch::getParentLastNodeStateString() const
{
    return this->lastNode->getParent()->getStateString();
}

void  GreedySearch::run() 
{
    init();
    nextStepPermission->lock();
    nextStepPermission->unlock();
    while (resultingDepth == -1 && !priorityQueue.empty()) {
        emit updateStats(currentDepth);
        iteration();
        steps++;
        nextStepPermission->lock();
        nextStepPermission->unlock();
    }
    qDebug() << "steps: " << steps << "nodes: " << uniqueStates.size() << "queue size: " << priorityQueue.size();
    cleanup();
}

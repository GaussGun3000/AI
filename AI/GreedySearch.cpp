#include "GreedySearch.h"
#include <QSet>
#include <algorithm>

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


GreedySearch::GreedySearch(QMutex* mutex, HFunction heuristic,
    const QVector<int>& startState,
    const QVector<int>& targetState)
    : mutex(mutex), heuristic(heuristic),
    startState(startState), targetState(targetState) {
    // Constructor implementation
    // You may initialize other members if necessary
}

int GreedySearch::h(const QSharedPointer<Node> node) {
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
}

void  GreedySearch::run() {

}

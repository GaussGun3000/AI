#include "AStar.h"

int AStar::h(const QSharedPointer<Node>& node)
{
    auto f = GreedySearch::h(node) + node->getCost();
    node->setH(f);
    return f;
}

AStar::AStar(QMutex* mutex, HFunction heuristic, const QVector<int>& startState, const QVector<int>& targetState) 
    : GreedySearch(mutex, heuristic, startState, targetState)
{
}
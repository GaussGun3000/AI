#pragma once
#include "GreedySearch.h"

class AStar : public GreedySearch
{
public:

	AStar::AStar(QMutex* mutex, HFunction heuristic, const QVector<int>& startState, const QVector<int>& targetState);

private:

	int h(const QSharedPointer<Node>& node) override;
};


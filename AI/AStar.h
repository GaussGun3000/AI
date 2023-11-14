#pragma once
#include "GreedySearch.h"

class AStar : public GreedySearch
{
	int h(const QSharedPointer<Node>& node) override;
};


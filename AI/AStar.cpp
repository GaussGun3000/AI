#include "AStar.h"

int AStar::h(const QSharedPointer<Node>& node)
{
    auto f = GreedySearch::h(node) + node->getCost();
    node->setH(f);
    return f;
}

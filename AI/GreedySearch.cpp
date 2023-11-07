#include "GreedySearch.h"

GreedySearch::GreedySearch(Node startNode, Node targetNode)
{
}

void GreedySearch::run()
{
}

void GreedySearch::run()
{
    initialize();
}

void GreedySearch::initialize()
{
    // Initialize the open set (queue) with the start node
    QQueue<QSharedPointer<Node>> openSet;
    openSet.enqueue(startNode);

    // Initialize the closed set (visited nodes)
    QSet<QVector<int>> closedSet;

    while (!openSet.isEmpty())
    {
        searchStep(openSet, closedSet);
    }

    // If the open set is empty and no solution was found, emit a signal to indicate failure
    emit updateStats(UINT32_MAX); // You can define a special value for failure if needed
}

void GreedySearch::searchStep(QQueue<QSharedPointer<Node>>& openSet, QSet<QVector<int>>& closedSet)
{
    // Get the current node from the front of the open set
    QSharedPointer<Node> currentNode = openSet.dequeue();

    // Check if the current node is the target node
    if (*currentNode == *targetNode)
    {
        // We found the solution, emit the depth signal and return
        emit updateStats(currentNode->getDepth());
        return;
    }

    // Mark the current node as visited
    closedSet.insert(currentNode->getState());

    // Expand the current node's children (nodes reachable by legal actions)
    QList<QSharedPointer<Node>> children = expandNode(currentNode);

    for (const QSharedPointer<Node>& child : children)
    {
        // Check if the child node is not in the closed set
        if (!closedSet.contains(child->getState()))
        {
            // Add the child node to the open set
            openSet.enqueue(child);
        }
    }
}

// Implement your h1 heuristic function here
uint32_t GreedySearch::h(const Node& node)
{
    // Calculate and return the h1 value for the given node
    // This function should define the number of misplaced tiles or any suitable heuristic
    // Example: return the count of tiles that are not in their goal positions
}

// Implement your expandNode function here
QList<QSharedPointer<Node>> GreedySearch::expandNode(const QSharedPointer<Node>& node)
{
    // Generate and return a list of child nodes based on legal actions from the given node
}

QQueue<QSharedPointer<Node>> GreedySearch::queuingFunction(const QQueue<QSharedPointer<Node>>& nodeQueue)
{
    return QQueue<QSharedPointer<Node>>();
}

uint32_t GreedySearch::h(const Node& node)
{
    return 0;
}


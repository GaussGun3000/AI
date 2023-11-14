#include "GreedySearch.h"
#include <QSet>
#include <algorithm>

GreedySearch::GreedySearch(QMutex* mutex, HFunction heuristic,
    const QVector<int>& startState,
    const QVector<int>& targetState)
    : mutex(mutex), heuristic(heuristic),
    startState(startState), targetState(targetState) {
    // Constructor implementation
    // You may initialize other members if necessary
}

int  GreedySearch::h(const QVector<int>& state) {
    int count = 0;
    for (int i = 0; i < state.size(); ++i) {
        if (state[i] != targetState[i] && state[i] != 0) { // Assuming 0 is the blank tile
            ++count;
        }
    }
    return count;
}

void  GreedySearch::run() {
    QSharedPointer<Node> root = QSharedPointer<Node>::create(startState, nullptr, Node::Action::NoAction, 0, 0);
    QSet<QVector<int>> visited;
    QList<QSharedPointer<Node>> frontier;
    frontier.append(root);

    while (!frontier.isEmpty()) {
        std::sort(frontier.begin(), frontier.end(), [this](const QSharedPointer<Node>& nodeA, const QSharedPointer<Node>& nodeB) {
            return h(nodeA->getState()) < h1(nodeB->getState());
            });

        QSharedPointer<Node> currentNode = frontier.takeFirst();
        QVector<int> currentState = currentNode->getState();

        if (visited.contains(currentState)) {
            continue; // Skip already visited states
        }

        if (currentState == targetState) {
            emit targetFound(currentNode);
            return;
        }

        visited.insert(currentState);

        QList<Node::Action> actions = currentNode->getAvailableActions();
        for (Node::Action action : actions) {
            QVector<int> newState = currentState;
            // Apply action to newState...
            // Make sure to implement the action application logic according to your puzzle rules

            if (!visited.contains(newState)) {
                QSharedPointer<Node> newNode = QSharedPointer<Node>::create(newState, currentNode.data(), action, currentNode->getDepth() + 1, currentNode->getCost() + 1);
                frontier.append(newNode);
            }
        }
    }
    emit searchFailed(); // No solution found
}

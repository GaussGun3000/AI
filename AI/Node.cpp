#include "Node.h"

void Node::applyAction(int action)
{
}

Node::Node(QScopedPointer<Node>& node, int action): parent(node.data())
{
	this->state = node->state;
	//this->parent = QScopedPointer<Node>(node.data());
	this->action = action;
	this->cost = node->cost + 1;
	this->depth = node->cost + 1;
	this->applyAction(action);

}

Node::Node(QVector<int> state, QScopedPointer<Node>& parent, int action, int depth, int cost):
	state(state), parent(parent.data()), action(action), depth(depth), cost(cost)
{}
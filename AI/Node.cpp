#include "Node.h"

Node::Node(QScopedPointer<Node>& node, Action action): parent(node.data())
{
	this->state = node->state;
	//this->parent = QScopedPointer<Node>(node.data());
	this->action = action;
	this->cost = node->cost + 1;
	this->depth = node->cost + 1;
	this->applyAction(action);
}

QVector<int> Node::getState() const
{
	return state;
}

Node::Node(QVector<int> state, QScopedPointer<Node>& parent, Action action, int depth, int cost):
	state(state), parent(parent.data()), action(action), depth(depth), cost(cost)
{}

Node::Node()
{
}

std::list<int> Node::getAvailableActions()
{
	int zeroPos = this->state.indexOf(0);
	std::list<int> availableActions;
	if (zeroPos > 2)
		availableActions.push_back(1); // up
	if (zeroPos % 3 != 0)
		availableActions.push_back(2); // right
	if (zeroPos < 6)
		availableActions.push_back(3); // down
	if (zeroPos % 3 != 2)
		availableActions.push_back(4); // left
	return availableActions;
}

void Node::applyAction(Action action)
{
	int zeroPos = this->state.indexOf(0);
	switch (action)
	{
	case Action::MoveUp:
	{
		if (zeroPos > 2)
		{
			this->state[zeroPos] = this->state[zeroPos - 3];
			this->state[zeroPos - 3] = 0;
		}
		else {}
		break;
	};

	case Action::MoveDown:
	{
		if (zeroPos < 6)
		{
			this->state[zeroPos] = this->state[zeroPos + 3];
			this->state[zeroPos + 3] = 0;
		}
		break;
	};

	case Action::MoveLeft:
	{
		if (zeroPos % 3 != 0)
		{
			this->state[zeroPos] = this->state[zeroPos - 1];
			this->state[zeroPos - 1] = 0;
		}
		break;
	};

	case Action::MoveRight:
	{
		if (zeroPos % 3 != 2)
		{
			this->state[zeroPos] = this->state[zeroPos + 1];
			this->state[zeroPos + 1] = 0;
		}
		break;
	};
	}
}

Node& Node::operator=(const Node& other)
{
	if (this != &other) // Проверка на самоприсваивание
	{
		state = other.state;
		//if (other.parent) parent.reset(new Node(other.parent, Action::NoAction));
		//else parent.reset();
		parent.reset(other.parent.data());
		action = other.action;
		cost = other.cost;
		depth = other.depth;
	}
	return *this;
}

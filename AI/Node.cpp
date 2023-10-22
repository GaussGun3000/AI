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
		else {}; // мб добавить обработку ошибок? но по сути если алгоритм правильно работает они не должны появлвяться. и эти if тоже тогда не нужны
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

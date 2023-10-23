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

uint32_t Node::getDepth() const
{
	return depth;
}

Node::Node(QVector<int> state, QScopedPointer<Node>& parent, Action action, int depth, int cost):
	state(state), parent(parent.data()), action(action), depth(depth), cost(cost)
{}

Node::Node()
{
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
		else {}; // �� �������� ��������� ������? �� �� ���� ���� �������� ��������� �������� ��� �� ������ �����������. � ��� if ���� ����� �� �����
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
	if (this != &other) // �������� �� ����������������
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

QVector<Node::Action> Node::getAvailableActions() const
{
	return QVector<Action>();
}

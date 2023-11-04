#include "Node.h"

Node::Node(QSharedPointer<Node>& node, Action action)
{
	this->state = node->state;
	this->parent = node;
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

uint32_t Node::getCost() const
{
	return cost;
}

QSharedPointer<Node> Node::getParent() const
{
	return parent;
}

Node::Action Node::getAction() const
{
	return action;
}

Node::Node(QVector<int> state, Node* parent, Action action, int depth, int cost):
	state(state), parent(parent), action(action), depth(depth), cost(cost)
{}

Node::Node(const Node & other)
{
	this->state = other.state;
	this->parent = other.parent;
	this->action = other.action;
	this->cost = other.cost;
	this->depth = other.depth;
}

Node::Node()
{
	action = Node::Action::NoAction;
	cost = 0;
	depth = 0;
}

Node::~Node()
{
	parent.reset();
}

QList<Node::Action> Node::getAvailableActions() const
{
	int zeroPos = this->state.indexOf(0);
	QList<Node::Action> availableActions;
	if (zeroPos > 2)
		availableActions.push_back(Node::Action::MoveUp); 
	if (zeroPos % 3 != 2)
		availableActions.push_back(Node::Action::MoveRight); 
	if (zeroPos < 6)
		availableActions.push_back(Node::Action::MoveDown); 
	if (zeroPos % 3 != 0)
		availableActions.push_back(Node::Action::MoveLeft); 
	return availableActions;
}

void Node::setState(QVector<int> state)
{
	this->state = state;
}

void Node::setDepth(uint32_t depth)
{
	this->depth = depth;
}

void Node::setCost(uint32_t cost)
{
	this->cost = cost;
}

void Node::setParent(QSharedPointer<Node> parent)
{
	this->parent = parent;
}

void Node::setAction(Action action)
{
	this->action = action;
}

QString Node::getStateString()
{
	const QVector<int>& state = getState();
	QString formattedState;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			formattedState.append(QString::number(state[i * 3 + j]));
			if (j < 2) { 
				formattedState.append(' ');
			}
		}
		if (i < 2) {
			formattedState.append('\n');
		}
	}
	return formattedState;
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

bool Node::operator==(const Node& other) const{
	return this->getState() == other.getState();
}


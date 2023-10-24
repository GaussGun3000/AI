#include "NodePtrWrapper.h"

inline uint qHash(const NodePtrWrapper& wrapper)
{
	return qHash(wrapper.node->getState());
}

inline bool operator==(const NodePtrWrapper& left, const NodePtrWrapper& right)
{
	return left.node->getState() == right.node->getState();
};

NodePtrWrapper::NodePtrWrapper()
{
}

QSharedPointer<Node>& NodePtrWrapper::operator=(const QSharedPointer<Node>& other)
{
	if (this != other) // Проверка на самоприсваивание
	{
		this->node->setState(other.data()->getState());
		this->node->getParent().reset(other.data()->getParent().data());
		this->node->setAction(other.data()->getAction());
		this->node->setDepth(other.data()->getDepth());
		this->node->setCost(other.data()->getCost());
	}
	return *this;
}

bool NodePtrWrapper::operator==(const QSharedPointer<Node>& other) const
{
	return this->node->getState() == other.data()->getState();
}


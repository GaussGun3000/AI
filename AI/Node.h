#pragma once
#include <QVector>
#include <qscopedpointer.h>
#include <qsharedpointer.h>
#include <list>

class Node
{

public:
	QVector<int> getState() const;
	uint32_t getDepth() const;
	enum class Action { NoAction = -1, MoveUp = 1, MoveRight, MoveDown, MoveLeft };
	enum class Cell { UpLeft = 0, UpCenter, UpRight, MidLeft, Center, MidRight, BottomLeft, BottomCenter, BottomRight };
	Node(QSharedPointer<Node>& node, Action action);
	Node(QVector<int> state, Node* parent, Action action, int depth, int cost);
	Node(const Node& other);
	Node();
	Node& operator=(const Node& other);
	bool operator==(const Node& other) const;
	std::list<Node::Action> getAvailableActions() const;

private:
	QVector<int> state;
	QSharedPointer<Node> parent;
	Action action;
	uint32_t cost;
	uint32_t depth;
	void applyAction(Action action);

};

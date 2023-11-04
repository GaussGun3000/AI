#pragma once
#include <QVector>
#include <qscopedpointer.h>
#include <qsharedpointer.h>
#include <qlist.h>

class Node
{

public:
	enum class Action { NoAction = -1, MoveUp = 1, MoveRight, MoveDown, MoveLeft };
	enum class Cell { UpLeft = 0, UpCenter, UpRight, MidLeft, Center, MidRight, BottomLeft, BottomCenter, BottomRight };
	
	QVector<int> getState() const;
	uint32_t getDepth() const;
	uint32_t getCost() const;
	QSharedPointer<Node> getParent() const;
	Node::Action getAction() const;
	QList<Node::Action> getAvailableActions() const;

	void setState(QVector<int> state);
	void setDepth(uint32_t depth);
	void setCost(uint32_t cost);
	void setParent(QSharedPointer<Node> parent);
	void setAction(Action action);

	Node(QSharedPointer<Node>& node, Action action);
	Node(QVector<int> state, Node* parent, Action action, int depth, int cost);
	Node(const Node& other);
	Node();
	~Node();

	Node& operator=(const Node& other);
	bool operator==(const Node& other) const;

private:
	QVector<int> state;
	QSharedPointer<Node> parent;
	Action action;
	uint32_t cost;
	uint32_t depth;
	void applyAction(Action action);

};

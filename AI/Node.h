#pragma once
#include <QVector>
#include <qscopedpointer.h>

class Node
{

public:
	QVector<int> getState() const;
	enum class Action { NoAction = -1, MoveUp = 1, MoveRight, MoveDown, MoveLeft };
	enum class Cell { UpLeft = 0, UpCenter, UpRight, MidLeft, Center, MidRight, BottomLeft, BottomCenter, BottomRight };
	Node(QScopedPointer<Node>& node, Action action);
	Node(QVector<int> state, QScopedPointer<Node>& parent, Action action, int depth, int cost);
	Node();
	Node& operator=(const Node& other);

private:
	QVector<int> state;
	QScopedPointer<Node> parent;
	Action action;
	int cost;
	int depth;

	void applyAction(Action action);


};

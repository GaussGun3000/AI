#pragma once
#include <QVector>
#include <qscopedpointer.h>

class Node
{
	QVector<int> state;
	QScopedPointer<Node> parent;
	enum class Action {MoveUp = 1, MoveRight, MoveDown, MoveLeft};
	enum class Cell {UpLeft = 0, UpCenter, UpRight, MidLeft, Center, MidRight, BottomLeft, BottomCenter, BottomRight};
	Action action;
	int cost;
	int depth;

	Node(QScopedPointer<Node>& node, Action action);
	Node(QVector<int> state, QScopedPointer<Node>& parent, Action action, int depth, int cost);
	void applyAction(Action action);
public:
	 QVector<int> getState() const;

};

#pragma once
#include <QVector>
#include <qscopedpointer.h>

class Node
{
	QVector<int> state;
	QScopedPointer<Node> parent;
	enum class Action {Up = 1, Down, Left, Right};
	Action action;
	int cost;
	int depth;

	Node(QScopedPointer<Node>& node, Action action);
	Node(QVector<int> state, QScopedPointer<Node>& parent, Action action, int depth, int cost);
	void applyAction(Action action);

};


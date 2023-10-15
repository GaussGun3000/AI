#pragma once
#include <QVector>
#include <qscopedpointer.h>

class Node
{
	QVector<int> state;
	QScopedPointer<Node> parent;
	int action;
	int cost;
	int depth;

	Node(QScopedPointer<Node>& node, int action);
	Node(QVector<int> state, QScopedPointer<Node>& parent, int action, int depth, int cost);
	void applyAction(int action);

};


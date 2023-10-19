#pragma once
#include "Node.h"
#include <qset.h>
#include <qthread.h>
#include <qmutex.h>

class BidirectionalDFS
{
	QScopedPointer<Node> start;
	QScopedPointer<Node> target;
	QSet<Node> startDirectionSet;
	QSet<Node> targetDirectionSet;
};

class DirectionalSearch : public QThread
{
	QScopedPointer<Node> otherDirectionSet;
	QScopedPointer<Node> thisDirectionSet;
	QScopedPointer<QMutex> otherDirectionMutex;
	QScopedPointer<QMutex> thisDirectionMutex;
	int32_t maxDepth;
	void run() override;
	void createNodeLayer();

public:
	DirectionalSearch(Node* ods, Node* tds, QMutex* odm, QMutex* tdm, int32_t maxDepth);
};


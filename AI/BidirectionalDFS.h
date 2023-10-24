#pragma once
#include "Node.h"
#include <qset.h>
#include <qthread.h>
#include <qmutex.h>
#include <qlist.h>
#include <qstack.h>

class BidirectionalDFS
{
	// reduntant class. Remove later if proven completelt unnecessary
public:
	BidirectionalDFS();
};

class DirectionalSearch : public QThread
{
	Q_OBJECT

signals:
	void updateStats(const uint32_t depth);

private:
	QSet<QSharedPointer<Node>> targetDirectionSet;
	QSet<QSharedPointer<Node>> startDirectionSet;
	QMutex* nextStepPermission;
	QList<QSharedPointer<Node>> nodes;
	QSharedPointer<Node> lastStartNode;
	QSharedPointer<Node> lastTargetNode;
	QStack<QSharedPointer<Node>> startStack;
	QStack<QSharedPointer<Node>> targetStack;
	int32_t resulting_depth = -1;

	uint32_t maxDepth;
	void run() override;
	void createNodeLayerStart();
	void createNodeLayerTarget();

public:
	DirectionalSearch(QMutex* nsp, uint32_t maxDepth, QVector<int>& start, QVector<int>& target);
	void setMaxDepth(uint32_t maxDepth);

};


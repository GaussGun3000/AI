#pragma once
#include "Node.h"
#include <qset.h>
#include <qthread.h>
#include <qmutex.h>
#include <qlist.h>
#include <qstack.h>
#include "NodePtrWrapper.h"

class BidirectionalDFS
{
	// reduntant class. Remove later if proven completelt unnecessary
public:
	BidirectionalDFS();
};

class NodePtr {
public:
	explicit NodePtr(const QSharedPointer<Node>& node) : node(node) {}

	QSharedPointer<Node> node;
};

class DirectionalSearch : public QThread
{
	Q_OBJECT

signals:
	void updateStats(const uint32_t depth);

private:
	QSet<NodePtrWrapper> targetDirectionSet;
	QSet<NodePtrWrapper> startDirectionSet;
	QMutex* nextStepPermission;
	QList<NodePtrWrapper> nodes;
	NodePtrWrapper lastStartNode;
	NodePtrWrapper lastTargetNode;
	QStack<NodePtrWrapper> startStack;
	QStack<NodePtrWrapper> targetStack;
	
	int32_t resultingDepth = -1;
	uint32_t currentDepth = 0;
	uint32_t maxDepth;
	void run() override;
	void createNodeLayerStart();
	void createNodeLayerTarget();

public:
	DirectionalSearch(QMutex* nsp, uint32_t maxDepth, QVector<int>& start, QVector<int>& target);
	void setMaxDepth(uint32_t maxDepth);
	uint32_t getResultingDepth() const;

};


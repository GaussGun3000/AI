#pragma once
#include "Node.h"
#include <qset.h>
#include <qthread.h>
#include <qmutex.h>
#include <qlist.h>
#include <qstack.h>
#include <qqueue.h>

class NodePtr {
public:
	explicit NodePtr(const QSharedPointer<Node>& node) : node(node) {}

	QSharedPointer<Node> node;
};

class BiDirectionalSearch : public QThread
{
	Q_OBJECT

signals:
	void updateStats(const quint32 depth);

private:
	QSet<NodePtr> targetDirectionSet;
	QSet<NodePtr> startDirectionSet;
	QMutex* nextStepPermission;
	QList<QSharedPointer<Node>> nodes;
	QSharedPointer<Node> lastStartNode;
	QSharedPointer<Node> lastTargetNode;
	QQueue<QSharedPointer<Node>> startQueue;
	QQueue<QSharedPointer<Node>> targetQueue;
	
	QSharedPointer<Node> startNode;
	QSharedPointer<Node> target;
	int32_t resultingDepth = -1;
	uint32_t currentDepth = 0;
	uint32_t maxDepth;
	uint32_t steps;
	uint32_t nodeCount;
	void run() override;
	void createNodeLayerStart();
	void createNodeLayerTarget();
	void init();
	void cleanup();
public:
	BiDirectionalSearch(QMutex* nsp, uint32_t maxDepth, QVector<int>& start, QVector<int>& target);
	void setMaxDepth(uint32_t maxDepth);
	int32_t getResultingDepth();
	quint32 getNodeCount();
	quint32 getStepCount();
	QString getLastStartNodeStateString() const;
	QString getLastTargetNodeStateString() const;

};

class DFS : public QThread 
{
	Q_OBJECT

signals:
	void updateStats(const quint32 depth);

private:
	QMutex* nextStepPermission;
	QSharedPointer<Node> lastNode;
	QSharedPointer<Node> targetNode;
	QStack<QSharedPointer<Node>> dfsStack;
	QSet<NodePtr> uniqueStatesSet;
	QSharedPointer<Node> startNode;

	int32_t resultingDepth = -1;
	uint32_t currentDepth = 0;
	uint32_t maxDepth;
	uint32_t steps;
	uint32_t nodeCount;
	void run() override;
	void createNodeLayer();
	void init();
	void cleanup();
public:
	DFS(QMutex* nsp, uint32_t maxDepth, QVector<int>& start, QVector<int>& target);
	void setMaxDepth(uint32_t maxDepth);
	int32_t getResultingDepth();
	quint32 getNodeCount();
	quint32 getStepCount();
	QString getLastNodeStateString() const;
};
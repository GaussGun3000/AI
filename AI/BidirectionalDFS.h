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
	
	int32_t resultingDepth = -1;
	uint32_t currentDepth = 0;
	uint32_t maxDepth;
	void run() override;
	void createNodeLayerStart();
	void createNodeLayerTarget();

public:
	BiDirectionalSearch(QMutex* nsp, uint32_t maxDepth, QVector<int>& start, QVector<int>& target);
	void setMaxDepth(uint32_t maxDepth);
	int32_t getResultingDepth();
	quint32 getNodesNumSize();

};

class DFS : public QThread 
{
	Q_OBJECT

signals:
	void updateStats(const quint32 depth);

private:
	QMutex* nextStepPermission;
	QList<QSharedPointer<Node>> nodes;
	QSharedPointer<Node> lastNode;
	QSharedPointer<Node> targetNode;
	QStack<QSharedPointer<Node>> dfsStack;
	QSet<NodePtr> uniqueStatesSet;

	int32_t resultingDepth = -1;
	uint32_t currentDepth = 0;
	uint32_t maxDepth;
	void run() override;
	void createNodeLayer();

public:
	DFS(QMutex* nsp, uint32_t maxDepth, QVector<int>& start, QVector<int>& target);
	void setMaxDepth(uint32_t maxDepth);
	int32_t getResultingDepth();
	quint32 getNodesNumSize();
};
#pragma once
#include "Node.h"
#include <qset.h>
#include <qthread.h>
#include <qmutex.h>

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
	void updateStats(uint32_t depth);

private:
	QSet<Node> targerDirectionSet;
	QSet<Node> startDirectionSet;
	QScopedPointer<QMutex> nextStepPermission;

	uint32_t maxDepth;
	void run() override;
	void createNodeLayerStart();
	void createNodeLayerEnd();

public:
	DirectionalSearch(QMutex* nsp, uint32_t maxDepth);
};


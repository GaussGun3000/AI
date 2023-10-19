#pragma once
#include "Node.h"
#include <qset.h>
class BidirectionalDFS
{
	QScopedPointer<Node> start;
	QScopedPointer<Node> target;
	QSet<Node> startDirectionSet;
	QSet<Node> targetDirectionSet;
};


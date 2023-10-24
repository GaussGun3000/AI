#pragma once
#include "Node.h"

class NodePtrWrapper
{
public:
    explicit NodePtrWrapper(const QSharedPointer<Node>& node) : node(node) {}
    NodePtrWrapper();

    QSharedPointer<Node> node;

    QSharedPointer<Node>& operator=(const QSharedPointer<Node>& other);
    bool operator==(const QSharedPointer<Node>& other) const;
};


#include <QThread>
#include <QVector>
#include <QSharedPointer>
#include <qqueue.h>
#include <qset.h>
#include "Node.h" 


class NodePtr {
public:
    explicit NodePtr(const QSharedPointer<Node>& node) : node(node) {}

    QSharedPointer<Node> node;
};

class BFS : public QThread
{
    Q_OBJECT

public:
    enum class hFunction { h1 = 0, h2 = 1 };
    BFS(Node startNode, Node targetNode);

signals:
    void updateStats(uint32_t depth);

private:
    QSharedPointer<Node> startNode;
    QSharedPointer<Node> targetNode;

    void run() override;
    void initialize();
    void searchStep(QQueue<QSharedPointer<Node>>& openSet, QSet<QVector<int>>& closedSet);

    QList<QSharedPointer<Node>> expandNode(const QSharedPointer<Node>& node);

    uint32_t h(const Node& node);

};

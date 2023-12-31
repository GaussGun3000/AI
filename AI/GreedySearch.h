#include <QThread>
#include <QVector>
#include <QSharedPointer>
#include <qqueue.h>
#include <qset.h>
#include "Node.h" 
#include <qmutex.h>
#include <qmap.h>
#include <queue>

class NodePtr {
public:
    explicit NodePtr(const QSharedPointer<Node>& node) : node(node) {}

    QSharedPointer<Node> node;
};

class GreedySearch : public QThread {
    Q_OBJECT

public:
    enum class HFunction { h1 = 0, h2 = 1 };
    GreedySearch::GreedySearch(QMutex* mutex, HFunction heuristic, const QVector<int>& startState, const QVector<int>& targetState);
    GreedySearch::GreedySearch();
    int32_t getResultingDepth();
    quint32 getNodeCount();
    quint32 getStepCount();
    QString getLastNodeStateString() const;
    QString getParentLastNodeStateString() const;

signals:
    void updateStats(const quint32 depth);

protected:
    void run() override;
    virtual int h(const QSharedPointer<Node>& node);
    struct NodeComparator {
        bool operator()(const QSharedPointer<Node>& lhs, const QSharedPointer<Node>& rhs) const {
            return lhs->getH() > rhs->getH();
        }
    };
    std::priority_queue<QSharedPointer<Node>, QVector<QSharedPointer<Node>>, NodeComparator> priorityQueue;
    QMutex* nextStepPermission;
    HFunction heuristic;
    QVector<int> startState;
    QVector<int> targetState;
    qint32 resultingDepth = -1;
    qint32 steps = 0;
    qint32 currentDepth = 0;
    qint32 nodeCount = 0;
    QMap<QString, int> h2Cost = {
        {"01", 1}, {"02", 2}, {"03", 1}, {"04", 2}, {"05", 3}, {"06", 2}, {"07", 3}, {"08", 4},
        {"12", 1}, {"13", 2}, {"14", 1}, {"15", 2}, {"16", 3}, {"17", 2}, {"18", 3},
        {"23", 3}, {"24", 2}, {"25", 1}, {"26", 4}, {"27", 3}, {"28", 2},
        {"34", 1}, {"35", 2}, {"36", 1}, {"37", 2}, {"38", 3},
        {"45", 1}, {"46", 2}, {"47", 1}, {"48", 2},
        {"56", 3}, {"57", 2}, {"58", 1},
        {"67", 1}, {"68", 2},
        {"78", 1}
    };
    QSet<NodePtr> uniqueStates;
    QSharedPointer<Node> lastNode;
    void init();
    void cleanup();
    void iteration();

private:


};

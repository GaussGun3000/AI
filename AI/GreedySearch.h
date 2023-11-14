#include <QThread>
#include <QVector>
#include <QSharedPointer>
#include <qqueue.h>
#include <qset.h>
#include "Node.h" 
#include <qmutex.h>
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

signals:
    void targetFound(QSharedPointer<Node> targetNode); 
    void searchFailed();

protected:
    void run() override;

private:
    struct NodeComparator {
        bool operator()(const QSharedPointer<Node>& lhs, const QSharedPointer<Node>& rhs) const {
            return lhs->getH() > rhs->getH();
        }
    };
    std::priority_queue<QSharedPointer<Node>, QVector<QSharedPointer<Node>>, NodeComparator> priorityQueue ;
    QMutex* mutex;
    HFunction heuristic;
    int h(const QSharedPointer<Node>& node);
    QVector<int> startState;
    QVector<int> targetState;
    QSet<NodePtr> uniqueStates;
    void init();


};

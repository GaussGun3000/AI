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

class GreedySearch : public QThread {
    Q_OBJECT

public:
    enum class HFunction { h1 = 0, h2 = 1 };
    GreedySearch(const QVector<int>& startState, const QVector<int>& goalState, QObject* parent = nullptr);

signals:
    void targetFound(QSharedPointer<Node> targetNode); 
    void searchFailed();

protected:
    void run() override;

private:
    int h(const QVector<int>& state);
    QVector<int> startState;
    QVector<int> targetState;
};

#include "MainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
//#include <QThread>
//#include <QVector>
//#include <QSharedPointer>
//#include <qqueue.h>
//#include <qset.h>
//#include "Node.h" 
//#include <qmutex.h>
//#include <qmap.h>
//#include <queue>
//#include <qdebug.h>
//
//QMap<QString, int> h2Cost = {
//    {"01", 1}, {"02", 2}, {"03", 1}, {"04", 2}, {"05", 3}, {"06", 2}, {"07", 3}, {"08", 4},
//    {"12", 1}, {"13", 2}, {"14", 1}, {"15", 2}, {"16", 3}, {"17", 2}, {"18", 3},
//    {"23", 3}, {"24", 2}, {"25", 1}, {"26", 4}, {"27", 3}, {"28", 2},
//    {"34", 1}, {"35", 2}, {"36", 1}, {"37", 2}, {"38", 3},
//    {"45", 1}, {"46", 2}, {"47", 1}, {"48", 2},
//    {"56", 3}, {"57", 2}, {"58", 1},
//    {"67", 1}, {"68", 2},
//    {"78", 1}
//};
//
//enum class HFunction { h1 = 0, h2 = 1 };
//
//QVector<int> targetState = { 1, 2, 3, 8, 0, 4, 7, 6, 5 };
//
//int h(const QSharedPointer<Node>& node, HFunction heuristic) {
//    QVector<int> state = node->getState();
//    int count = 0;
//    if (heuristic == HFunction::h1)
//    {
//        for (int i = 0; i < 9; ++i) {
//            if (state[i] != targetState[i]) {
//                ++count;
//            }
//        }
//    }
//    else if (heuristic == HFunction::h2)
//    {
//        for (int i = 0; i < 9; ++i) {
//            int targetIndex = targetState.indexOf(state[i]);
//            if (i - targetIndex != 0) // if == 0: current number already is on the right position
//            {
//                if (h2Cost.contains(QString::number(i) + QString::number(targetIndex)))
//                    count = count + h2Cost.value(QString::number(i) + QString::number(targetIndex));
//                else if (h2Cost.contains(QString::number(targetIndex) + QString::number(i)))
//                    count = count + h2Cost.value(QString::number(targetIndex) + QString::number(i));
//            }
//        }
//    }
//    node->setH(count);
//    return count;
//}
//
//int main(int argc, char* argv[]) {
//    //QCoreApplication a(argc, argv);
//
//    //// Test States
//    //QVector<int> state1 = { 1, 2, 3,
//    //                        4, 5, 6, 
//    //                        7, 8, 0 }; // Ideal State (h1 and h2 should be 0)
//
//    //QVector<int> state2 = { 1, 2, 3, 
//    //                        4, 5, 6,
//    //                        7, 0, 8 }; // One move away from ideal (h1 should be 1)
//
//    //QVector<int> state3 = { 8, 7, 6,
//    //                        5, 4, 3, 
//    //                        2, 1, 0 }; // Completely reversed (higher h1 and h2 values)
//
//    //// Test Nodes
//    //QSharedPointer<Node> testNode1(new Node(state1, nullptr, Node::Action::NoAction, 0, 0));
//    //QSharedPointer<Node> testNode2(new Node(state2, nullptr, Node::Action::NoAction, 0, 0));
//    //QSharedPointer<Node> testNode3(new Node(state3, nullptr, Node::Action::NoAction, 0, 0));
//
//    //// Testing with HFunction::h1
//    //qDebug() << "h1 value for state1:" << h(testNode1, HFunction::h1);
//    //qDebug() << "h1 value for state2:" << h(testNode2, HFunction::h1);
//    //qDebug() << "h1 value for state3:" << h(testNode3, HFunction::h1);
//
//    //// Testing with HFunction::h2
//    //qDebug() << "h2 value for state1:" << h(testNode1, HFunction::h2);
//    //qDebug() << "h2 value for state2:" << h(testNode2, HFunction::h2);
//    //qDebug() << "h2 value for state3:" << h(testNode3, HFunction::h2);
//
//    //return a.exec();
//    QVector<QVector<int>> testStates = {
//    {1, 2, 3, 8, 0, 4, 7, 6, 5}, // Target state
//    {1, 2, 3, 4, 5, 6, 7, 8, 0}, // Reversed
//    {2, 8, 3, 1, 6, 4, 7, 0, 5}, // Random state
//    // Add more test states as needed
//    };
//
//    struct TestData {
//        QVector<int> state;
//        int expectedH1;
//        int expectedH2;
//    };
//
//    QVector<TestData> testCases = {
//        {{1, 2, 3, 8, 0, 4, 7, 6, 5}, 0, 0}, // Target state, H1 and H2 should both be 0
//        {{1, 2, 3, 4, 5, 6, 7, 8, 0}, 5, 10}, // Reversed, H1 = 6, H2 = 12
//        {{2, 8, 3, 1, 6, 4, 7, 0, 5}, 8, 18}, // Random state, H1 = 8, H2 = 18
//        {{4, 1, 3, 8, 6, 2, 7, 0, 5}, 8, 20}, // Another state, H1 = 8, H2 = 20
//        {{5, 6, 7, 4, 0, 8, 3, 2, 1}, 8, 24}, // Another state, H1 = 8, H2 = 24
//        // Add more test cases as needed
//    };
//
//    for (const auto& testData : testCases) {
//        QSharedPointer<Node> testNode(new Node(testData.state, nullptr, Node::Action::NoAction, 0, 0));
//
//        int h1Value = h(testNode, HFunction::h1);
//        int h2Value = h(testNode, HFunction::h2);
//
//        qDebug() << "State: " << testNode->getStateString();
//        qDebug() << " | Expected H1: " << testData.expectedH1 << " | Calculated H1: " << h1Value;
//        qDebug() << " | Expected H2: " << testData.expectedH2 << " | Calculated H2: " << h2Value;
//        qDebug() << "------------------------------------";
//    }
//    getchar();
//}
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QPair>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Node {
    QVector<QVector<int>> reducedMatrix;
    int cost;
    int vertex;
    int level;
    QVector<int> path;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_solveButton_clicked();
    void on_stepButton_clicked();
    void on_resetButton_clicked();
    void on_loadMatrixButton_clicked();

private:
    Ui::MainWindow *ui;

    QVector<QVector<int>> originalMatrix = {
        {-1, 5, 3, 3},
        {5, -1, 9, 7},
        {3, 9, -1, 4},
        {3, 7, 4, -1}
    };

    QVector<QVector<int>> currentMatrix;
    QVector<int> optimalPath;
    int optimalCost;
    QVector<QPair<int, int>> steps;
    int currentStep;

    void initializeMatrix();
    void solveTSP();
    void reduceMatrix(QVector<QVector<int>>& matrix, int& cost);
    Node* createNode(const QVector<QVector<int>>& parentMatrix, const QVector<int>& path,
                     int level, int i, int j);
    void updateVisualization();
    void drawGraph();
    void highlightPath(const QVector<int>& path);
};

#endif // MAINWINDOW_H

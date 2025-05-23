#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "node.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnBuildTree_clicked();
    void on_btnVisualize_clicked();
    void on_btnInsert_clicked();
    void on_btnDelete_clicked();
    void on_btnSearch_clicked();
    void on_btnPreorder_clicked();
    void on_btnInorder_clicked();
    void on_btnPostorder_clicked();
    void on_btnHeight_clicked();
    void on_btnBalance_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    Node* root;

    void drawTree(Node* node, int x, int y, int dx, int dy, QGraphicsScene* scene);
    void clearTree(Node* node);
};

#endif // MAINWINDOW_H

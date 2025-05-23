#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class GraphWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddVertexClicked();
    void onRemoveVertexClicked();
    void onAddEdgeClicked();
    void onRemoveEdgeClicked();
    void onEditWeightClicked();
    void onEditMatrixClicked();
    void onBFSClicked();
    void onDFSClicked();
    void onDijkstraClicked();
    void onFloydClicked();
    void onTSPClicked();

private:
    Ui::MainWindow *ui;
    GraphWidget *graphWidget;
    void setupUI();
};

#endif // MAINWINDOW_H

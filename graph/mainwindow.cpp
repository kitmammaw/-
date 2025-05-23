#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphwidget.h"
#include <QPushButton>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    graphWidget = new GraphWidget(this);

    // Создаем кнопки
    QPushButton *addVertexButton = new QPushButton("Добавить вершину", this);
    QPushButton *removeVertexButton = new QPushButton("Удалить вершину", this);
    QPushButton *addEdgeButton = new QPushButton("Добавить ребро", this);
    QPushButton *removeEdgeButton = new QPushButton("Удалить ребро", this);
    QPushButton *editWeightButton = new QPushButton("Изменить вес ребра", this);
    QPushButton *editMatrixButton = new QPushButton("Редактировать матрицу смежности", this);
    QPushButton *bfsButton = new QPushButton("Обход в ширину (BFS)", this);
    QPushButton *dfsButton = new QPushButton("Обход в глубину (DFS)", this);
    QPushButton *dijkstraButton = new QPushButton("Алгоритм Дейкстры", this);
    QPushButton *floydButton = new QPushButton("Алгоритм Флойда", this);
    QPushButton *tspButton = new QPushButton("Решить TSP", this);

    // Подключаем кнопки к слотам
    connect(addVertexButton, &QPushButton::clicked, this, &MainWindow::onAddVertexClicked);
    connect(removeVertexButton, &QPushButton::clicked, this, &MainWindow::onRemoveVertexClicked);
    connect(addEdgeButton, &QPushButton::clicked, this, &MainWindow::onAddEdgeClicked);
    connect(removeEdgeButton, &QPushButton::clicked, this, &MainWindow::onRemoveEdgeClicked);
    connect(editWeightButton, &QPushButton::clicked, this, &MainWindow::onEditWeightClicked);
    connect(editMatrixButton, &QPushButton::clicked, this, &MainWindow::onEditMatrixClicked);
    connect(bfsButton, &QPushButton::clicked, this, &MainWindow::onBFSClicked);
    connect(dfsButton, &QPushButton::clicked, this, &MainWindow::onDFSClicked);
    connect(dijkstraButton, &QPushButton::clicked, this, &MainWindow::onDijkstraClicked);
    connect(floydButton, &QPushButton::clicked, this, &MainWindow::onFloydClicked);
    connect(tspButton, &QPushButton::clicked, this, &MainWindow::onTSPClicked);

    // Создаем layout для кнопок
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addVertexButton);
    buttonLayout->addWidget(removeVertexButton);
    buttonLayout->addWidget(addEdgeButton);
    buttonLayout->addWidget(removeEdgeButton);
    buttonLayout->addWidget(editWeightButton);
    buttonLayout->addWidget(editMatrixButton);

    QHBoxLayout *algorithmLayout = new QHBoxLayout();
    algorithmLayout->addWidget(bfsButton);
    algorithmLayout->addWidget(dfsButton);
    algorithmLayout->addWidget(dijkstraButton);
    algorithmLayout->addWidget(floydButton);
    algorithmLayout->addWidget(tspButton);

    // Основной layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(graphWidget);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(algorithmLayout);

    // Центральный виджет
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Настройки окна
    setWindowTitle("Графы: алгоритмы и визуализация");
    resize(1000, 800);
}

void MainWindow::onAddVertexClicked()
{
    bool ok;
    int vertexNumber = QInputDialog::getInt(this, "Добавить вершину",
                                            "Введите номер вершины:",
                                            graphWidget->vertexCount(), 0, 1000, 1, &ok);
    if (ok) {
        graphWidget->setWaitingForClick(true, vertexNumber);
    }
}

void MainWindow::onRemoveVertexClicked()
{
    bool ok;
    int vertexNumber = QInputDialog::getInt(this, "Удалить вершину",
                                            "Введите номер вершины для удаления:",
                                            0, 0, graphWidget->vertexCount() - 1, 1, &ok);
    if (ok) {
        graphWidget->removeVertex(vertexNumber);
    }
}

void MainWindow::onAddEdgeClicked()
{
    bool ok1, ok2;
    int from = QInputDialog::getInt(this, "Добавить ребро", "Первая вершина:",
                                    0, 0, graphWidget->vertexCount() - 1, 1, &ok1);
    int to = QInputDialog::getInt(this, "Добавить ребро", "Вторая вершина:",
                                  0, 0, graphWidget->vertexCount() - 1, 1, &ok2);
    if (ok1 && ok2) {
        graphWidget->addEdge(from, to);
    }
}

void MainWindow::onRemoveEdgeClicked()
{
    bool ok1, ok2;
    int from = QInputDialog::getInt(this, "Удалить ребро", "Первая вершина:",
                                    0, 0, graphWidget->vertexCount() - 1, 1, &ok1);
    int to = QInputDialog::getInt(this, "Удалить ребро", "Вторая вершина:",
                                  0, 0, graphWidget->vertexCount() - 1, 1, &ok2);
    if (ok1 && ok2) {
        graphWidget->removeEdge(from, to);
    }
}

void MainWindow::onEditWeightClicked()
{
    bool ok1, ok2, ok3;
    int from = QInputDialog::getInt(this, "Изменить вес ребра", "Первая вершина:",
                                    0, 0, graphWidget->vertexCount() - 1, 1, &ok1);
    int to = QInputDialog::getInt(this, "Изменить вес ребра", "Вторая вершина:",
                                  0, 0, graphWidget->vertexCount() - 1, 1, &ok2);
    int weight = QInputDialog::getInt(this, "Изменить вес ребра", "Новый вес:",
                                      1, 1, 10000, 1, &ok3);
    if (ok1 && ok2 && ok3) {
        graphWidget->setEdgeWeight(from, to, weight);
    }
}

void MainWindow::onEditMatrixClicked()
{
    int n = graphWidget->vertexCount();
    if (n == 0) {
        QMessageBox::warning(this, "Ошибка", "Нет вершин для редактирования матрицы");
        return;
    }

    QVector<QVector<int>> matrix = graphWidget->getAdjacencyMatrix();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            bool ok;
            int val = QInputDialog::getInt(this, "Редактирование матрицы",
                                           QString("Матрица[%1][%2]:").arg(i).arg(j),
                                           matrix[i][j], 0, 1, 1, &ok);
            if (!ok) return;
            matrix[i][j] = val;
        }
    }

    graphWidget->setAdjacencyMatrix(matrix);
}

void MainWindow::onBFSClicked()
{
    bool ok;
    int start = QInputDialog::getInt(this, "BFS", "Начальная вершина:",
                                     0, 0, graphWidget->vertexCount() - 1, 1, &ok);
    if (ok) {
        graphWidget->breadthFirstSearch(start);
    }
}

void MainWindow::onDFSClicked()
{
    bool ok;
    int start = QInputDialog::getInt(this, "DFS", "Начальная вершина:",
                                     0, 0, graphWidget->vertexCount() - 1, 1, &ok);
    if (ok) {
        graphWidget->depthFirstSearch(start);
    }
}

void MainWindow::onDijkstraClicked()
{
    bool ok1, ok2;
    int from = QInputDialog::getInt(this, "Дейкстра", "Откуда:",
                                    0, 0, graphWidget->vertexCount() - 1, 1, &ok1);
    int to = QInputDialog::getInt(this, "Дейкстра", "Куда:",
                                  0, 0, graphWidget->vertexCount() - 1, 1, &ok2);
    if (ok1 && ok2) {
        graphWidget->dijkstra(from, to);
    }
}

void MainWindow::onFloydClicked()
{
    graphWidget->floydWarshall();
}

void MainWindow::onTSPClicked()
{
    graphWidget->solveTSP();
}

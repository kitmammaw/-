#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <algorithm>
#include <climits>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    initializeMatrix();
    updateVisualization();
}

MainWindow::~MainWindow() {
    delete ui;
}

Node* MainWindow::createNode(const QVector<QVector<int>>& parentMatrix,
                             const QVector<int>& path, int level, int i, int j) {
    Node* node = new Node;
    node->path = path;
    if (level != 0) node->path.push_back(j);

    node->reducedMatrix = parentMatrix;
    node->level = level;
    node->vertex = j;

    const int N = parentMatrix.size();
    for (int k = 0; k < N && level != 0; k++) {
        node->reducedMatrix[i][k] = -1;
        node->reducedMatrix[k][j] = -1;
    }
    node->reducedMatrix[j][0] = -1;
    return node;
}

void MainWindow::reduceMatrix(QVector<QVector<int>>& matrix, int& cost) {
    const int N = matrix.size();
    // Редукция строк
    for (int i = 0; i < N; i++) {
        int min_val = INT_MAX;
        for (int j = 0; j < N; j++)
            if (matrix[i][j] != -1 && matrix[i][j] < min_val)
                min_val = matrix[i][j];

        if (min_val != INT_MAX && min_val != 0) {
            for (int j = 0; j < N; j++)
                if (matrix[i][j] != -1)
                    matrix[i][j] -= min_val;
            cost += min_val;
        }
    }

    // Редукция столбцов
    for (int j = 0; j < N; j++) {
        int min_val = INT_MAX;
        for (int i = 0; i < N; i++)
            if (matrix[i][j] != -1 && matrix[i][j] < min_val)
                min_val = matrix[i][j];

        if (min_val != INT_MAX && min_val != 0) {
            for (int i = 0; i < N; i++)
                if (matrix[i][j] != -1)
                    matrix[i][j] -= min_val;
            cost += min_val;
        }
    }
}

void MainWindow::solveTSP() {
    const int N = currentMatrix.size();
    if (N == 0) return;

    QVector<Node*> pq;
    QVector<int> path = {0};
    Node* root = createNode(currentMatrix, path, 0, -1, 0);
    reduceMatrix(root->reducedMatrix, root->cost);
    pq.push_back(root);

    optimalCost = INT_MAX;
    optimalPath.clear();
    steps.clear();
    currentStep = 0;

    while (!pq.empty()) {
        auto it = std::min_element(pq.begin(), pq.end(), [](const Node* a, const Node* b) {
            return a->cost < b->cost;
        });
        Node* min = *it;
        pq.erase(it);

        if (min->level == N - 1) {
            min->path.push_back(0);
            if (min->cost < optimalCost) {
                optimalCost = min->cost;
                optimalPath = min->path;
                steps.clear();
                for (int i = 0; i < optimalPath.size() - 1; i++)
                    steps.append({optimalPath[i], optimalPath[i+1]});
            }
            delete min;
            continue;
        }

        for (int j = 0; j < N; j++) {
            if (min->reducedMatrix[min->vertex][j] != -1) {
                Node* child = createNode(min->reducedMatrix, min->path,
                                         min->level + 1, min->vertex, j);
                child->cost = min->cost + min->reducedMatrix[min->vertex][j];
                reduceMatrix(child->reducedMatrix, child->cost);
                pq.push_back(child);
            }
        }
        delete min;
    }

    QStringList pathStr;
    QStringList labels = {"A", "B", "C", "D"};
    for (int v : optimalPath) pathStr << labels[v];

    ui->resultLabel->setText(QString("Оптимальный путь: %1\nДлина пути: %2")
                                 .arg(pathStr.join(" → ")).arg(optimalCost));
}

void MainWindow::initializeMatrix() {
    currentMatrix = originalMatrix;
    optimalPath.clear();
    optimalCost = INT_MAX;
    steps.clear();
    currentStep = 0;

    ui->matrixTable->setRowCount(currentMatrix.size());
    ui->matrixTable->setColumnCount(currentMatrix.size());

    QStringList labels = {"A", "B", "C", "D"};
    ui->matrixTable->setHorizontalHeaderLabels(labels);
    ui->matrixTable->setVerticalHeaderLabels(labels);

    for (int i = 0; i < currentMatrix.size(); ++i) {
        for (int j = 0; j < currentMatrix[i].size(); ++j) {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText(currentMatrix[i][j] == -1 ? "∞" : QString::number(currentMatrix[i][j]));
            ui->matrixTable->setItem(i, j, item);
        }
    }
    drawGraph();
}

void MainWindow::updateVisualization() {
    for (int i = 0; i < currentMatrix.size(); ++i) {
        for (int j = 0; j < currentMatrix[i].size(); ++j) {
            QTableWidgetItem *item = ui->matrixTable->item(i, j);
            if (!item) item = new QTableWidgetItem();
            item->setText(currentMatrix[i][j] == -1 ? "∞" : QString::number(currentMatrix[i][j]));
        }
    }

    drawGraph();

    if (currentStep > 0 && currentStep <= steps.size()) {
        QVector<int> path;
        for (int i = 0; i < currentStep; i++) {
            path.append(steps[i].first);
            if (i == currentStep - 1) path.append(steps[i].second);
        }
        highlightPath(path);
    }

    if (!optimalPath.isEmpty() && currentStep >= steps.size()) {
        highlightPath(optimalPath);
    }
}

void MainWindow::drawGraph() {
    QGraphicsScene *scene = ui->graphicsView->scene();
    scene->clear();

    QStringList labels = {"A", "B", "C", "D"};
    QVector<QPointF> positions;
    int radius = 150;
    QPointF center(200, 200);

    for (int i = 0; i < labels.size(); ++i) {
        double angle = 2 * M_PI * i / labels.size();
        positions.append(QPointF(center.x() + radius * cos(angle),
                                 center.y() + radius * sin(angle)));
    }

    for (int i = 0; i < currentMatrix.size(); ++i) {
        for (int j = 0; j < currentMatrix[i].size(); ++j) {
            if (i != j && currentMatrix[i][j] != -1) {
                scene->addLine(QLineF(positions[i], positions[j]), QPen(Qt::gray, 1));
            }
        }
    }

    for (int i = 0; i < labels.size(); ++i) {
        scene->addEllipse(positions[i].x() - 20, positions[i].y() - 20, 40, 40,
                          QPen(Qt::black), QBrush(Qt::lightGray));
        QGraphicsTextItem *label = scene->addText(labels[i]);
        label->setPos(positions[i].x() - 5, positions[i].y() - 8);
    }
}

void MainWindow::highlightPath(const QVector<int>& path) {
    QGraphicsScene *scene = ui->graphicsView->scene();

    // Сохраняем все элементы, кроме тех, что нужно перерисовать
    QList<QGraphicsItem*> items = scene->items();
    QVector<QGraphicsItem*> itemsToKeep;

    // Определяем какие элементы оставить (текстовые метки и узлы не из пути)
    for (QGraphicsItem* item : items) {
        if (QGraphicsTextItem* textItem = dynamic_cast<QGraphicsTextItem*>(item)) {
            itemsToKeep.append(textItem);
        }
        else if (QGraphicsEllipseItem* ellipseItem = dynamic_cast<QGraphicsEllipseItem*>(item)) {
            bool isInPath = false;
            QPointF pos = ellipseItem->rect().center();

            // Проверяем, принадлежит ли текущий узел к пути
            QStringList labels = {"A", "B", "C", "D"};
            QVector<QPointF> positions;
            int radius = 150;
            QPointF center(200, 200);

            for (int i = 0; i < labels.size(); ++i) {
                double angle = 2 * M_PI * i / labels.size();
                positions.append(QPointF(center.x() + radius * cos(angle),
                                         center.y() + radius * sin(angle)));
            }

            for (int v : path) {
                if (qAbs(positions[v].x() - pos.x()) < 5 &&
                    qAbs(positions[v].y() - pos.y()) < 5) {
                    isInPath = true;
                    break;
                }
            }

            if (!isInPath) {
                itemsToKeep.append(ellipseItem);
            }
        }
    }

    // Создаем новую сцену и переносим в нее нужные элементы
    QGraphicsScene* newScene = new QGraphicsScene(this);
    for (QGraphicsItem* item : itemsToKeep) {
        newScene->addItem(item);
    }
    ui->graphicsView->setScene(newScene);

    // Теперь рисуем подсветку поверх существующих элементов
    QStringList labels = {"A", "B", "C", "D"};
    QVector<QPointF> positions;
    int radius = 150;
    QPointF center(200, 200);

    for (int i = 0; i < labels.size(); ++i) {
        double angle = 2 * M_PI * i / labels.size();
        positions.append(QPointF(center.x() + radius * cos(angle),
                                 center.y() + radius * sin(angle)));
    }

    // Подсвечиваем ребра пути
    for (int i = 0; i < path.size() - 1; ++i) {
        QGraphicsLineItem *edge = newScene->addLine(QLineF(positions[path[i]],
                                                           positions[path[i+1]]));
        edge->setPen(QPen(Qt::red, 2));
        edge->setZValue(1);
    }

    // Подсвечиваем вершины пути
    for (int v : path) {
        QGraphicsEllipseItem *node = newScene->addEllipse(positions[v].x() - 22,
                                                          positions[v].y() - 22,
                                                          44, 44,
                                                          QPen(Qt::blue, 2),
                                                          QBrush(Qt::lightGray));
        node->setZValue(2);

        // Добавляем текст поверх подсвеченного узла
        QGraphicsTextItem *label = newScene->addText(labels[v]);
        label->setPos(positions[v].x() - 5, positions[v].y() - 8);
        label->setZValue(3); // Текст поверх всего
    }

    // Удаляем старую сцену
    delete scene;
}

void MainWindow::on_solveButton_clicked() {
    solveTSP();
    updateVisualization();
}

void MainWindow::on_stepButton_clicked() {
    if (currentStep <= steps.size()) {
        currentStep++;
        updateVisualization();
    }
}

void MainWindow::on_resetButton_clicked() {
    initializeMatrix();
    ui->graphicsView->scene()->clear();
    drawGraph();
    ui->resultLabel->clear();
}

void MainWindow::on_loadMatrixButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть матрицу", "", "Текстовые файлы (*.txt)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
        return;
    }

    QVector<QVector<int>> newMatrix;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QStringList values = in.readLine().split(" ", Qt::SkipEmptyParts);
        QVector<int> row;
        for (const QString &value : values)
            row.append(value == "∞" || value == "-" ? -1 : value.toInt());
        if (!row.isEmpty()) newMatrix.append(row);
    }

    if (newMatrix.size() > 0 && newMatrix.size() == newMatrix[0].size()) {
        originalMatrix = newMatrix;
        initializeMatrix();
    } else {
        QMessageBox::warning(this, "Ошибка", "Некорректный формат матрицы");
    }
}

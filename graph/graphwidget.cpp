#include "graphwidget.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QWheelEvent>
#include <QMessageBox>
#include <QInputDialog>
#include <QColorDialog>
#include <climits>
#include <algorithm>
#include <QDebug>

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 600);
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}

GraphWidget::~GraphWidget()
{
    clearTraversal();
}

void GraphWidget::addVertex(int x, int y, int number) {
    if (number < 0) {
        QMessageBox::warning(nullptr, "Ошибка", "Номер вершины не может быть отрицательным");
        return;
    }

    // Проверяем, существует ли уже вершина с таким номером
    if (number < vertices.size() && vertices[number].ellipse != nullptr) {
        QMessageBox::warning(nullptr, "Ошибка", "Вершина с таким номером уже существует");
        return;
    }

    // Увеличиваем размер вектора вершин, если нужно
    if (number >= vertices.size()) {
        vertices.resize(number + 1);

        // Запоминаем старый размер матрицы
        int oldSize = adjacencyMatrix.size();

        // Расширяем матрицы смежности и весов
        adjacencyMatrix.resize(number + 1);
        edgeWeights.resize(number + 1);

        for (int i = 0; i <= number; ++i) {
            // Если строка новая, создаём её
            if (i >= oldSize) {
                adjacencyMatrix[i] = QVector<int>(number + 1, 0);
                edgeWeights[i] = QVector<int>(number + 1, 0);
            }
            // Если строка старая, расширяем её
            else {
                adjacencyMatrix[i].resize(number + 1);
                edgeWeights[i].resize(number + 1);
                // Инициализируем новые элементы в старых строках
                for (int j = oldSize; j <= number; ++j) {
                    adjacencyMatrix[i][j] = 0;
                    edgeWeights[i][j] = 0;
                }
            }
        }
    }

    // Создаём вершину
    Vertex &v = vertices[number];
    v.x = x;
    v.y = y;

    // Создаём графические элементы
    v.ellipse = scene()->addEllipse(v.x - 15, v.y - 15, 30, 30,
                                    QPen(Qt::black), QBrush(Qt::white));
    v.label = scene()->addText(QString::number(number));
    QFont font = v.label->font();
    font.setPointSize(12);
    v.label->setFont(font);
    v.label->setDefaultTextColor(Qt::black); // Устанавливаем черный цвет текста
    QRectF textRect = v.label->boundingRect();
    v.label->setPos(v.x - textRect.width() / 2, v.y - textRect.height() / 2);

    emit vertexAdded(number);
}

void GraphWidget::removeVertex(int index)
{
    if (index < 0 || index >= vertices.size() || vertices[index].ellipse == nullptr) {
        QMessageBox::warning(nullptr, "Ошибка", "Неверный индекс вершины");
        return;
    }

    // Удаляем все ребра, связанные с этой вершиной
    for (int i = 0; i < vertices.size(); ++i) {
        if (i == index) continue;

        if (adjacencyMatrix[index][i] != 0) {
            adjacencyMatrix[index][i] = 0;
            adjacencyMatrix[i][index] = 0;
            edgeWeights[index][i] = 0;
            edgeWeights[i][index] = 0;
        }
    }

    // Удаляем вершину
    vertices[index].ellipse = nullptr;
    vertices[index].label = nullptr;

    // Перерисовываем граф
    redrawGraph();

    emit vertexRemoved(index);
}

void GraphWidget::addEdge(int from, int to)
{
    if (from < 0 || to < 0 || from >= vertices.size() || to >= vertices.size() ||
        vertices[from].ellipse == nullptr || vertices[to].ellipse == nullptr) {
        QMessageBox::warning(nullptr, "Ошибка", "Неверные индексы вершин");
        return;
    }

    if (from == to) {
        QMessageBox::warning(nullptr, "Ошибка", "Нельзя создать петлю");
        return;
    }

    adjacencyMatrix[from][to] = 1;
    adjacencyMatrix[to][from] = 1;

    // Устанавливаем вес по умолчанию
    edgeWeights[from][to] = 1;
    edgeWeights[to][from] = 1;

    redrawGraph();

    emit edgeAdded(from, to);
}

void GraphWidget::removeEdge(int from, int to)
{
    if (from < 0 || to < 0 || from >= vertices.size() || to >= vertices.size()) {
        QMessageBox::warning(nullptr, "Ошибка", "Неверные индексы вершин");
        return;
    }

    if (adjacencyMatrix[from][to] == 0) {
        QMessageBox::warning(nullptr, "Ошибка", "Ребро не существует");
        return;
    }

    adjacencyMatrix[from][to] = 0;
    adjacencyMatrix[to][from] = 0;
    edgeWeights[from][to] = 0;
    edgeWeights[to][from] = 0;

    redrawGraph();

    emit edgeRemoved(from, to);
}

void GraphWidget::setEdgeWeight(int from, int to, int weight)
{
    if (from < 0 || to < 0 || from >= vertices.size() || to >= vertices.size()) {
        QMessageBox::warning(nullptr, "Ошибка", "Неверные индексы вершин");
        return;
    }

    if (adjacencyMatrix[from][to] == 0) {
        QMessageBox::warning(nullptr, "Ошибка", "Ребро не существует");
        return;
    }

    if (weight <= 0) {
        QMessageBox::warning(nullptr, "Ошибка", "Вес должен быть положительным");
        return;
    }

    edgeWeights[from][to] = weight;
    edgeWeights[to][from] = weight;

    redrawGraph();

    emit edgeWeightChanged(from, to, weight);
}

void GraphWidget::setAdjacencyMatrix(const QVector<QVector<int>> &matrix)
{
    if (matrix.size() != vertices.size()) {
        QMessageBox::warning(nullptr, "Ошибка", "Размер матрицы не соответствует количеству вершин");
        return;
    }

    adjacencyMatrix = matrix;
    edgeWeights.resize(vertices.size());

    for (int i = 0; i < vertices.size(); ++i) {
        edgeWeights[i].resize(vertices.size());
        for (int j = 0; j < vertices.size(); ++j) {
            edgeWeights[i][j] = (adjacencyMatrix[i][j] != 0) ? 1 : 0;
        }
    }

    redrawGraph();

    emit adjacencyMatrixChanged(adjacencyMatrix);
}

QVector<QVector<int>> GraphWidget::getAdjacencyMatrix() const
{
    return adjacencyMatrix;
}

void GraphWidget::redrawGraph() {
    // Очищаем только рёбра и их подписи
    for (auto line : edgeLines) {
        scene()->removeItem(line);
        delete line;
    }
    edgeLines.clear();

    for (auto label : edgeLabels) {
        scene()->removeItem(label);
        delete label;
    }
    edgeLabels.clear();

    // Радиус вершин (15 по умолчанию, так как размер 30x30)
    const qreal vertexRadius = 15.0;

    // Рисуем рёбра
    for (int i = 0; i < vertices.size(); ++i) {
        if (vertices[i].ellipse == nullptr) continue;

        for (int j = i + 1; j < vertices.size(); ++j) {
            if (vertices[j].ellipse == nullptr) continue;

            if (adjacencyMatrix[i][j] != 0) {
                QPen pen(Qt::black);
                if (edgeWeights[i][j] > 1) {
                    pen.setWidth(2);
                }

                // Координаты центров вершин
                QPointF center1(vertices[i].x, vertices[i].y);
                QPointF center2(vertices[j].x, vertices[j].y);

                // Вектор направления линии
                QPointF direction = center2 - center1;
                qreal length = sqrt(direction.x() * direction.x() + direction.y() * direction.y());

                // Нормализуем вектор
                if (length > 0) {
                    direction /= length;
                }

                // Вычисляем точки начала и конца линии на границах кругов
                QPointF startPoint = center1 + direction * vertexRadius;
                QPointF endPoint = center2 - direction * vertexRadius;

                QGraphicsLineItem* edgeLine = scene()->addLine(
                    QLineF(startPoint, endPoint), pen);
                edgeLines.append(edgeLine);

                // Добавляем подпись веса
                if (edgeWeights[i][j] > 0) {
                    QGraphicsTextItem* weightText = scene()->addText(QString::number(edgeWeights[i][j]));
                    weightText->setDefaultTextColor(Qt::black);
                    // Позиция надписи - середина линии между границами кругов
                    QPointF midPoint = (startPoint + endPoint) / 2;
                    weightText->setPos(midPoint);
                    edgeLabels.append(weightText);
                }
            }
        }
    }
}

void GraphWidget::breadthFirstSearch(int startVertex)
{
    if (startVertex < 0 || startVertex >= vertices.size() || vertices[startVertex].ellipse == nullptr) {
        QMessageBox::warning(nullptr, "Ошибка", "Неверная начальная вершина");
        return;
    }

    clearVisited();
    clearTraversal();

    QQueue<int> queue;
    queue.enqueue(startVertex);
    visited[startVertex] = true;

    QString order = "BFS: ";

    while (!queue.isEmpty()) {
        int v = queue.dequeue();
        bfsTraversal.append(v);
        order += QString::number(v) + " ";

        for (int i = 0; i < vertices.size(); ++i) {
            if (adjacencyMatrix[v][i] != 0 && !visited[i]) {
                visited[i] = true;
                queue.enqueue(i);
            }
        }
    }

    QMessageBox::information(nullptr, "Обход в ширину", order);
}

void GraphWidget::depthFirstSearch(int startVertex)
{
    if (startVertex < 0 || startVertex >= vertices.size() || vertices[startVertex].ellipse == nullptr) {
        QMessageBox::warning(nullptr, "Ошибка", "Неверная начальная вершина");
        return;
    }

    clearVisited();
    clearTraversal();

    dfsRecursive(startVertex);

    QString order = "DFS: ";
    for (int v : dfsTraversal) {
        order += QString::number(v) + " ";
    }

    QMessageBox::information(nullptr, "Обход в глубину", order);
}

void GraphWidget::dfsRecursive(int vertex)
{
    visited[vertex] = true;
    dfsTraversal.append(vertex);

    for (int i = 0; i < vertices.size(); ++i) {
        if (adjacencyMatrix[vertex][i] != 0 && !visited[i]) {
            dfsRecursive(i);
        }
    }
}

void GraphWidget::dijkstra(int startVertex, int endVertex)
{
    if (startVertex < 0 || startVertex >= vertices.size() || vertices[startVertex].ellipse == nullptr ||
        endVertex < 0 || endVertex >= vertices.size() || vertices[endVertex].ellipse == nullptr) {
        QMessageBox::warning(nullptr, "Ошибка", "Неверные вершины");
        return;
    }

    int n = vertices.size();
    QVector<int> dist(n, INT_MAX);
    QVector<int> prev(n, -1);
    QVector<bool> visited(n, false);

    dist[startVertex] = 0;

    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && (v == -1 || dist[j] < dist[v])) {
                v = j;
            }
        }

        if (v == -1 || dist[v] == INT_MAX) {
            break;
        }

        visited[v] = true;

        for (int to = 0; to < n; ++to) {
            if (adjacencyMatrix[v][to] != 0) {
                int alt = dist[v] + edgeWeights[v][to];
                if (alt < dist[to]) {
                    dist[to] = alt;
                    prev[to] = v;
                }
            }
        }
    }

    if (dist[endVertex] == INT_MAX) {
        QMessageBox::information(nullptr, "Алгоритм Дейкстры", "Путь не существует");
        return;
    }

    QVector<int> path;
    for (int v = endVertex; v != -1; v = prev[v]) {
        path.prepend(v);
    }

    QString pathStr;
    for (int v : path) {
        pathStr += QString::number(v) + " ";
    }

    QMessageBox::information(nullptr, "Алгоритм Дейкстры",
                             QString("Кратчайшее расстояние: %1\nПуть: %2").arg(dist[endVertex]).arg(pathStr));

    highlightPath(path, Qt::red);
}

void GraphWidget::floydWarshall()
{
    int n = vertices.size();
    if (n == 0) return;

    QVector<QVector<int>> dist(n, QVector<int>(n));

    // Инициализация матрицы расстояний
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                dist[i][j] = 0;
            } else if (adjacencyMatrix[i][j] != 0) {
                dist[i][j] = edgeWeights[i][j];
            } else {
                dist[i][j] = INT_MAX / 2; // Чтобы избежать переполнения
            }
        }
    }

    // Алгоритм Флойда-Уоршелла
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Формирование результата
    QString result = "Матрица кратчайших расстояний:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == INT_MAX / 2) {
                result += "∞ ";
            } else {
                result += QString::number(dist[i][j]) + " ";
            }
        }
        result += "\n";
    }

    QMessageBox::information(nullptr, "Алгоритм Флойда-Уоршелла", result);
}

void GraphWidget::solveTSP()
{
    int n = vertices.size();
    if (n < 2) {
        QMessageBox::warning(nullptr, "Ошибка", "Недостаточно вершин для задачи коммивояжера");
        return;
    }

    // Проверяем, является ли граф полным
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && adjacencyMatrix[i][j] == 0) {
                QMessageBox::warning(nullptr, "Ошибка", "Граф должен быть полным для задачи коммивояжера");
                return;
            }
        }
    }

    QVector<int> vertexIndices;
    for (int i = 0; i < n; ++i) {
        vertexIndices.append(i);
    }

    QVector<int> bestPath;
    int minCost = INT_MAX;

    // Генерация всех перестановок вершин
    do {
        int currentCost = 0;
        bool valid = true;

        // Вычисляем стоимость текущего пути
        for (int i = 0; i < n - 1; ++i) {
            int from = vertexIndices[i];
            int to = vertexIndices[i + 1];
            currentCost += edgeWeights[from][to];
        }

        // Добавляем возвращение в начальную вершину
        currentCost += edgeWeights[vertexIndices[n - 1]][vertexIndices[0]];

        if (currentCost < minCost) {
            minCost = currentCost;
            bestPath = vertexIndices;
        }

    } while (std::next_permutation(vertexIndices.begin() + 1, vertexIndices.end()));

    // Формируем результат
    QString result = "Оптимальный маршрут: ";
    for (int v : bestPath) {
        result += QString::number(v) + " -> ";
    }
    result += QString::number(bestPath[0]); // Возвращаемся в начало
    result += QString("\nОбщая стоимость: %1").arg(minCost);

    QMessageBox::information(nullptr, "Задача коммивояжера", result);

    // Подсвечиваем путь
    bestPath.append(bestPath[0]); // Для замыкания цикла
    highlightPath(bestPath, Qt::blue);
}

void GraphWidget::highlightPath(const QVector<int>& path, const QColor& color) {
    if (path.size() < 2) return;

    const qreal vertexRadius = 15.0;

    for (int i = 0; i < path.size() - 1; ++i) {
        int from = path[i];
        int to = path[i + 1];

        if (from < 0 || to < 0 || from >= vertices.size() || to >= vertices.size() ||
            vertices[from].ellipse == nullptr || vertices[to].ellipse == nullptr) {
            continue;
        }

        // Координаты центров вершин
        QPointF center1(vertices[from].x, vertices[from].y);
        QPointF center2(vertices[to].x, vertices[to].y);

        // Вектор направления линии
        QPointF direction = center2 - center1;
        qreal length = sqrt(direction.x() * direction.x() + direction.y() * direction.y());

        if (length > 0) {
            direction /= length;
        }

        // Вычисляем точки начала и конца линии на границах кругов
        QPointF startPoint = center1 + direction * vertexRadius;
        QPointF endPoint = center2 - direction * vertexRadius;

        // Подсвечиваем ребро
        QPen pen(color);
        pen.setWidth(3);
        scene()->addLine(QLineF(startPoint, endPoint), pen);

        // Подсвечиваем вершины
        vertices[from].ellipse->setBrush(QBrush(color.lighter(150)));
        vertices[to].ellipse->setBrush(QBrush(color.lighter(150)));
    }
}

void GraphWidget::setWaitingForClick(bool waiting, int vertexNumber)
{
    m_waitingForClick = waiting;
    m_nextVertexNumber = vertexNumber;
}

void GraphWidget::mousePressEvent(QMouseEvent *event)
{
    if (m_waitingForClick) {
        QPointF pt = mapToScene(event->pos());
        addVertex(pt.x(), pt.y(), m_nextVertexNumber);
        m_waitingForClick = false;
        m_nextVertexNumber = -1;
        return;
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->angleDelta().y() / 240.0));
}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100) return;
    scale(scaleFactor, scaleFactor);
}

void GraphWidget::clearVisited()
{
    visited.clear();
    visited.resize(vertices.size());
    for (int i = 0; i < visited.size(); ++i) {
        visited[i] = false;
    }
}

void GraphWidget::clearTraversal()
{
    bfsTraversal.clear();
    dfsTraversal.clear();
}

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);
    painter->fillRect(sceneRect(), Qt::white);
}

#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QVector>
#include <QMouseEvent>
#include <QGraphicsTextItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QQueue>
#include <QStack>

struct Vertex {
    int x, y;
    QGraphicsEllipseItem* ellipse = nullptr;
    QGraphicsTextItem* label = nullptr;
};

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    explicit GraphWidget(QWidget *parent = nullptr);
    ~GraphWidget();

    // Основные операции с графом
    void addVertex(int x, int y, int number);
    void removeVertex(int index);
    void addEdge(int from, int to);
    void removeEdge(int from, int to);
    void setEdgeWeight(int from, int to, int weight);
    void setAdjacencyMatrix(const QVector<QVector<int>> &matrix);
    QVector<QVector<int>> getAdjacencyMatrix() const;

    // Алгоритмы
    void breadthFirstSearch(int startVertex);
    void depthFirstSearch(int startVertex);
    void dijkstra(int startVertex, int endVertex);
    void floydWarshall();
    void solveTSP();

    // Вспомогательные методы
    void setWaitingForClick(bool waiting, int vertexNumber);
    int vertexCount() const { return vertices.size(); }

signals:
    void vertexAdded(int index);
    void vertexRemoved(int index);
    void edgeAdded(int from, int to);
    void edgeRemoved(int from, int to);
    void edgeWeightChanged(int from, int to, int weight);
    void adjacencyMatrixChanged(const QVector<QVector<int>> &matrix);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void scaleView(qreal scaleFactor);
    void clearVisited();
    void clearTraversal();
    void dfsRecursive(int vertex);
    void redrawGraph();
    void highlightPath(const QVector<int>& path, const QColor& color);

    QVector<Vertex> vertices;
    QVector<QVector<int>> adjacencyMatrix;
    QVector<QVector<int>> edgeWeights;
    QVector<bool> visited;
    QVector<int> bfsTraversal;
    QVector<int> dfsTraversal;
    bool m_waitingForClick = false;
    int m_nextVertexNumber = -1;
    QVector<QGraphicsLineItem*> edgeLines;
    QVector<QGraphicsTextItem*> edgeLabels;
};

#endif // GRAPHWIDGET_H

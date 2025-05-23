#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), root(nullptr) {
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    connect(ui->btnBuildTree, &QPushButton::clicked, this, &MainWindow::on_btnBuildTree_clicked);
    connect(ui->btnVisualize, &QPushButton::clicked, this, &MainWindow::on_btnVisualize_clicked);
    connect(ui->btnInsert, &QPushButton::clicked, this, &MainWindow::on_btnInsert_clicked);
    connect(ui->btnDelete, &QPushButton::clicked, this, &MainWindow::on_btnDelete_clicked);
    connect(ui->btnSearch, &QPushButton::clicked, this, &MainWindow::on_btnSearch_clicked);
    connect(ui->btnHeight, &QPushButton::clicked, this, &MainWindow::on_btnHeight_clicked);
    connect(ui->btnPreorder, &QPushButton::clicked, this, &MainWindow::on_btnPreorder_clicked);
    connect(ui->btnInorder, &QPushButton::clicked, this, &MainWindow::on_btnInorder_clicked);
    connect(ui->btnPostorder, &QPushButton::clicked, this, &MainWindow::on_btnPostorder_clicked);
    connect(ui->btnBalance, &QPushButton::clicked, this, &MainWindow::on_btnBalance_clicked);
}

MainWindow::~MainWindow() {
    delete ui;
    clearTree(root);
}

void MainWindow::on_btnBuildTree_clicked() {
    clearTree(root);
    std::vector<char> values = {'D','B','F','A','C','E','G'};
    root = Node::buildPerfectTree(values, 0, values.size() - 1);
    on_btnVisualize_clicked();
}

void MainWindow::on_btnVisualize_clicked() {
    scene->clear();
    if (!root) return;
    drawTree(root, 480, 20, 200, 80, scene);
}

void MainWindow::drawTree(Node* node, int x, int y, int dx, int dy, QGraphicsScene* scene) {
    if (!node) return;
    int radius = 20;
    scene->addEllipse(x - radius, y - radius, 2*radius, 2*radius, QPen(Qt::black));
    QGraphicsTextItem* text = scene->addText(QString(node->data));
    text->setPos(x - 8, y - 12);
    if (node->left) {
        scene->addLine(x, y, x - dx, y + dy);
        drawTree(node->left, x - dx, y + dy, dx / 2, dy, scene);
    }
    if (node->right) {
        scene->addLine(x, y, x + dx, y + dy);
        drawTree(node->right, x + dx, y + dy, dx / 2, dy, scene);
    }
}

void MainWindow::clearTree(Node* node) {
    if (!node) return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

void MainWindow::on_btnInsert_clicked() {
    QString text = ui->lineEditChar->text();
    if (text.isEmpty()) return;
    root = Node::insert(root, text[0].toLatin1());
    on_btnVisualize_clicked();
}

void MainWindow::on_btnDelete_clicked() {
    QString text = ui->lineEditChar->text();
    if (text.isEmpty()) return;
    root = Node::remove(root, text[0].toLatin1());
    on_btnVisualize_clicked();
}

void MainWindow::on_btnSearch_clicked() {
    QString text = ui->lineEditChar->text();
    if (text.isEmpty()) return;
    Node* found = Node::search(root, text[0].toLatin1());
    if (found)
        ui->textEditOutput->setText("Найден узел: " + QString(found->data));
    else
        ui->textEditOutput->setText("Узел не найден.");
}

void MainWindow::on_btnHeight_clicked() {
    int h = Node::height(root);
    ui->textEditOutput->setText("Высота дерева: " + QString::number(h));
}

void MainWindow::on_btnPreorder_clicked() {
    QString output;
    Node::preorder(root, output);
    ui->textEditOutput->setText("Прямой обход: " + output);
}

void MainWindow::on_btnInorder_clicked() {
    QString output;
    Node::inorder(root, output);
    ui->textEditOutput->setText("Симметричный обход: " + output);
}

void MainWindow::on_btnPostorder_clicked() {
    QString output;
    Node::postorder(root, output);
    ui->textEditOutput->setText("Обратный обход: " + output);
}

void MainWindow::on_btnBalance_clicked() {
    Node::balanceTree(root);
    on_btnVisualize_clicked();
}

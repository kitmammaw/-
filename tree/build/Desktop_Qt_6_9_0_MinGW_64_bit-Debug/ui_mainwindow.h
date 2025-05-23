/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btnBuildTree;
    QPushButton *btnVisualize;
    QPushButton *btnInsert;
    QPushButton *btnDelete;
    QPushButton *btnSearch;
    QPushButton *btnHeight;
    QPushButton *btnPreorder;
    QPushButton *btnInorder;
    QPushButton *btnPostorder;
    QPushButton *btnBalance;
    QLineEdit *lineEditChar;
    QTextEdit *textEditOutput;
    QGraphicsView *graphicsView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 700);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        btnBuildTree = new QPushButton(centralwidget);
        btnBuildTree->setObjectName("btnBuildTree");
        btnBuildTree->setGeometry(QRect(20, 20, 120, 30));
        btnVisualize = new QPushButton(centralwidget);
        btnVisualize->setObjectName("btnVisualize");
        btnVisualize->setGeometry(QRect(150, 20, 120, 30));
        btnInsert = new QPushButton(centralwidget);
        btnInsert->setObjectName("btnInsert");
        btnInsert->setGeometry(QRect(280, 20, 80, 30));
        btnDelete = new QPushButton(centralwidget);
        btnDelete->setObjectName("btnDelete");
        btnDelete->setGeometry(QRect(370, 20, 80, 30));
        btnSearch = new QPushButton(centralwidget);
        btnSearch->setObjectName("btnSearch");
        btnSearch->setGeometry(QRect(460, 20, 80, 30));
        btnHeight = new QPushButton(centralwidget);
        btnHeight->setObjectName("btnHeight");
        btnHeight->setGeometry(QRect(550, 20, 80, 30));
        btnPreorder = new QPushButton(centralwidget);
        btnPreorder->setObjectName("btnPreorder");
        btnPreorder->setGeometry(QRect(640, 20, 100, 30));
        btnInorder = new QPushButton(centralwidget);
        btnInorder->setObjectName("btnInorder");
        btnInorder->setGeometry(QRect(750, 20, 100, 30));
        btnPostorder = new QPushButton(centralwidget);
        btnPostorder->setObjectName("btnPostorder");
        btnPostorder->setGeometry(QRect(860, 20, 100, 30));
        btnBalance = new QPushButton(centralwidget);
        btnBalance->setObjectName("btnBalance");
        btnBalance->setGeometry(QRect(20, 60, 120, 30));
        lineEditChar = new QLineEdit(centralwidget);
        lineEditChar->setObjectName("lineEditChar");
        lineEditChar->setGeometry(QRect(160, 60, 60, 30));
        textEditOutput = new QTextEdit(centralwidget);
        textEditOutput->setObjectName("textEditOutput");
        textEditOutput->setGeometry(QRect(240, 60, 720, 50));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(20, 130, 960, 520));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        btnBuildTree->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\321\202\321\200\320\276\320\270\321\202\321\214 \320\264\320\265\321\200\320\265\320\262\320\276", nullptr));
        btnVisualize->setText(QCoreApplication::translate("MainWindow", "\320\222\320\270\320\267\321\203\320\260\320\273\320\270\320\267\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        btnInsert->setText(QCoreApplication::translate("MainWindow", "\320\222\321\201\321\202\320\260\320\262\320\270\321\202\321\214", nullptr));
        btnDelete->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        btnSearch->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        btnHeight->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\201\320\276\321\202\320\260", nullptr));
        btnPreorder->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\321\217\320\274\320\276\320\271 \320\276\320\261\321\205\320\276\320\264", nullptr));
        btnInorder->setText(QCoreApplication::translate("MainWindow", "\320\241\320\270\320\274\320\274. \320\276\320\261\321\205\320\276\320\264", nullptr));
        btnPostorder->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\321\200\320\260\321\202\320\275\321\213\320\271 \320\276\320\261\321\205\320\276\320\264", nullptr));
        btnBalance->setText(QCoreApplication::translate("MainWindow", "\320\221\320\260\320\273\320\260\320\275\321\201\320\270\321\200\320\276\320\262\320\272\320\260", nullptr));
        (void)MainWindow;
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

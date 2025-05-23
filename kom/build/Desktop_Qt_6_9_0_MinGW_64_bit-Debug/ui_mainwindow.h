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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QListWidget *citiesList;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *matrixTable;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_4;
    QGraphicsView *graphicsView;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *solveButton;
    QPushButton *stepButton;
    QPushButton *resetButton;
    QPushButton *loadMatrixButton;
    QLabel *resultLabel;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setVisible(false);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        citiesList = new QListWidget(groupBox);
        citiesList->setObjectName("citiesList");
        citiesList->setStyleSheet(QString::fromUtf8("font: 12pt;"));

        verticalLayout_2->addWidget(citiesList);


        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        matrixTable = new QTableWidget(groupBox_2);
        matrixTable->setObjectName("matrixTable");
        matrixTable->setStyleSheet(QString::fromUtf8("font: 12pt;"));

        verticalLayout_3->addWidget(matrixTable);


        horizontalLayout->addWidget(groupBox_2);


        verticalLayout->addLayout(horizontalLayout);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        verticalLayout_4 = new QVBoxLayout(groupBox_3);
        verticalLayout_4->setObjectName("verticalLayout_4");
        graphicsView = new QGraphicsView(groupBox_3);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setStyleSheet(QString::fromUtf8("background-color: white;"));

        verticalLayout_4->addWidget(graphicsView);


        verticalLayout->addWidget(groupBox_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        solveButton = new QPushButton(centralwidget);
        solveButton->setObjectName("solveButton");
        solveButton->setStyleSheet(QString::fromUtf8("font: 12pt;"));

        horizontalLayout_2->addWidget(solveButton);

        stepButton = new QPushButton(centralwidget);
        stepButton->setObjectName("stepButton");
        stepButton->setStyleSheet(QString::fromUtf8("font: 12pt;"));

        horizontalLayout_2->addWidget(stepButton);

        resetButton = new QPushButton(centralwidget);
        resetButton->setObjectName("resetButton");
        resetButton->setStyleSheet(QString::fromUtf8("font: 12pt;"));

        horizontalLayout_2->addWidget(resetButton);

        loadMatrixButton = new QPushButton(centralwidget);
        loadMatrixButton->setObjectName("loadMatrixButton");
        loadMatrixButton->setStyleSheet(QString::fromUtf8("font: 12pt;"));

        horizontalLayout_2->addWidget(loadMatrixButton);


        verticalLayout->addLayout(horizontalLayout_2);

        resultLabel = new QLabel(centralwidget);
        resultLabel->setObjectName("resultLabel");
        resultLabel->setStyleSheet(QString::fromUtf8("font: 14pt; font-weight: bold;"));
        resultLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(resultLabel);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\321\207\320\260 \320\272\320\276\320\274\320\274\320\270\320\262\320\276\321\217\320\266\320\265\321\200\320\260", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\223\320\276\321\200\320\276\320\264\320\260", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\202\321\200\320\270\321\206\320\260 \321\200\320\260\321\201\321\201\321\202\320\276\321\217\320\275\320\270\320\271", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\320\223\321\200\320\260\321\204", nullptr));
        solveButton->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\321\210\320\270\321\202\321\214", nullptr));
        stepButton->setText(QCoreApplication::translate("MainWindow", "\320\250\320\260\320\263", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\261\321\200\320\276\321\201", nullptr));
        loadMatrixButton->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\274\320\260\321\202\321\200\320\270\321\206\321\203", nullptr));
        resultLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

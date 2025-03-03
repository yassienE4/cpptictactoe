/********************************************************************************
** Form generated from reading UI file 'aigamewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AIGAMEWINDOW_H
#define UI_AIGAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AiGameWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *TM;
    QPushButton *MM;
    QPushButton *TL;
    QPushButton *TR;
    QPushButton *ML;
    QPushButton *MR;
    QPushButton *BL;
    QPushButton *BM;
    QPushButton *BR;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AiGameWindow)
    {
        if (AiGameWindow->objectName().isEmpty())
            AiGameWindow->setObjectName("AiGameWindow");
        AiGameWindow->resize(800, 600);
        centralwidget = new QWidget(AiGameWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(140, 80, 411, 271));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        TM = new QPushButton(gridLayoutWidget);
        TM->setObjectName("TM");

        gridLayout->addWidget(TM, 0, 1, 1, 1);

        MM = new QPushButton(gridLayoutWidget);
        MM->setObjectName("MM");

        gridLayout->addWidget(MM, 1, 1, 1, 1);

        TL = new QPushButton(gridLayoutWidget);
        TL->setObjectName("TL");

        gridLayout->addWidget(TL, 0, 0, 1, 1);

        TR = new QPushButton(gridLayoutWidget);
        TR->setObjectName("TR");

        gridLayout->addWidget(TR, 0, 2, 1, 1);

        ML = new QPushButton(gridLayoutWidget);
        ML->setObjectName("ML");

        gridLayout->addWidget(ML, 1, 0, 1, 1);

        MR = new QPushButton(gridLayoutWidget);
        MR->setObjectName("MR");

        gridLayout->addWidget(MR, 1, 2, 1, 1);

        BL = new QPushButton(gridLayoutWidget);
        BL->setObjectName("BL");

        gridLayout->addWidget(BL, 2, 0, 1, 1);

        BM = new QPushButton(gridLayoutWidget);
        BM->setObjectName("BM");

        gridLayout->addWidget(BM, 2, 1, 1, 1);

        BR = new QPushButton(gridLayoutWidget);
        BR->setObjectName("BR");

        gridLayout->addWidget(BR, 2, 2, 1, 1);

        AiGameWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AiGameWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        AiGameWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(AiGameWindow);
        statusbar->setObjectName("statusbar");
        AiGameWindow->setStatusBar(statusbar);

        retranslateUi(AiGameWindow);

        QMetaObject::connectSlotsByName(AiGameWindow);
    } // setupUi

    void retranslateUi(QMainWindow *AiGameWindow)
    {
        AiGameWindow->setWindowTitle(QCoreApplication::translate("AiGameWindow", "MainWindow", nullptr));
        TM->setText(QCoreApplication::translate("AiGameWindow", "PushButton", nullptr));
        MM->setText(QCoreApplication::translate("AiGameWindow", "PushButton", nullptr));
        TL->setText(QCoreApplication::translate("AiGameWindow", "PushButton", nullptr));
        TR->setText(QCoreApplication::translate("AiGameWindow", "PushButton", nullptr));
        ML->setText(QCoreApplication::translate("AiGameWindow", "PushButton", nullptr));
        MR->setText(QCoreApplication::translate("AiGameWindow", "PushButton", nullptr));
        BL->setText(QCoreApplication::translate("AiGameWindow", "PushButton", nullptr));
        BM->setText(QCoreApplication::translate("AiGameWindow", "PushButton", nullptr));
        BR->setText(QCoreApplication::translate("AiGameWindow", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AiGameWindow: public Ui_AiGameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AIGAMEWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'plazzagui.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAZZAGUI_H
#define UI_PLAZZAGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlazzaGui
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PlazzaGui)
    {
        if (PlazzaGui->objectName().isEmpty())
            PlazzaGui->setObjectName(QStringLiteral("PlazzaGui"));
        PlazzaGui->resize(1255, 683);
        centralWidget = new QWidget(PlazzaGui);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(140, 220, 80, 25));
        PlazzaGui->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PlazzaGui);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1255, 22));
        PlazzaGui->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PlazzaGui);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        PlazzaGui->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PlazzaGui);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PlazzaGui->setStatusBar(statusBar);

        retranslateUi(PlazzaGui);

        QMetaObject::connectSlotsByName(PlazzaGui);
    } // setupUi

    void retranslateUi(QMainWindow *PlazzaGui)
    {
        PlazzaGui->setWindowTitle(QApplication::translate("PlazzaGui", "PlazzaGui", 0));
        pushButton->setText(QApplication::translate("PlazzaGui", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class PlazzaGui: public Ui_PlazzaGui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAZZAGUI_H

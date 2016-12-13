/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_5;
    QGridLayout *maingrid;
    QLineEdit *imgadd;
    QPushButton *ContrastButton;
    QLabel *msglabel;
    QPushButton *detectlanes;
    QPushButton *undo;
    QLabel *msgbox;
    QPushButton *clear;
    QLabel *imagelabel;
    QPushButton *invertcolors;
    QPushButton *upperbound;
    QPushButton *linearize;
    QFrame *line_2;
    QPushButton *loadimage;
    QPushButton *reset;
    QSlider *BrightnessSlider;
    QPushButton *brightnessbutton;
    QPushButton *baseline;
    QPushButton *drawalllanes;
    QPushButton *lowerbound;
    QPushButton *verticalflip;
    QPushButton *removespecks;
    QPushButton *crop;
    QCustomPlot *customPlot;
    QSlider *ContrastSlider;
    QPushButton *labellanes;
    QPushButton *horizontalflip;
    QPushButton *drawlanes;
    QPushButton *calculatearea;
    QLabel *bllabel;
    QLabel *ublabel;
    QLabel *lblabel;
    QLabel *arealabel;
    QPushButton *normalize;
    QPushButton *clearallgraphs;
    QPushButton *legendonoff;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1169, 720);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_5 = new QGridLayout(centralWidget);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        maingrid = new QGridLayout();
        maingrid->setSpacing(6);
        maingrid->setObjectName(QStringLiteral("maingrid"));
        imgadd = new QLineEdit(centralWidget);
        imgadd->setObjectName(QStringLiteral("imgadd"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(imgadd->sizePolicy().hasHeightForWidth());
        imgadd->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(10);
        imgadd->setFont(font);

        maingrid->addWidget(imgadd, 5, 0, 1, 5);

        ContrastButton = new QPushButton(centralWidget);
        ContrastButton->setObjectName(QStringLiteral("ContrastButton"));

        maingrid->addWidget(ContrastButton, 8, 3, 1, 1);

        msglabel = new QLabel(centralWidget);
        msglabel->setObjectName(QStringLiteral("msglabel"));
        msglabel->setFont(font);

        maingrid->addWidget(msglabel, 0, 8, 1, 1);

        detectlanes = new QPushButton(centralWidget);
        detectlanes->setObjectName(QStringLiteral("detectlanes"));
        sizePolicy.setHeightForWidth(detectlanes->sizePolicy().hasHeightForWidth());
        detectlanes->setSizePolicy(sizePolicy);
        detectlanes->setFont(font);

        maingrid->addWidget(detectlanes, 2, 8, 1, 1);

        undo = new QPushButton(centralWidget);
        undo->setObjectName(QStringLiteral("undo"));
        sizePolicy.setHeightForWidth(undo->sizePolicy().hasHeightForWidth());
        undo->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(9);
        undo->setFont(font1);

        maingrid->addWidget(undo, 7, 6, 1, 1);

        msgbox = new QLabel(centralWidget);
        msgbox->setObjectName(QStringLiteral("msgbox"));
        msgbox->setFont(font);

        maingrid->addWidget(msgbox, 1, 8, 1, 1);

        clear = new QPushButton(centralWidget);
        clear->setObjectName(QStringLiteral("clear"));
        sizePolicy.setHeightForWidth(clear->sizePolicy().hasHeightForWidth());
        clear->setSizePolicy(sizePolicy);
        clear->setFont(font);

        maingrid->addWidget(clear, 9, 8, 1, 1);

        imagelabel = new QLabel(centralWidget);
        imagelabel->setObjectName(QStringLiteral("imagelabel"));
        sizePolicy.setHeightForWidth(imagelabel->sizePolicy().hasHeightForWidth());
        imagelabel->setSizePolicy(sizePolicy);
        imagelabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        maingrid->addWidget(imagelabel, 0, 0, 5, 7);

        invertcolors = new QPushButton(centralWidget);
        invertcolors->setObjectName(QStringLiteral("invertcolors"));
        sizePolicy.setHeightForWidth(invertcolors->sizePolicy().hasHeightForWidth());
        invertcolors->setSizePolicy(sizePolicy);
        invertcolors->setFont(font);

        maingrid->addWidget(invertcolors, 7, 0, 1, 2);

        upperbound = new QPushButton(centralWidget);
        upperbound->setObjectName(QStringLiteral("upperbound"));
        sizePolicy.setHeightForWidth(upperbound->sizePolicy().hasHeightForWidth());
        upperbound->setSizePolicy(sizePolicy);
        upperbound->setFont(font);

        maingrid->addWidget(upperbound, 5, 11, 1, 1);

        linearize = new QPushButton(centralWidget);
        linearize->setObjectName(QStringLiteral("linearize"));
        sizePolicy.setHeightForWidth(linearize->sizePolicy().hasHeightForWidth());
        linearize->setSizePolicy(sizePolicy);
        linearize->setFont(font);

        maingrid->addWidget(linearize, 7, 2, 1, 1);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        sizePolicy.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy);
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        maingrid->addWidget(line_2, 0, 9, 10, 1);

        loadimage = new QPushButton(centralWidget);
        loadimage->setObjectName(QStringLiteral("loadimage"));
        sizePolicy.setHeightForWidth(loadimage->sizePolicy().hasHeightForWidth());
        loadimage->setSizePolicy(sizePolicy);
        loadimage->setFont(font);

        maingrid->addWidget(loadimage, 5, 5, 1, 1);

        reset = new QPushButton(centralWidget);
        reset->setObjectName(QStringLiteral("reset"));
        sizePolicy.setHeightForWidth(reset->sizePolicy().hasHeightForWidth());
        reset->setSizePolicy(sizePolicy);
        reset->setFont(font);

        maingrid->addWidget(reset, 5, 6, 1, 1);

        BrightnessSlider = new QSlider(centralWidget);
        BrightnessSlider->setObjectName(QStringLiteral("BrightnessSlider"));
        sizePolicy.setHeightForWidth(BrightnessSlider->sizePolicy().hasHeightForWidth());
        BrightnessSlider->setSizePolicy(sizePolicy);
        BrightnessSlider->setMinimum(-200);
        BrightnessSlider->setMaximum(200);
        BrightnessSlider->setOrientation(Qt::Horizontal);

        maingrid->addWidget(BrightnessSlider, 8, 1, 1, 2);

        brightnessbutton = new QPushButton(centralWidget);
        brightnessbutton->setObjectName(QStringLiteral("brightnessbutton"));

        maingrid->addWidget(brightnessbutton, 8, 0, 1, 1);

        baseline = new QPushButton(centralWidget);
        baseline->setObjectName(QStringLiteral("baseline"));
        sizePolicy.setHeightForWidth(baseline->sizePolicy().hasHeightForWidth());
        baseline->setSizePolicy(sizePolicy);
        baseline->setFont(font);

        maingrid->addWidget(baseline, 5, 10, 1, 1);

        drawalllanes = new QPushButton(centralWidget);
        drawalllanes->setObjectName(QStringLiteral("drawalllanes"));
        sizePolicy.setHeightForWidth(drawalllanes->sizePolicy().hasHeightForWidth());
        drawalllanes->setSizePolicy(sizePolicy);
        drawalllanes->setFont(font);

        maingrid->addWidget(drawalllanes, 5, 8, 1, 1);

        lowerbound = new QPushButton(centralWidget);
        lowerbound->setObjectName(QStringLiteral("lowerbound"));
        sizePolicy.setHeightForWidth(lowerbound->sizePolicy().hasHeightForWidth());
        lowerbound->setSizePolicy(sizePolicy);
        lowerbound->setFont(font);

        maingrid->addWidget(lowerbound, 5, 12, 1, 1);

        verticalflip = new QPushButton(centralWidget);
        verticalflip->setObjectName(QStringLiteral("verticalflip"));
        sizePolicy.setHeightForWidth(verticalflip->sizePolicy().hasHeightForWidth());
        verticalflip->setSizePolicy(sizePolicy);
        verticalflip->setFont(font);

        maingrid->addWidget(verticalflip, 9, 2, 1, 1);

        removespecks = new QPushButton(centralWidget);
        removespecks->setObjectName(QStringLiteral("removespecks"));
        sizePolicy.setHeightForWidth(removespecks->sizePolicy().hasHeightForWidth());
        removespecks->setSizePolicy(sizePolicy);
        removespecks->setFont(font);

        maingrid->addWidget(removespecks, 9, 0, 1, 1);

        crop = new QPushButton(centralWidget);
        crop->setObjectName(QStringLiteral("crop"));
        sizePolicy.setHeightForWidth(crop->sizePolicy().hasHeightForWidth());
        crop->setSizePolicy(sizePolicy);
        crop->setFont(font);

        maingrid->addWidget(crop, 7, 5, 1, 1);

        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        sizePolicy.setHeightForWidth(customPlot->sizePolicy().hasHeightForWidth());
        customPlot->setSizePolicy(sizePolicy);

        maingrid->addWidget(customPlot, 0, 10, 5, 4);

        ContrastSlider = new QSlider(centralWidget);
        ContrastSlider->setObjectName(QStringLiteral("ContrastSlider"));
        sizePolicy.setHeightForWidth(ContrastSlider->sizePolicy().hasHeightForWidth());
        ContrastSlider->setSizePolicy(sizePolicy);
        ContrastSlider->setSliderPosition(50);
        ContrastSlider->setOrientation(Qt::Horizontal);

        maingrid->addWidget(ContrastSlider, 8, 4, 1, 2);

        labellanes = new QPushButton(centralWidget);
        labellanes->setObjectName(QStringLiteral("labellanes"));
        sizePolicy.setHeightForWidth(labellanes->sizePolicy().hasHeightForWidth());
        labellanes->setSizePolicy(sizePolicy);
        labellanes->setFont(font);

        maingrid->addWidget(labellanes, 3, 8, 1, 1);

        horizontalflip = new QPushButton(centralWidget);
        horizontalflip->setObjectName(QStringLiteral("horizontalflip"));
        sizePolicy.setHeightForWidth(horizontalflip->sizePolicy().hasHeightForWidth());
        horizontalflip->setSizePolicy(sizePolicy);
        horizontalflip->setFont(font);

        maingrid->addWidget(horizontalflip, 9, 1, 1, 1);

        drawlanes = new QPushButton(centralWidget);
        drawlanes->setObjectName(QStringLiteral("drawlanes"));
        sizePolicy.setHeightForWidth(drawlanes->sizePolicy().hasHeightForWidth());
        drawlanes->setSizePolicy(sizePolicy);
        drawlanes->setFont(font);

        maingrid->addWidget(drawlanes, 4, 8, 1, 1);

        calculatearea = new QPushButton(centralWidget);
        calculatearea->setObjectName(QStringLiteral("calculatearea"));
        sizePolicy.setHeightForWidth(calculatearea->sizePolicy().hasHeightForWidth());
        calculatearea->setSizePolicy(sizePolicy);
        calculatearea->setFont(font);

        maingrid->addWidget(calculatearea, 5, 13, 1, 1);

        bllabel = new QLabel(centralWidget);
        bllabel->setObjectName(QStringLiteral("bllabel"));
        bllabel->setFont(font);

        maingrid->addWidget(bllabel, 6, 10, 1, 1);

        ublabel = new QLabel(centralWidget);
        ublabel->setObjectName(QStringLiteral("ublabel"));
        ublabel->setFont(font);

        maingrid->addWidget(ublabel, 6, 11, 1, 1);

        lblabel = new QLabel(centralWidget);
        lblabel->setObjectName(QStringLiteral("lblabel"));
        lblabel->setFont(font);

        maingrid->addWidget(lblabel, 6, 12, 1, 1);

        arealabel = new QLabel(centralWidget);
        arealabel->setObjectName(QStringLiteral("arealabel"));
        arealabel->setFont(font);

        maingrid->addWidget(arealabel, 6, 13, 1, 1);

        normalize = new QPushButton(centralWidget);
        normalize->setObjectName(QStringLiteral("normalize"));
        sizePolicy.setHeightForWidth(normalize->sizePolicy().hasHeightForWidth());
        normalize->setSizePolicy(sizePolicy);
        normalize->setFont(font);

        maingrid->addWidget(normalize, 7, 10, 1, 1);

        clearallgraphs = new QPushButton(centralWidget);
        clearallgraphs->setObjectName(QStringLiteral("clearallgraphs"));
        sizePolicy.setHeightForWidth(clearallgraphs->sizePolicy().hasHeightForWidth());
        clearallgraphs->setSizePolicy(sizePolicy);
        clearallgraphs->setFont(font);

        maingrid->addWidget(clearallgraphs, 7, 13, 1, 1);

        legendonoff = new QPushButton(centralWidget);
        legendonoff->setObjectName(QStringLiteral("legendonoff"));
        sizePolicy.setHeightForWidth(legendonoff->sizePolicy().hasHeightForWidth());
        legendonoff->setSizePolicy(sizePolicy);
        legendonoff->setFont(font);

        maingrid->addWidget(legendonoff, 7, 11, 1, 1);


        gridLayout_5->addLayout(maingrid, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1169, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        ContrastButton->setText(QApplication::translate("MainWindow", "Contrast", 0));
        msglabel->setText(QApplication::translate("MainWindow", "Message", 0));
        detectlanes->setText(QApplication::translate("MainWindow", "Detect Lanes", 0));
        undo->setText(QApplication::translate("MainWindow", "Undo", 0));
        msgbox->setText(QString());
        clear->setText(QApplication::translate("MainWindow", "Clear", 0));
        imagelabel->setText(QString());
        invertcolors->setText(QApplication::translate("MainWindow", "Invert Colors", 0));
        upperbound->setText(QApplication::translate("MainWindow", "Upper Bound", 0));
        linearize->setText(QApplication::translate("MainWindow", "Linearize", 0));
        loadimage->setText(QApplication::translate("MainWindow", "Load Image", 0));
        reset->setText(QApplication::translate("MainWindow", "Reset", 0));
        brightnessbutton->setText(QApplication::translate("MainWindow", "Brightness", 0));
        baseline->setText(QApplication::translate("MainWindow", "Baseline", 0));
        drawalllanes->setText(QApplication::translate("MainWindow", "Draw All Lanes", 0));
        lowerbound->setText(QApplication::translate("MainWindow", "Lower Bound", 0));
        verticalflip->setText(QApplication::translate("MainWindow", "Vertical Flip", 0));
        removespecks->setText(QApplication::translate("MainWindow", "Remove Specks", 0));
        crop->setText(QApplication::translate("MainWindow", "Crop", 0));
        labellanes->setText(QApplication::translate("MainWindow", "Label Lanes", 0));
        horizontalflip->setText(QApplication::translate("MainWindow", "Horizontal Flip", 0));
        drawlanes->setText(QApplication::translate("MainWindow", "Draw Lanes", 0));
        calculatearea->setText(QApplication::translate("MainWindow", "Calculate Area", 0));
        bllabel->setText(QString());
        ublabel->setText(QString());
        lblabel->setText(QString());
        arealabel->setText(QString());
        normalize->setText(QApplication::translate("MainWindow", "Normalize", 0));
        clearallgraphs->setText(QApplication::translate("MainWindow", "Clear All Graphs", 0));
        legendonoff->setText(QApplication::translate("MainWindow", "View/Hide\n"
"Legend", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

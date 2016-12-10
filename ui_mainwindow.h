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
#include <QtWidgets/QCheckBox>
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
    QPushButton *plot;
    QPushButton *removesmear;
    QLabel *imagelabel;
    QFrame *line_2;
    QCustomPlot *customPlot;
    QPushButton *loadimage;
    QLineEdit *imgadd;
    QPushButton *detectlanes;
    QSlider *BrightnessSlider;
    QPushButton *orientation;
    QPushButton *baseline;
    QPushButton *linearize;
    QSlider *ContrastSlider;
    QPushButton *verticalflip;
    QPushButton *background;
    QCheckBox *checkBox;
    QPushButton *crop;
    QPushButton *invertcolors;
    QPushButton *ContrastButton;
    QPushButton *horizontalflip;
    QPushButton *normalizearea;
    QPushButton *calculatearea;
    QPushButton *brightnessbutton;
    QLabel *arealabel;
    QPushButton *removespecks;
    QPushButton *drawlanes;
    QPushButton *labellanes;
    QPushButton *reset;
    QPushButton *undo;
    QFrame *line;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1120, 720);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_5 = new QGridLayout(centralWidget);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        maingrid = new QGridLayout();
        maingrid->setSpacing(6);
        maingrid->setObjectName(QStringLiteral("maingrid"));
        plot = new QPushButton(centralWidget);
        plot->setObjectName(QStringLiteral("plot"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(plot->sizePolicy().hasHeightForWidth());
        plot->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(10);
        plot->setFont(font);

        maingrid->addWidget(plot, 4, 8, 1, 1);

        removesmear = new QPushButton(centralWidget);
        removesmear->setObjectName(QStringLiteral("removesmear"));
        sizePolicy.setHeightForWidth(removesmear->sizePolicy().hasHeightForWidth());
        removesmear->setSizePolicy(sizePolicy);
        removesmear->setFont(font);

        maingrid->addWidget(removesmear, 3, 8, 1, 1);

        imagelabel = new QLabel(centralWidget);
        imagelabel->setObjectName(QStringLiteral("imagelabel"));
        sizePolicy.setHeightForWidth(imagelabel->sizePolicy().hasHeightForWidth());
        imagelabel->setSizePolicy(sizePolicy);
        imagelabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        maingrid->addWidget(imagelabel, 0, 0, 4, 7);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        sizePolicy.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy);
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        maingrid->addWidget(line_2, 0, 9, 9, 1);

        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        sizePolicy.setHeightForWidth(customPlot->sizePolicy().hasHeightForWidth());
        customPlot->setSizePolicy(sizePolicy);

        maingrid->addWidget(customPlot, 0, 10, 4, 4);

        loadimage = new QPushButton(centralWidget);
        loadimage->setObjectName(QStringLiteral("loadimage"));
        sizePolicy.setHeightForWidth(loadimage->sizePolicy().hasHeightForWidth());
        loadimage->setSizePolicy(sizePolicy);
        loadimage->setFont(font);

        maingrid->addWidget(loadimage, 5, 5, 1, 1);

        imgadd = new QLineEdit(centralWidget);
        imgadd->setObjectName(QStringLiteral("imgadd"));
        sizePolicy.setHeightForWidth(imgadd->sizePolicy().hasHeightForWidth());
        imgadd->setSizePolicy(sizePolicy);
        imgadd->setFont(font);

        maingrid->addWidget(imgadd, 5, 0, 1, 5);

        detectlanes = new QPushButton(centralWidget);
        detectlanes->setObjectName(QStringLiteral("detectlanes"));
        sizePolicy.setHeightForWidth(detectlanes->sizePolicy().hasHeightForWidth());
        detectlanes->setSizePolicy(sizePolicy);
        detectlanes->setFont(font);

        maingrid->addWidget(detectlanes, 0, 8, 1, 1);

        BrightnessSlider = new QSlider(centralWidget);
        BrightnessSlider->setObjectName(QStringLiteral("BrightnessSlider"));
        sizePolicy.setHeightForWidth(BrightnessSlider->sizePolicy().hasHeightForWidth());
        BrightnessSlider->setSizePolicy(sizePolicy);
        BrightnessSlider->setMinimum(-200);
        BrightnessSlider->setMaximum(200);
        BrightnessSlider->setOrientation(Qt::Horizontal);

        maingrid->addWidget(BrightnessSlider, 7, 1, 1, 2);

        orientation = new QPushButton(centralWidget);
        orientation->setObjectName(QStringLiteral("orientation"));
        sizePolicy.setHeightForWidth(orientation->sizePolicy().hasHeightForWidth());
        orientation->setSizePolicy(sizePolicy);
        orientation->setFont(font);

        maingrid->addWidget(orientation, 6, 3, 1, 2);

        baseline = new QPushButton(centralWidget);
        baseline->setObjectName(QStringLiteral("baseline"));
        sizePolicy.setHeightForWidth(baseline->sizePolicy().hasHeightForWidth());
        baseline->setSizePolicy(sizePolicy);
        baseline->setFont(font);

        maingrid->addWidget(baseline, 5, 10, 1, 1);

        linearize = new QPushButton(centralWidget);
        linearize->setObjectName(QStringLiteral("linearize"));
        sizePolicy.setHeightForWidth(linearize->sizePolicy().hasHeightForWidth());
        linearize->setSizePolicy(sizePolicy);
        linearize->setFont(font);

        maingrid->addWidget(linearize, 6, 2, 1, 1);

        ContrastSlider = new QSlider(centralWidget);
        ContrastSlider->setObjectName(QStringLiteral("ContrastSlider"));
        sizePolicy.setHeightForWidth(ContrastSlider->sizePolicy().hasHeightForWidth());
        ContrastSlider->setSizePolicy(sizePolicy);
        ContrastSlider->setSliderPosition(50);
        ContrastSlider->setOrientation(Qt::Horizontal);

        maingrid->addWidget(ContrastSlider, 7, 4, 1, 2);

        verticalflip = new QPushButton(centralWidget);
        verticalflip->setObjectName(QStringLiteral("verticalflip"));
        sizePolicy.setHeightForWidth(verticalflip->sizePolicy().hasHeightForWidth());
        verticalflip->setSizePolicy(sizePolicy);
        verticalflip->setFont(font);

        maingrid->addWidget(verticalflip, 8, 5, 1, 1);

        background = new QPushButton(centralWidget);
        background->setObjectName(QStringLiteral("background"));
        sizePolicy.setHeightForWidth(background->sizePolicy().hasHeightForWidth());
        background->setSizePolicy(sizePolicy);
        background->setFont(font);

        maingrid->addWidget(background, 5, 11, 1, 1);

        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        sizePolicy.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy);

        maingrid->addWidget(checkBox, 6, 8, 1, 1);

        crop = new QPushButton(centralWidget);
        crop->setObjectName(QStringLiteral("crop"));
        sizePolicy.setHeightForWidth(crop->sizePolicy().hasHeightForWidth());
        crop->setSizePolicy(sizePolicy);
        crop->setFont(font);

        maingrid->addWidget(crop, 6, 5, 1, 1);

        invertcolors = new QPushButton(centralWidget);
        invertcolors->setObjectName(QStringLiteral("invertcolors"));
        sizePolicy.setHeightForWidth(invertcolors->sizePolicy().hasHeightForWidth());
        invertcolors->setSizePolicy(sizePolicy);
        invertcolors->setFont(font);

        maingrid->addWidget(invertcolors, 6, 0, 1, 2);

        ContrastButton = new QPushButton(centralWidget);
        ContrastButton->setObjectName(QStringLiteral("ContrastButton"));

        maingrid->addWidget(ContrastButton, 7, 3, 1, 1);

        horizontalflip = new QPushButton(centralWidget);
        horizontalflip->setObjectName(QStringLiteral("horizontalflip"));
        sizePolicy.setHeightForWidth(horizontalflip->sizePolicy().hasHeightForWidth());
        horizontalflip->setSizePolicy(sizePolicy);
        horizontalflip->setFont(font);

        maingrid->addWidget(horizontalflip, 8, 3, 1, 2);

        normalizearea = new QPushButton(centralWidget);
        normalizearea->setObjectName(QStringLiteral("normalizearea"));
        sizePolicy.setHeightForWidth(normalizearea->sizePolicy().hasHeightForWidth());
        normalizearea->setSizePolicy(sizePolicy);
        normalizearea->setFont(font);

        maingrid->addWidget(normalizearea, 5, 12, 1, 1);

        calculatearea = new QPushButton(centralWidget);
        calculatearea->setObjectName(QStringLiteral("calculatearea"));
        sizePolicy.setHeightForWidth(calculatearea->sizePolicy().hasHeightForWidth());
        calculatearea->setSizePolicy(sizePolicy);
        calculatearea->setFont(font);

        maingrid->addWidget(calculatearea, 5, 13, 1, 1);

        brightnessbutton = new QPushButton(centralWidget);
        brightnessbutton->setObjectName(QStringLiteral("brightnessbutton"));

        maingrid->addWidget(brightnessbutton, 7, 0, 1, 1);

        arealabel = new QLabel(centralWidget);
        arealabel->setObjectName(QStringLiteral("arealabel"));

        maingrid->addWidget(arealabel, 6, 13, 1, 1);

        removespecks = new QPushButton(centralWidget);
        removespecks->setObjectName(QStringLiteral("removespecks"));
        sizePolicy.setHeightForWidth(removespecks->sizePolicy().hasHeightForWidth());
        removespecks->setSizePolicy(sizePolicy);
        removespecks->setFont(font);

        maingrid->addWidget(removespecks, 8, 1, 1, 2);

        drawlanes = new QPushButton(centralWidget);
        drawlanes->setObjectName(QStringLiteral("drawlanes"));
        sizePolicy.setHeightForWidth(drawlanes->sizePolicy().hasHeightForWidth());
        drawlanes->setSizePolicy(sizePolicy);
        drawlanes->setFont(font);

        maingrid->addWidget(drawlanes, 2, 8, 1, 1);

        labellanes = new QPushButton(centralWidget);
        labellanes->setObjectName(QStringLiteral("labellanes"));
        sizePolicy.setHeightForWidth(labellanes->sizePolicy().hasHeightForWidth());
        labellanes->setSizePolicy(sizePolicy);
        labellanes->setFont(font);

        maingrid->addWidget(labellanes, 1, 8, 1, 1);

        reset = new QPushButton(centralWidget);
        reset->setObjectName(QStringLiteral("reset"));
        sizePolicy.setHeightForWidth(reset->sizePolicy().hasHeightForWidth());
        reset->setSizePolicy(sizePolicy);
        reset->setFont(font);

        maingrid->addWidget(reset, 5, 6, 1, 1);

        undo = new QPushButton(centralWidget);
        undo->setObjectName(QStringLiteral("undo"));
        sizePolicy.setHeightForWidth(undo->sizePolicy().hasHeightForWidth());
        undo->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(9);
        undo->setFont(font1);

        maingrid->addWidget(undo, 6, 6, 1, 1);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        sizePolicy.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy);
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        maingrid->addWidget(line, 7, 8, 1, 1);


        gridLayout_5->addLayout(maingrid, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1120, 21));
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
        plot->setText(QApplication::translate("MainWindow", "Plot", 0));
        removesmear->setText(QApplication::translate("MainWindow", "Remove Smear", 0));
        imagelabel->setText(QString());
        loadimage->setText(QApplication::translate("MainWindow", "Load Image", 0));
        detectlanes->setText(QApplication::translate("MainWindow", "Detect Lanes", 0));
        orientation->setText(QApplication::translate("MainWindow", "Orientation", 0));
        baseline->setText(QApplication::translate("MainWindow", "Baseline", 0));
        linearize->setText(QApplication::translate("MainWindow", "Linearize", 0));
        verticalflip->setText(QApplication::translate("MainWindow", "Vertical Flip", 0));
        background->setText(QApplication::translate("MainWindow", "Background", 0));
        checkBox->setText(QApplication::translate("MainWindow", "Plot on\n"
"same graph", 0));
        crop->setText(QApplication::translate("MainWindow", "Crop", 0));
        invertcolors->setText(QApplication::translate("MainWindow", "Invert Colors", 0));
        ContrastButton->setText(QApplication::translate("MainWindow", "Contrast", 0));
        horizontalflip->setText(QApplication::translate("MainWindow", "Horizontal Flip", 0));
        normalizearea->setText(QApplication::translate("MainWindow", "Normalize Area", 0));
        calculatearea->setText(QApplication::translate("MainWindow", "Calculate Area", 0));
        brightnessbutton->setText(QApplication::translate("MainWindow", "Brightness", 0));
        arealabel->setText(QString());
        removespecks->setText(QApplication::translate("MainWindow", "Remove Specks", 0));
        drawlanes->setText(QApplication::translate("MainWindow", "Draw Lanes", 0));
        labellanes->setText(QApplication::translate("MainWindow", "Label Lanes", 0));
        reset->setText(QApplication::translate("MainWindow", "Reset", 0));
        undo->setText(QApplication::translate("MainWindow", "Undo", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

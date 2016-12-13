#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <QFileDialog>
#include <QInputDialog>
#include <tiff.h>
#include <tiffio.h>
#include <stdarg.h>
#include "qcustomplot.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//git test
//git test 2

int kClamp( int x, int  low, int  high )
{
    if ( x < low )       return low;
    else if ( high < x ) return high;
    else                 return x;
}
//jhu test 3

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    isCropping(false),
    isBrightness(false),
    isContrast(false),
    curralpha (1.0),
    currbeta (0),
    isSquareGel(false),
    scalePixel(1.0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->BrightnessSlider, SIGNAL(valueChanged(int)), this, SLOT(on_BrightnessSlider_changed(int)));
    connect(ui->ContrastSlider, SIGNAL(valueChanged(int)), this, SLOT(on_ContrastSlider_changed(int)));
}



MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::validimage() {
    if (image.isNull()) {
        ui->msgbox->setText("Please load\nan image.");
        return false;
    } else {
        ui->msgbox->clear();
        return true;
    }
}

bool MainWindow::validplot() {
    if (currdata.isEmpty()) {
        ui->msgbox->setText("Please draw a\nlane.");
        return false;
    } else {
        ui->msgbox->clear();
        return true;
    }
}

void MainWindow::showpixmap(QImage a) {
    if (validimage()) {
        QPixmap p = QPixmap::fromImage(a);
        ui->imagelabel->setPixmap(p.scaled(ui->imagelabel->width(),ui->imagelabel->height(),Qt::KeepAspectRatio,Qt::FastTransformation));
    }
}

void MainWindow::loadGel(QString imageaddress)
{
    uint32_t fileTag = 0;
    double scaleFactor = 1.0;
    uint16 count;
    void *data;
    //Open the image using the TIFF library and read the tags
       TIFF* tif = TIFFOpen(imageaddress.toStdString().c_str(), "r");
       if(tif == nullptr)
       {
        cout << "Could not open image" << endl;
       }
       else
       {
           if(1 == TIFFGetFieldDefaulted(tif, 33445, &count, &data))
           {
               fileTag = *(uint32 *)data;
               if(fileTag == 2)
               {
                   isSquareGel = true;
               }
               cout << "fileTag: " << fileTag << endl;
           }
           if(1 == TIFFGetFieldDefaulted(tif, 33446, &count, &data))
           {
               scaleFactor = *(float*)data;
               scalePixel = scaleFactor;
               cout << "scalePixel: " << scaleFactor << endl;
           }
           TIFFClose(tif);
       }

}

void MainWindow::on_loadimage_clicked()
{
    QString imageaddress;

        imageaddress = QDir::toNativeSeparators(QFileDialog::getOpenFileName(this, tr("Select image"), "C:\\", tr("Images (*.png *.gel *.jpg)")));
        cout << imageaddress.toStdString() << endl;
        ui->imgadd->setText(imageaddress);

    image.load(imageaddress);
    initimage.load(imageaddress);
    if(imageaddress.endsWith(".gel", Qt::CaseInsensitive))
    {
        isGelFile = true;
        loadGel(imageaddress);
    }
    else
    {
        isGelFile = false;
    }
    showpixmap(image);

    undoStack.clear();
    undoStack.push(image);
}

void MainWindow::on_invertcolors_clicked()
{
    undoStack.push(image);
    image.invertPixels();
    showpixmap(image);
}

void MainWindow::on_horizontalflip_clicked()
{
    undoStack.push(image);
    image = image.mirrored(true, false);
    showpixmap(image);
}

void MainWindow::on_verticalflip_clicked()
{
    undoStack.push(image);
    image = image.mirrored(false, true);
    showpixmap(image);
}

void MainWindow::on_reset_clicked()
{
    undoStack.clear();
    image = initimage;
    showpixmap(image);
    ui->BrightnessSlider->setSliderPosition(0);
    ui->ContrastSlider->setSliderPosition(50);
    undoStack.push(image);
}

void MainWindow::on_crop_clicked()
{
    if (validimage()) {
        isCropping = true;
        ui->crop->setFlat(true);
    }
}

void MainWindow::on_linearize_clicked()
{
    if (validimage()) {
        QString imageaddress;
            imageaddress = ui->imgadd->text();
            undoStack.push(image);
            if(isGelFile)
            {
                TIFF* tif = TIFFOpen(imageaddress.toStdString().c_str(), "r");
                if(tif == nullptr)
                {
                 cout << "Could not open image" << endl;
                }
                else
                {
                    uint32 imagelength;
                    tsize_t scanline;
                    tdata_t buf;
                    uint32 row;
                    uint32 col;

                    TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &imagelength);

                    scanline = TIFFScanlineSize(tif);
                    buf = _TIFFmalloc(scanline);
                    int pixCheck = 0;
                    for (row = 0; row < imagelength; row++)
                    {
                        TIFFReadScanline(tif, buf, row);
                        for (col = 0; col < scanline; col+=2)
                        {
                            uint16 pixVal = ((uint16*)buf)[col];
                            uint32 longPixVal = pixVal * pixVal;
                            double newPixVal = longPixVal * scalePixel;
                            pixCheck++;
                            uint16 maxVal = 0xFFFF;
                            uint8 scaledMax = 0xFF;

                            uint8 scaledVal = newPixVal / maxVal * scaledMax;
                            image.setPixelColor(col/2,row,QColor(scaledVal,scaledVal,scaledVal));
                            //printf("%f ", newPixVal);
                        }
                        //printf("\n");
                    }
                    cout << pixCheck << endl;
                    _TIFFfree(buf);
                    TIFFClose(tif);
                }
            }
            image=image.copy(0,0,image.width()/2,image.height());
            showpixmap(image);
    }
}

//  Brightness Functions
void MainWindow::on_brightnessbutton_clicked()
{
    if (validimage()) {
        isBrightness = !isBrightness;
        ui->brightnessbutton->setFlat(isBrightness);
        if(isBrightness==false)
        {
            undoStack.push(image);
            image=tempimage;
        }
    }
}

void MainWindow::on_BrightnessSlider_changed(int value)
{
    if (validimage()) {
        if (isBrightness)
        {
            cout<<value<<endl;
            int beta=value;
            currbeta=beta;
            QImage BrightImage=image.copy();
            for (int y = 0; y < image.height(); y++)
            {

                for (int x = 0; x < image.width(); x++)
                {
                    QRgb temp = image.pixel(x,y);
                    int grayVal = qGray(temp);
                    int brightgray = kClamp(grayVal*curralpha+beta, 0, 255);
                    QColor brightcolor(brightgray,brightgray,brightgray);
                    BrightImage.setPixelColor(x,y,brightcolor);

                }

            }
            showpixmap(BrightImage);
            tempimage=BrightImage;
        }
    }
}


//Contrast functions

void MainWindow::on_ContrastButton_clicked()
{
    if (validimage()) {
        isContrast = !isContrast;

        ui->ContrastButton->setFlat(isContrast);
        if(isContrast==false)
        {
            undoStack.push(image);
            image=tempimage;
        }
    }
}

void MainWindow::on_ContrastSlider_changed(int value)
{
    if (validimage()) {
        if (isContrast)
        {
            double alpha;

            if(value < 50)
            {
             alpha = (1.0/3.0) + ( value * (2.0/3.0)/49.0);
            }
            else if(value == 50)
            {
             alpha = 1.0;
            }
            else
            {
             alpha = 1.0 + ((value-50.0) * (1.0/49.0));
            }
            curralpha=alpha;

            QImage ContImage=image.copy();
            for (int y = 0; y < image.height(); y++)
            {

                for (int x = 0; x < image.width(); x++)
                {
                    QRgb temp = image.pixel(x,y);
                    int grayVal = qGray(temp);
                    int contgray = kClamp(grayVal*alpha +currbeta, 0, 255);
                    QColor contcolor(contgray,contgray,contgray);
                    ContImage.setPixelColor(x,y,contcolor);

                }

            }
            showpixmap(ContImage);
            tempimage=ContImage;

        }
    }
}
//This function assumes that the image is just one lane
//not fully tested yet
void MainWindow::on_removespecks_clicked()
{
    //Light pixels are more than the threshold
    //Dark pixels are less than the threshold

    if (validimage()) {
        int darkThreshold = 220;
        int speckThreshold = 5;

        bool ok;
        QInputDialog inputDialog;
        inputDialog.setOption(QInputDialog::NoButtons);
        QString text =  inputDialog.getText(NULL ,"Input Speck Threshold:",
                                                 "Speck Threshold:", QLineEdit::Normal,
                                                 "5", &ok);
        if (ok && !text.isEmpty())
        {
            speckThreshold = atoi(text.toStdString().c_str());
            std::cout<<speckThreshold<<std::endl;
        }

        text =  inputDialog.getText(NULL ,"Dark Threshold:",
                                    "Dark Threshold:", QLineEdit::Normal,
                                    "220", &ok);

        if (ok && !text.isEmpty())
        {
            darkThreshold = atoi(text.toStdString().c_str());
            std::cout<<darkThreshold<<std::endl;
        }
        if (darkThreshold < 0 || darkThreshold > 255) {
            ui->msgbox->setText("Please enter an/integer between/n0 and 255/nfor Dark Threshold.");
        } else {
            ui->msgbox->clear();
            if (speckThreshold < 0 || speckThreshold > 100) {
                ui->msgbox->setText("Please enter an/integer between/n0 and 100/nfor Speck Threshold.");
            } else {
                ui->msgbox->clear();
                int maxBandWidth = 0;
                for (int y = 0; y < image.height(); y++)
                {
                    int len = 0;
                    int maxLen = 0;
                    for (int x = 0; x < image.width(); x++)
                    {
                        QRgb temp = image.pixel(x,y);
                        int grayVal = qGray(temp);
                        if(grayVal < darkThreshold)
                        {
                            len += 1;
                        }
                        else
                        {
                            if(len > maxLen)
                            {
                                maxLen = len;
                            }
                            len = 0;
                        }
                    }
                    if(maxLen > maxBandWidth)
                    {
                        maxBandWidth = maxLen;
                    }
                    maxLen = 0;
                }

                int numPixInSpec = maxBandWidth / speckThreshold;
                undoStack.push(image);

                for (int y = 0; y < image.height(); y++)
                {
                    int len = 0;
                    for (int x = 0; x < image.width(); x++)
                    {
                        QRgb temp = image.pixel(x,y);
                        int grayVal = qGray(temp);
                        if(grayVal < darkThreshold)
                        {
                            len += 1;
                        }
                        else
                        {
                            if(len <= numPixInSpec)
                            {
                                for(int i = 1; i <= len; i++)
                                {
                                   image.setPixelColor(x-i,y,QColor(grayVal,grayVal,grayVal));
                                }
                            }
                            len = 0;
                        }
                    }
                }

                showpixmap(image);
            }
        }
    }
}

void MainWindow::on_detectlanes_clicked()
{
    if (validimage()) {
        counts.clear();
        qcounts.clear();
        for (int y = 0; y < image.height(); y++) {
            for (int x = 0; x < image.width(); x++) {
                QRgb temp = image.pixel(x,y);
                int grayval = qGray(temp);
                if (y==0) {
                    if (grayval<=96) counts.push_back(1);
                    else counts.push_back(0);
                }
                else {
                    if (grayval<=96) counts[x]+=1;
                }
            }
        }
        qcounts = QVector<double>::fromStdVector(counts);
        QVector<double> x = generatex(image.width());
        MainWindow::findpeaks();
        if (!peaklocations.isEmpty()) {
            QImage aaa(image);
            aaa = aaa.convertToFormat(QImage::Format_RGB30);
            QPainter paint(&aaa);
            QPen paintpen(Qt::red);
            paintpen.setWidth(image.width()/150);
            int i = 1;
            for (double location: peaklocations) {
                paint.setPen (paintpen);
                paint.drawLine(location, 0, location, aaa.height());
                i+=1;
            }
            showpixmap(aaa);
        }
    }
}

QVector<double> MainWindow::generatex(int size) {
    QVector<double> x(size);
    for (int i=0; i<x.size(); i++) {
        x[i] = i;
    }
    return x;
}

void MainWindow::makePlot(QVector<double> x, QVector<double> y) {
    ui->customPlot->clearGraphs();
    ui->customPlot->replot();
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    ui->customPlot->graph(0)->setName("Intensity Graph");
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();
    numgraph = 0;
    baselineval = 0;
    lowerbound = 0;
    upperbound = x.size();
    setbaseline = false;
    setupperbound = false;
    setlowerbound = false;
    ui->arealabel->clear();
    ui->bllabel->clear();
    ui->ublabel->clear();
    ui->lblabel->clear();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(ui->imagelabel->underMouse() && isCropping)
    {
        startPoint = event->pos();
        rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
        rubberBand->show();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(ui->imagelabel->underMouse() && isCropping)
    {
        rubberBand->setGeometry(QRect(startPoint, event->pos()).normalized());
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(ui->imagelabel->underMouse() && isCropping){
        endPoint = event->pos();
        rubberBand->hide();
        isCropping = false;

        QPoint a = mapToGlobal(startPoint);
        QPoint b = mapToGlobal(endPoint);

        a = ui->imagelabel->mapFromGlobal(a);
        b = ui->imagelabel->mapFromGlobal(b);

        //This allows us to crop all ways
        if(a.x() > b.x())
        {
            int swapX = a.x();
            a.setX(b.x());
            b.setX(swapX);
        }

        if(a.y() > b.y())
        {
            int swapY = a.y();
            a.setY(b.y());
            b.setY(swapY);
        }

        double sx = ui->imagelabel->pixmap()->rect().width();
        double sy = ui->imagelabel->pixmap()->rect().height();

        sx = image.width() / sx;
        sy = image.height() / sy;
        a.setX(int(a.x() * sx));
        b.setX(int(b.x() * sx));
        a.setY(int(a.y() * sy));
        b.setY(int(b.y() * sy));

        QRect myRect(a, b);

        undoStack.push(image);
        if(b.y() <= image.height() && b.x()<=image.width())
        {
            image = image.copy(myRect);
            showpixmap(image);
        }

        ui->crop->setFlat(false);

        delete rubberBand;
    }
    else if(isCropping)
    {
        rubberBand->hide();
    }
}

void MainWindow::on_drawlanes_clicked()
{
    if (validimage()) {
        if (peaklocations.isEmpty()) {
            ui->msgbox->setText("Please detect\nlanes first.");
        } else {
            ui->msgbox->clear();
            int lanenumber = 1;
            bool ok;
            QInputDialog inputDialog;
            inputDialog.setOption(QInputDialog::NoButtons);
            QString text =  inputDialog.getText(NULL ,"lane number:",
                                                     "lane number:", QLineEdit::Normal,
                                                     "1", &ok);
            if (ok && !text.isEmpty())
            {
                lanenumber = atoi(text.toStdString().c_str());
            }
            if (lanenumber <= 0) {
                ui->msgbox->setText("Please enter a\npositive integer.");
            } else if (lanenumber > peaklocations.size()) {
                ui->msgbox->setText("Please enter a\nnumber less than\nmax lane number.");
            } else {
                ui->msgbox->clear();
                currdata.clear();
                for (int y = 0; y < image.height(); y++) {
                    QRgb temp = image.pixel(peaklocations[lanenumber-1], y);
                    int grayval = qGray(temp);
                    currdata.append(255-grayval);
                }
                QVector<double> x = generatex(image.height());
                makePlot(x, currdata);
            }
        }
    }
}

QVector<double> MainWindow::initialguess(int n) {
    QVector<double> temp(qcounts);
    int start = 0;
    int end = temp.size();
    while (!temp.isEmpty() && temp.first() == 0) {
        start+=1;
        temp.pop_front();
    }
    while (!temp.isEmpty() && temp.last() == 0) {
        end-=1;
        temp.pop_back();
    }
    QVector<double> init(n);
    if (!temp.isEmpty()) {
        int interval = (end-start)/(n+1);
        int curr = start;
        for (int i=0; i<init.size(); i++) {
            curr+=interval;
            init[i] = curr;
        }
    }
    return init;
}

void MainWindow::findpeaks() {
    detectioncomplete = false;
    int n = 12;
    bool ok;
    QInputDialog inputDialog;
    inputDialog.setOption(QInputDialog::NoButtons);
    QString text =  inputDialog.getText(NULL ,"number of lanes:",
                                             "number of lanes:", QLineEdit::Normal,
                                             "12", &ok);
    if (ok && !text.isEmpty())
    {
        n = atoi(text.toStdString().c_str());
    }
    if (n <= 0) {
        ui->msgbox->setText("Please enter a\npositive integer.");
    } else {
        ui->msgbox->clear();
        QVector<double> init(initialguess(n));
        if (init.isEmpty()) {
            ui->msgbox->setText("No lanes detected.");
        } else {
            peaklocations.clear();
            ui->msgbox->clear();
            while (!detectioncomplete) {
                modifylabel(init);
            }
            for (double value: init) {
                peaklocations.append(value);
            }
        }
    }
}


void MainWindow::on_labellanes_clicked()
{
    if (validimage()) {
        if (peaklocations.isEmpty()) {
            ui->msgbox->setText("Please detect\nlanes first.");
        } else {
            ui->msgbox->clear();
            QImage aaa(image);
            aaa = aaa.convertToFormat(QImage::Format_RGB30);
            QPainter paint(&aaa);
            QPen paintpen(Qt::red);
            QFont fontt = font();
            //QFont font("Helvetica");
            int labelsize = aaa.width()/2/peaklocations.size();
            fontt.setPixelSize(labelsize);
            paintpen.setWidth(image.width()/150);
            int i = 1;
            for (double location: peaklocations) {
                paint.setPen (paintpen);
                paint.drawLine(location, 0, location, aaa.height()-labelsize);
                paint.setFont(fontt);
                paint.drawText(location-labelsize/2, aaa.height()-labelsize, labelsize, labelsize, Qt::AlignCenter, QString::number(i));
                i+=1;
            }
            showpixmap(aaa);
        }
    }
}

void MainWindow::modifylabel(QVector<double> &init) {
    QVector<bool> complete;
    for (int i=0; i<init.size(); i++) {
        int start;
        int end;
        if (i==0) {
            start = 0;
            end = (init[0]+init[1])/2;
        }
        else if (i==init.size()-1) {
            start = (init[i]+init[i-1])/2;
            end = image.width();
        } else {
            start = (init[i]+init[i-1])/2;
            end = (init[i]+init[i+1])/2;
        }
        int sum = 0;
        int weight = 0;
        for (int j=start; j<end; j++) {
            sum+=j*qcounts[j];
            weight+=qcounts[j];
        }
        if (weight != 0) {
            if (abs(init[i]-sum/weight) <= 1) {
                complete.append(true);
            } else {
                complete.append(false);
            }
            init[i]=sum/weight;
        }
    }
    if (complete.contains(false)) {
        detectioncomplete = false;
    } else {
        detectioncomplete = true;
    }
}

void MainWindow::on_calculatearea_clicked()
{
    if (validplot()) {
        double sum = 0;
        for (int i=lowerbound; i<upperbound; i++) {
            sum+=currdata[i];
        }
        QString aaa("area = ");
        aaa.append(QString::number(sum));
        ui->arealabel->setText(aaa);
    }
}

void MainWindow::graphhorizontalline(int size, double yval) {
    QVector<double> x = generatex(size);
    QVector<double> y(size, yval);
    ui->customPlot->graph(numbaseline)->setData(x, y);
    ui->customPlot->graph(numbaseline)->setPen(QPen(QColor(255, 100, 0)));
    ui->customPlot->graph(numbaseline)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->graph(numbaseline)->setVisible(true);
    ui->customPlot->replot();
}

void MainWindow::graphupperbound(double size, double xval) {
    QVector<double> y;
    y.append(0);
    y.append(size);
    QVector<double> x(y.size(), xval);
    ui->customPlot->graph(numupperbound)->setData(x, y);
    ui->customPlot->graph(numupperbound)->setPen(QPen(QColor(0, 204, 0)));
    ui->customPlot->graph(numupperbound)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->replot();
}

void MainWindow::graphlowerbound(double size, double xval) {
    QVector<double> y;
    y.append(0);
    y.append(size);
    QVector<double> x(y.size(), xval);
    ui->customPlot->graph(numlowerbound)->setData(x, y);
    ui->customPlot->graph(numlowerbound)->setPen(QPen(QColor(255, 102, 178)));
    ui->customPlot->graph(numlowerbound)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->replot();
}

void MainWindow::on_baseline_clicked()
{
    if (validplot()) {
        if (!clickedbaseline) {
            if (!setbaseline) {
                setbaseline = true;
                ui->customPlot->addGraph();
                numgraph+=1;
                numbaseline = numgraph;
                ui->customPlot->graph(numbaseline)->setName("Baseline");
            }
            ui->baseline->setFlat(true);
            clickedbaseline = true;
            graphhorizontalline(currdata.size(), baselineval);
            connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this,SLOT(startmovingbaseline()));
        } else {
            disconnect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this,SLOT(startmovingbaseline()));
            disconnect(ui->customPlot, SIGNAL(mouseMove(QMouseEvent*)), this,SLOT(movebaseline(QMouseEvent*)));
            disconnect(ui->customPlot, SIGNAL(mouseRelease(QMouseEvent*)), this,SLOT(confirmbaseline(QMouseEvent*)));
            ui->baseline->setFlat(false);
            clickedbaseline = false;
            ui->customPlot->graph(numbaseline)->setVisible(false);
            QString aaa("baseline level\n= ");
            aaa.append(QString::number(baselineval));
            ui->bllabel->setText(aaa);
            QVector<double> temp(currdata);
            currdata.clear();
            for (double data : temp) {
                if (data-baselineval > 0) {
                    currdata.append(data-baselineval);
                } else {
                    currdata.append(0);
                }
            }
            QVector<double> x = generatex(currdata.size());
            ui->customPlot->graph(0)->setData(x, currdata);
            ui->customPlot->replot();
        }
    }
}

double MainWindow::maxqvec(QVector<double> aaa) {
    double max = aaa.first();
    for (double value : aaa) {
        if (value > max) {
            max = value;
        }
    }
    return max;
}

void MainWindow::startmovingbaseline() {
    connect(ui->customPlot, SIGNAL(mouseMove(QMouseEvent*)), this,SLOT(movebaseline(QMouseEvent*)));
}

void MainWindow::movebaseline(QMouseEvent *event) {
    disconnect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this,SLOT(startmovingbaseline()));
    double yval = ui->customPlot->yAxis->pixelToCoord(event->pos().y());
    MainWindow::graphhorizontalline(currdata.size(), yval);
    connect(ui->customPlot, SIGNAL(mouseRelease(QMouseEvent*)), this,SLOT(confirmbaseline(QMouseEvent*)));
}

void MainWindow::confirmbaseline(QMouseEvent *event) {
    disconnect(ui->customPlot, SIGNAL(mouseMove(QMouseEvent*)), this,SLOT(movebaseline(QMouseEvent*)));
    disconnect(ui->customPlot, SIGNAL(mouseRelease(QMouseEvent*)), this,SLOT(confirmbaseline(QMouseEvent*)));
    double yval = ui->customPlot->yAxis->pixelToCoord(event->pos().y());
    if (yval <= 0) baselineval = 0;
    else baselineval = yval;
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this,SLOT(startmovingbaseline()));
}

QColor MainWindow::randomqcolor() {
    int r, g, b;
    r = rand() % 256;
    g = rand() % 256;
    b = rand() % 256;
    return QColor(r, g, b);
}

void MainWindow::on_drawalllanes_clicked()
{
    if (validimage()) {
        if (peaklocations.isEmpty()) {
            ui->msgbox->setText("Please detect\nlanes first.");
        } else {
            ui->customPlot->clearGraphs();
			ui->customPlot->replot();
            ui->msgbox->clear();
            currdata.clear();
            ui->arealabel->clear();
            ui->bllabel->clear();
			ui->ublabel->clear();
            ui->lblabel->clear();
            QVector<double> x = generatex(image.height());
            for (int i=0; i<peaklocations.size(); i++) {
                QVector<double> aaa;
                for (int y = 0; y < image.height(); y++) {
                    QRgb temp = image.pixel(peaklocations[i], y);
                    int grayval = qGray(temp);
                    aaa.append(255-grayval);
                }
				QString name("Lane ");
                name.append(QString::number(i+1));
                ui->customPlot->addGraph();
                ui->customPlot->graph(i)->setData(x, aaa);
                ui->customPlot->graph(i)->setName(name);
                ui->customPlot->graph(i)->setPen(QPen(randomqcolor()));
                ui->customPlot->graph(i)->setLineStyle(QCPGraph::lsLine);
                ui->customPlot->rescaleAxes();
                ui->customPlot->replot();
            }
        }
    }
}

void MainWindow::on_upperbound_clicked()
{
    if (validplot()) {
        if (!clickedupperbound) {
			if (!setupperbound) {
                setupperbound = true;
                ui->customPlot->addGraph();
                numgraph+=1;
                numupperbound = numgraph;
                ui->customPlot->graph(numupperbound)->setName("Upper Bound");
            }
            ui->upperbound->setFlat(true);
            clickedupperbound = true;
            graphupperbound(maxqvec(currdata), upperbound);
            connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this,SLOT(startmovingbound()));
        } else {
            disconnect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this,SLOT(startmovingbound()));
            disconnect(ui->customPlot, SIGNAL(mouseMove(QMouseEvent*)), this,SLOT(movebound(QMouseEvent*)));
            disconnect(ui->customPlot, SIGNAL(mouseRelease(QMouseEvent*)), this,SLOT(confirmbound(QMouseEvent*)));
            ui->upperbound->setFlat(false);
            clickedupperbound = false;
            QString aaa("Upper bound level\n= ");
            aaa.append(QString::number(upperbound));
            ui->ublabel->setText(aaa);
        }
    }
}

void MainWindow::on_lowerbound_clicked()
{
    if (validplot()) {
        if (!clickedlowerbound) {
            if (!setlowerbound) {
                setlowerbound = true;
                ui->customPlot->addGraph();
                numgraph+=1;
                numlowerbound = numgraph;
                ui->customPlot->graph(numlowerbound)->setName("Lower Bound");
            }
            ui->lowerbound->setFlat(true);
            clickedlowerbound = true;
            graphlowerbound(maxqvec(currdata), lowerbound);
            connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this,SLOT(startmovingbound()));
        } else {
            disconnect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this,SLOT(startmovingbound()));
            disconnect(ui->customPlot, SIGNAL(mouseMove(QMouseEvent*)), this,SLOT(movebound(QMouseEvent*)));
            disconnect(ui->customPlot, SIGNAL(mouseRelease(QMouseEvent*)), this,SLOT(confirmbound(QMouseEvent*)));
            ui->lowerbound->setFlat(false);
            clickedlowerbound = false;
            QString aaa("Lower bound level\n= ");
            aaa.append(QString::number(lowerbound));
            ui->lblabel->setText(aaa);
        }
    }
}

void MainWindow::startmovingbound() {
    connect(ui->customPlot, SIGNAL(mouseMove(QMouseEvent*)), this,SLOT(movebound(QMouseEvent*)));
}

void MainWindow::movebound(QMouseEvent *event) {
    disconnect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this,SLOT(startmovingbound()));
    double xval = ui->customPlot->xAxis->pixelToCoord(event->pos().x());
    if (clickedupperbound) {
        MainWindow::graphupperbound(maxqvec(currdata), xval);
    } else if (clickedlowerbound) {
        MainWindow::graphlowerbound(maxqvec(currdata), xval);
    }
    connect(ui->customPlot, SIGNAL(mouseRelease(QMouseEvent*)), this,SLOT(confirmbound(QMouseEvent*)));
}

void MainWindow::confirmbound(QMouseEvent *event) {
    disconnect(ui->customPlot, SIGNAL(mouseMove(QMouseEvent*)), this,SLOT(movebound(QMouseEvent*)));
    disconnect(ui->customPlot, SIGNAL(mouseRelease(QMouseEvent*)), this,SLOT(confirmbound(QMouseEvent*)));
    double xval = ui->customPlot->xAxis->pixelToCoord(event->pos().x());
    if (clickedupperbound) {
        MainWindow::graphupperbound(maxqvec(currdata), xval);
        if (xval <= 0) upperbound = 0;
        else if (xval >= currdata.size()) upperbound = currdata.size();
        else upperbound = xval;
    } else if (clickedlowerbound) {
        MainWindow::graphlowerbound(maxqvec(currdata), xval);
        if (xval <= 0) lowerbound = 0;
        else if (xval >= currdata.size()) lowerbound = currdata.size();
        else lowerbound = xval;
    }
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this,SLOT(startmovingbound()));
}

void MainWindow::on_normalize_clicked()
{
    if (validplot()) {
        double sum = 0;
        for (double yval: currdata) {
            sum+=yval;
        }
        QVector<double> temp(currdata);
        currdata.clear();
        for (double yvall: temp) {
            currdata.append(yvall/sum);
        }
        QVector<double> x = generatex(currdata.size());
        makePlot(x, currdata);
    }
}

void MainWindow::on_legendonoff_clicked()
{
    if (ui->customPlot->legend->visible()) {
        ui->customPlot->legend->setVisible(false);
        ui->customPlot->replot();
    } else {
        ui->customPlot->legend->setVisible(true);
        ui->customPlot->replot();
    }
}

void MainWindow::on_clearallgraphs_clicked()
{
    ui->customPlot->clearGraphs();
    ui->customPlot->replot();
    currdata.clear();
    ui->arealabel->clear();
    ui->ublabel->clear();
    ui->lblabel->clear();
}
void MainWindow::on_clear_clicked()
{
    showpixmap(image);
}

void MainWindow::on_undo_clicked()
{
    if (!undoStack.isEmpty())
    {
        QImage lastImage = undoStack.pop();
        showpixmap(lastImage);
        image=lastImage;
    }

}

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

void MainWindow::showpixmap(QImage a) {
    QPixmap p = QPixmap::fromImage(a);
    ui->imagelabel->setPixmap(p.scaled(ui->imagelabel->width(),ui->imagelabel->height(),Qt::KeepAspectRatio,Qt::FastTransformation));
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
    cout << "width" << image.width() << endl;
    cout << "height" << image.height() << endl;
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

    isCropping = true;
    ui->crop->setFlat(true);
}

void MainWindow::on_linearize_clicked()
{
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

//  Brightness Functions
void MainWindow::on_brightnessbutton_clicked()
{
    isBrightness = !isBrightness;

    ui->brightnessbutton->setFlat(isBrightness);
    if(isBrightness==false)
    {
        undoStack.push(image);
        image=tempimage;
    }


}

void MainWindow::on_BrightnessSlider_changed(int value)
{
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


//Contrast functions

void MainWindow::on_ContrastButton_clicked()
{
    isContrast = !isContrast;

    ui->ContrastButton->setFlat(isContrast);
    if(isContrast==false)
    {
        undoStack.push(image);
        image=tempimage;
    }

}

void MainWindow::on_ContrastSlider_changed(int value)
{
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
//This function assumes that the image is just one lane
//not fully tested yet
void MainWindow::on_removespecks_clicked()
{
    //Light pixels are more than the threshold
    //Dark pixels are less than the threshold

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

void MainWindow::print_vec(vector<int> data) {
    for (int x_k : data)
        std::cout << x_k << " ";
    std::cout << std::endl;
}

void MainWindow::on_detectlanes_clicked()
{
    counts.clear();
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
    qcounts.clear();
    qcounts = QVector<double>::fromStdVector(counts);
    QVector<double> x(image.width());
    for (int i=0; i<image.width(); ++i)
    {
      x[i] = i;
    }
    MainWindow::findpeaks();
    //MainWindow::makePlot(x, qcounts);
}

void MainWindow::makePlot(QVector<double> x, QVector<double> y) {
    ui->customPlot->clearGraphs();
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    ui->customPlot->rescaleAxes();
    //ui->customPlot->xAxis->setRange(0, x.size());
    //ui->customPlot->yAxis->setRange(0, image.height());
    ui->customPlot->replot();
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
    int xval = 1;
    bool ok;
    QInputDialog inputDialog;
    inputDialog.setOption(QInputDialog::NoButtons);
    QString text =  inputDialog.getText(NULL ,"lane number:",
                                             "lane number:", QLineEdit::Normal,
                                             "1", &ok);
    if (ok && !text.isEmpty())
    {
        xval = atoi(text.toStdString().c_str());
    }
    currdata.clear();
    for (int y = 0; y < image.height(); y++) {
        QRgb temp = image.pixel(peaklocations[xval-1], y);
        int grayval = qGray(temp);
        currdata.append(255-grayval);
    }
    QVector<double> x(image.height());
    for (int i=0; i<image.height(); ++i)
    {
      x[i] = i;
    }
    makePlot(x,currdata);
}

QVector<double> MainWindow::initialguess(int n) {
    QVector<double> temp(qcounts);
    int start = 0;
    int end = qcounts.size();
    while (temp.first() == 0) {
        start+=1;
        temp.pop_front();
    }
    while (temp.last() == 0) {
        end-=1;
        temp.pop_back();
    }
    QVector<double> init(n);
    int interval = (end-start)/(n+1);
    int curr = start;
    for (int i=0; i<init.size(); i++) {
        curr+=interval;
        init[i] = curr;
    }
    return init;
}

void MainWindow::findpeaks() {
    peaklocations.clear();
    ui->customPlot->clearGraphs();
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
    QVector<double> init(initialguess(n));

    QVector<double> y1(image.width());
    for (double value: init) {
        y1[value] = 30;
    }

    while (!detectioncomplete) {
        modifylabel(init);
    }
    QVector<double> y2(image.width());
    for (double value: init) {
        peaklocations.append(value);
        y2[value] = 30;
    }

    QVector<double> x(y1.size());
    for (int i=0; i<x.size(); ++i)
    {
      x[i] = i;
    }
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, qcounts);
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setData(x, y1);
    ui->customPlot->graph(1)->setPen(QPen(Qt::green));
    ui->customPlot->addGraph();
    ui->customPlot->graph(2)->setData(x, y2);
    ui->customPlot->graph(2)->setPen(QPen(Qt::red));
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();
}


void MainWindow::on_labellanes_clicked()
{
    if (isLabelling) {
        showpixmap(image);
        isLabelling = false;
    }
    else {
        QImage aaa(image);
        aaa = aaa.convertToFormat(QImage::Format_RGB30);
        QPainter paint(&aaa);
        QPen paintpen(Qt::red);
        QFont font("Helvetica");
        int labelsize = aaa.width()/2/peaklocations.size();
        font.setPixelSize(labelsize);
        paintpen.setWidth(image.width()/300);
        int i = 1;
        for (double location: peaklocations) {
            paint.setPen (paintpen);
            paint.drawLine(location, 0, location, aaa.height()-labelsize);
            paint.setFont(font);
            paint.drawText(location-labelsize/2, aaa.height()-labelsize, labelsize, labelsize, Qt::AlignCenter, QString::number(i));
            i+=1;
        }
        showpixmap(aaa);
        isLabelling = true;
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
    int sum = 0;
    for (double data : currdata) {
        sum+=data;
    }
    QString aaa("area = ");
    aaa.append(QString::number(sum));
    ui->arealabel->setText(aaa);
}

void MainWindow::on_baseline_clicked()
{

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

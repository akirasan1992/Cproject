#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <QFileDialog>
#include <QInputDialog>
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

void MainWindow::on_loadimage_clicked()
{
    QString imageaddress;
    imageaddress = ui->imgadd->text();
    if(ui->imgadd->text().isNull() || ui->imgadd->text().isEmpty())
    {
        imageaddress = QDir::toNativeSeparators(QFileDialog::getOpenFileName(this, tr("Select image"), "C:\\", tr("Images (*.png *.gel *.jpg)")));
        cout << imageaddress.toStdString() << endl;
        ui->imgadd->setText(imageaddress);
    }
    image.load(imageaddress);
    initimage.load(imageaddress);
    if(imageaddress.endsWith(".gel", Qt::CaseInsensitive))
    {
        isGelFile = true;
    }
    else
    {
        isGelFile = false;
    }
    showpixmap(image);
    cout << "width" << image.width() << endl;
    cout << "height" << image.height() << endl;
}

void MainWindow::on_invertcolors_clicked()
{
    image.invertPixels();
    showpixmap(image);
}

void MainWindow::on_horizontalflip_clicked()
{
    image = image.mirrored(true, false);
    showpixmap(image);
}

void MainWindow::on_verticalflip_clicked()
{
    image = image.mirrored(false, true);
    showpixmap(image);
}

void MainWindow::on_reset_clicked()
{
    image = initimage;
    showpixmap(image);
}

void MainWindow::on_crop_clicked()
{
    isCropping = true;
    ui->crop->setFlat(true);
}

void MainWindow::on_linearize_clicked()
{
    const int scaleFactor = 21025;
    QImage image16bit = image.convertToFormat(QImage::Format_RGB16);

    if(isGelFile)
    {
        //for(int i = 0; i < image16bit.width(); i++)
        //{
         //   for(int j = 0; j < image16bit.height(); j++)
          //  {
           //     int pixVal = image16bit.pixel(i,j);
            //    float scaledVal = (float)pixVal * (float)pixVal / (float)scaleFactor;
             //   image16bit.setPixel(i,j,scaledVal);
              //  cout << "Init: " << pixVal << " Scaled: " << scaledVal << endl;
            //}
        //}
        cout << "Bit depth: " << image16bit.depth() << endl;
        showpixmap(image16bit);
    }
}

//  Brightness Functions
void MainWindow::on_brightnessbutton_clicked()
{
    isBrightness = !isBrightness;

    ui->brightnessbutton->setFlat(isBrightness);
    if(isBrightness==false)
    {
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
    qcounts = QVector<double>::fromStdVector(counts);
    QVector<double> x(image.width());
    for (int i=0; i<image.width(); ++i)
    {
      x[i] = i;
    }
    MainWindow::makePlot(x, qcounts);
}

void MainWindow::makePlot(QVector<double> x, QVector<double> y) {
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
    int xval = 120;
    bool ok;
    QInputDialog inputDialog;
    inputDialog.setOption(QInputDialog::NoButtons);
    QString text =  inputDialog.getText(NULL ,"x value:",
                                             "x value:", QLineEdit::Normal,
                                             "120", &ok);
    if (ok && !text.isEmpty())
    {
        xval = atoi(text.toStdString().c_str());
    }
    QVector<double> data;
    for (int y = 0; y < image.height(); y++) {
        QRgb temp = image.pixel(xval, y);
        int grayval = qGray(temp);
        data.append(grayval);
    }
    QVector<double> x(image.height());
    for (int i=0; i<image.height(); ++i)
    {
      x[i] = i;
    }
    makePlot(x,data);
}


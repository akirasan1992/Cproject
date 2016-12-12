#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QRubberBand>
#include <QStack>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_loadimage_clicked();

    void showpixmap(QImage a);

    void on_invertcolors_clicked();

    void on_horizontalflip_clicked();

    void on_verticalflip_clicked();

    void on_reset_clicked();

    void loadGel(QString imageaddress);

    void on_linearize_clicked();

    void on_detectlanes_clicked();

    void on_crop_clicked();

    void on_removespecks_clicked();

    void on_brightnessbutton_clicked();
    void on_ContrastButton_clicked();
    void on_BrightnessSlider_changed(int value);
    void on_ContrastSlider_changed(int value);


    void makePlot(QVector<double> x, QVector<double> y);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void on_drawlanes_clicked();

    void on_labellanes_clicked();
    void modifylabel(QVector<double> &init);
    void findpeaks();
    QVector<double> initialguess(int n);


    void on_calculatearea_clicked();

    void on_baseline_clicked();

    void on_undo_clicked();


    QVector<double> generatex(int size);

    void startmovingbaseline();
    void graphhorizontalline(int size, double yval);
    void movebaseline(QMouseEvent *event);
    void confirmbaseline(QMouseEvent *event);
    bool validimage();
    bool validplot();
    QColor randomqcolor();

    void on_drawalllanes_clicked();

    void on_upperbound_clicked();

    void on_clear_clicked();
    void graphupperbound(int size, double xval);
    double maxqvec(QVector<double> aaa);
    void startmovingbound();
    void movebound(QMouseEvent *event);
    void confirmbound(QMouseEvent *event);

    void on_lowerbound_clicked();
    void graphlowerbound(int size, double xval);


private:
    Ui::MainWindow *ui;
    QImage image;
    QImage initimage;
    QImage tempimage;
    double curralpha;
    int currbeta;
    vector<double> counts;
    QVector<double> qcounts;
    bool isGelFile;
    QRubberBand* rubberBand;
    QPoint startPoint;
    QPoint endPoint;
    bool isCropping;
    bool isBrightness;
    bool isContrast;
    bool isSquareGel;
    double scalePixel;
    bool detectioncomplete = false;
    bool isLabelling = false;
    QVector<double> peaklocations;
    QVector<double> currdata;
    QStack<QImage> undoStack;

    bool clickedbaseline = false;
    double baselineval;
    double upperbound;
    double lowerbound;
    bool clickedupperbound = false;
    bool clickedlowerbound = false;

};

#endif // MAINWINDOW_H

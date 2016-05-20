// http://www.amin-ahmadi.com

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtAndroidExtras>
#include <QImage>
#include <QObject>
#include <mainsetup.h>
#include <QSize>
#include <QStackedWidget>
#include <QLabel>
#include <QScroller>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QVector>
#include <vector>
#include <stdio.h>

using namespace std;
using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setupMainWindow(MainWindow &w);
    QWidget *setupFirstPageWidget();
    QWidget *setupEnhancementsPageWidget();
    QWidget *setupFiltersPageWidget();
    //void setupMainPage(MainWindow &w);

    QImage displayImage;
    QImage displayImage_1;
    QImage displayImage_2;
    QImage displayImage_3;

    QImage loadImage();
    QImage histogramEqualize();
    QImage convertToGray();
    QImage colorBalanceFunction();

private slots:
    void on_pushButton_pressed();

    void on_toolsButton_pressed();
    void on_enhancementsButton_pressed();
    void on_filtersButton_pressed();
    void on_backButton_1_pressed();

    void on_backButton_2_pressed();
    void on_histogramEnhance_pressed();
    void on_grayScale_pressed();
    void on_brightnessEnhance_pressed();
    void on_colorBalance_pressed();

    void on_backButton_3_pressed();
    void on_sepiaFilter_pressed();
    void on_pencilSketch_pressed();
    void on_edgeDetect_pressed();
    void on_imageSegment_pressed();

private:
    Ui::MainWindow *ui;

    MainSetup mainSetup;
    int x,y;

    QLabel *label_1;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QWidget *central;
    QStackedWidget *stack;
    QPushButton *pushButton;
    QStackedWidget *labelStack;
    QWidget *labelWidget_1;
    QWidget *labelWidget_2;
    QWidget *labelWidget_3;
    QWidget *labelWidget_4;

    QWidget *firstPageWidget;
    QPushButton *toolsButton;
    QPushButton *enhancementsButton;
    QPushButton *filtersButton;
    QPushButton *backButton_1;

    QWidget *enhancementsWidget;
    QPushButton *backButton_2;
    QScroller *scroller;
    QPushButton *histogramEnhance;
    QPushButton *grayScale;
    QPushButton *brightnessEnhance;
    QPushButton *colorBalance;

    QWidget *filtersWidget;
    QPushButton *backButton_3;
    QPushButton *sepiaFilter;
    QScroller *filterScroller;
    QPushButton *pencilSketch;
    QPushButton *edgeDetect;
    QPushButton *imageSegment;

    Mat image;
    Mat openedImage;
    Mat result;
    Mat grayImage;
    Mat out;
    Mat sepiaImage;
    vector<Mat> channels;
    vector<Mat> tmpsplit;
    float percent;

    //QStackedWidget *stack;
    //MyThread thread1;
};

#endif // MAINWINDOW_H

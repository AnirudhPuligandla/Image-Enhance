// http://www.amin-ahmadi.com

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPixmap>
#include <QWidget>
#include <QLayout>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QScroller>
#include <QAbstractItemView>
#include <QScrollArea>
#include <QImage>

QString selectedFileName;

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL
Java_com_amin_QtAndroidGallery_QtAndroidGallery_fileSelected(JNIEnv */*env*/,
                                                             jobject /*obj*/,
                                                             jstring results)
{
    selectedFileName = QAndroidJniObject(results).toString();
    qDebug()<<selectedFileName;
}

#ifdef __cplusplus
}
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupMainWindow(MainWindow& w)
{
    QSize size = mainSetup.size();
    w.x = size.width();
    w.y = size.height();
    w.setFixedSize(w.x,w.y);

    central = new QWidget(this);
    label_1 = new QLabel(this);
    label_2 = new QLabel(this);
    label_3 = new QLabel(this);
    label_4 = new QLabel(this);
    stack = new QStackedWidget(this);
    labelStack = new QStackedWidget(this);
    labelWidget_1 = new QWidget(this);
    labelWidget_2 = new QWidget(this);
    labelWidget_3 = new QWidget(this);
    labelWidget_4 = new QWidget(this);
    pushButton = new QPushButton("Open Image",this);
    QObject::connect(pushButton, SIGNAL(pressed()), this, SLOT(on_pushButton_pressed()));
    pushButton->setContentsMargins(0,0,10,0);

    firstPageWidget = w.setupFirstPageWidget();
    enhancementsWidget = w.setupEnhancementsPageWidget();
    filtersWidget = w.setupFiltersPageWidget();

    int y = w.y * 0.8;
    int y1 = w.y*0.8;
    int y2 = w.y/5;

    label_1->setFixedSize(w.x,y);
    label_1->setGeometry(0,0,w.x,y);
    label_2->setFixedSize(w.x,y);
    label_2->setGeometry(0,0,w.x,y);
    label_3->setFixedSize(w.x,y);
    label_3->setGeometry(0,0,w.x,y);

    QHBoxLayout *labelLayout_1 = new QHBoxLayout;
    labelLayout_1->addWidget(label_1);
    labelWidget_1->setLayout(labelLayout_1);

    QHBoxLayout *labelLayout_2 = new QHBoxLayout;
    labelLayout_2->addWidget(label_2);
    labelWidget_2->setLayout(labelLayout_2);

    QHBoxLayout *labelLayout_3 = new QHBoxLayout;
    labelLayout_3->addWidget(label_3);
    labelWidget_3->setLayout(labelLayout_3);

    QHBoxLayout *labelLayout_4 = new QHBoxLayout;
    labelLayout_4->addWidget(label_4);
    labelWidget_4->setLayout(labelLayout_4);

    stack->setFixedSize(w.x,y2);
    stack->setGeometry(0,y1,w.x,y2);
    labelStack->setFixedSize(w.x,y);
    labelStack->setGeometry(0,0,w.x,y);

    stack->addWidget(pushButton);
    stack->addWidget(firstPageWidget);
    stack->addWidget(enhancementsWidget);
    stack->addWidget(filtersWidget);

    labelStack->addWidget(labelWidget_1);
    labelStack->addWidget(labelWidget_2);
    labelStack->addWidget(labelWidget_3);
    labelStack->addWidget(labelWidget_4);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(labelStack);
    vLayout->addWidget(stack);

    central->setLayout(vLayout);
    setCentralWidget(central);

}

void MainWindow::on_pushButton_pressed()
{
    qDebug()<<"button pressed";
    displayImage = loadImage();
    qDebug()<<"back to main window";
    label_1->setPixmap(QPixmap::fromImage(displayImage));
    stack->setCurrentIndex(1);
    labelStack->setCurrentIndex(0);

        /*QImage img(selectedFileName);
        ui->label->setPixmap(QPixmap::fromImage(img));*/
}

QWidget* MainWindow::setupFirstPageWidget()
{
    QWidget *widget1 = new QWidget(this);
    backButton_1 = new QPushButton("back", this);
    QObject::connect(backButton_1, SIGNAL(pressed()), this, SLOT(on_backButton_1_pressed()));
    toolsButton = new QPushButton("Tools", this);
    QObject::connect(toolsButton, SIGNAL(pressed()), this, SLOT(on_toolsButton_pressed()));
    enhancementsButton = new QPushButton("Enhancements", this);
    QObject::connect(enhancementsButton, SIGNAL(pressed()), this, SLOT(on_enhancementsButton_pressed()));
    filtersButton = new QPushButton("Filters", this);
    QObject::connect(filtersButton, SIGNAL(pressed()), this, SLOT(on_filtersButton_pressed()));

    QHBoxLayout *firstPageLayout = new QHBoxLayout;
    firstPageLayout->addWidget(backButton_1);
    firstPageLayout->addWidget(toolsButton);
    firstPageLayout->addWidget(enhancementsButton);
    firstPageLayout->addWidget(filtersButton);

    widget1->setLayout(firstPageLayout);
    return widget1;
}

QWidget *MainWindow::setupEnhancementsPageWidget()
{
    QWidget *widget2 = new QWidget(this);
    QWidget *widget2_final = new QWidget(this);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    backButton_2 = new QPushButton("Back", this);
    QObject::connect(backButton_2, SIGNAL(pressed()), this, SLOT(on_backButton_2_pressed()));
    backButton_2->setFixedSize(400,200);

    histogramEnhance = new QPushButton("hist enhance", this);
    QObject::connect(histogramEnhance, SIGNAL(pressed()), this, SLOT(on_histogramEnhance_pressed()));
    histogramEnhance->setFixedSize(400,200);

    grayScale = new QPushButton("Gray Scale", this);
    QObject::connect(grayScale, SIGNAL(pressed()), this, SLOT(on_grayScale_pressed()));
    grayScale->setFixedSize(400,200);

    brightnessEnhance = new QPushButton("brightness enhance", this);
    QObject::connect(brightnessEnhance, SIGNAL(pressed()), this, SLOT(on_brightnessEnhance_pressed()));
    brightnessEnhance->setFixedSize(400,200);

    colorBalance = new QPushButton("color balance", this);
    QObject::connect(colorBalance, SIGNAL(pressed()), this, SLOT(on_colorBalance_pressed()));
    colorBalance->setFixedSize(400,200);

    QHBoxLayout *enhancementsPageLayout = new QHBoxLayout;
    enhancementsPageLayout->addWidget(backButton_2);
    enhancementsPageLayout->addWidget(histogramEnhance);
    enhancementsPageLayout->addWidget(grayScale);
    enhancementsPageLayout->addWidget(brightnessEnhance);
    enhancementsPageLayout->addWidget(colorBalance);

    widget2->setLayout(enhancementsPageLayout);

    scrollArea->setWidget(widget2);

    scroller = QScroller::scroller(scrollArea);

    QScrollerProperties prop = scroller->scrollerProperties();

    prop.setScrollMetric(QScrollerProperties::AxisLockThreshold, 0.66);
    prop.setScrollMetric(QScrollerProperties::ScrollingCurve, QEasingCurve(QEasingCurve::OutExpo));
    prop.setScrollMetric(QScrollerProperties::DecelerationFactor, 0.05);
    prop.setScrollMetric(QScrollerProperties::MaximumVelocity, 0.635);
    prop.setScrollMetric(QScrollerProperties::OvershootDragResistanceFactor, 0.33);
    prop.setScrollMetric(QScrollerProperties::OvershootScrollDistanceFactor, 0.33);
    prop.setScrollMetric(QScrollerProperties::SnapPositionRatio, 0.93);
    prop.setScrollMetric(QScrollerProperties::DragStartDistance, 0.001);
    //scroller->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

    scroller->setScrollerProperties(prop);
    scroller->grabGesture(scrollArea, QScroller::TouchGesture);

    QHBoxLayout *enhancementsPageLayout_final = new QHBoxLayout;
    enhancementsPageLayout_final->addWidget(scrollArea);

    widget2_final->setLayout(enhancementsPageLayout_final);

    return widget2_final;

}

QWidget* MainWindow::setupFiltersPageWidget()
{
    QWidget *widget3 = new QWidget(this);
    QWidget *widget3_final = new QWidget(this);

    QScrollArea *filterScrollArea = new QScrollArea(this);
    filterScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    filterScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    backButton_3 = new QPushButton("Back", this);
    QObject::connect(backButton_3, SIGNAL(pressed()), this, SLOT(on_backButton_3_pressed()));
    backButton_3->setFixedSize(400,200);

    sepiaFilter = new QPushButton("Sepia", this);
    QObject::connect(sepiaFilter, SIGNAL(pressed()), this, SLOT(on_sepiaFilter_pressed()));
    sepiaFilter->setFixedSize(400,200);

    pencilSketch = new QPushButton("Sketch", this);
    QObject::connect(pencilSketch, SIGNAL(pressed()), this, SLOT(on_pencilSketch_pressed()));
    pencilSketch->setFixedSize(400,200);

    edgeDetect = new QPushButton("Edge Detect", this);
    QObject::connect(edgeDetect, SIGNAL(pressed()), this, SLOT(on_edgeDetect_pressed()));
    edgeDetect->setFixedSize(400,200);

    imageSegment = new QPushButton("Segmentation", this);
    QObject::connect(imageSegment, SIGNAL(pressed()), this, SLOT(on_imageSegment_pressed()));
    imageSegment->setFixedSize(400,200);

    sepiaFilter->setFixedSize(400,200);

    QHBoxLayout *filtersPageLayout = new QHBoxLayout;
    filtersPageLayout->addWidget(backButton_3);
    filtersPageLayout->addWidget(sepiaFilter);
    filtersPageLayout->addWidget(pencilSketch);
    filtersPageLayout->addWidget(edgeDetect);
    filtersPageLayout->addWidget(imageSegment);

    widget3->setLayout(filtersPageLayout);

    filterScrollArea->setWidget(widget3);

    filterScroller = QScroller::scroller(filterScrollArea);

    QScrollerProperties prop = filterScroller->scrollerProperties();

    prop.setScrollMetric(QScrollerProperties::AxisLockThreshold, 0.66);
    prop.setScrollMetric(QScrollerProperties::ScrollingCurve, QEasingCurve(QEasingCurve::OutExpo));
    prop.setScrollMetric(QScrollerProperties::DecelerationFactor, 0.05);
    prop.setScrollMetric(QScrollerProperties::MaximumVelocity, 0.635);
    prop.setScrollMetric(QScrollerProperties::OvershootDragResistanceFactor, 0.33);
    prop.setScrollMetric(QScrollerProperties::OvershootScrollDistanceFactor, 0.33);
    prop.setScrollMetric(QScrollerProperties::SnapPositionRatio, 0.93);
    prop.setScrollMetric(QScrollerProperties::DragStartDistance, 0.001);
    //scroller->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

    filterScroller->setScrollerProperties(prop);
    filterScroller->grabGesture(filterScrollArea, QScroller::TouchGesture);

    QHBoxLayout *filtersPageLayout_final = new QHBoxLayout;
    filtersPageLayout_final->addWidget(filterScrollArea);

    widget3_final->setLayout(filtersPageLayout_final);

    return widget3_final;
}

QImage MainWindow::loadImage()
{
    qDebug()<<"function called";

    selectedFileName = "#";
    QAndroidJniObject::callStaticMethod<void>("com/amin/QtAndroidGallery/QtAndroidGallery",
                                              "openAnImage",
                                              "()V");

    qDebug()<<"Function called";

    while(selectedFileName == "#")
        qApp->processEvents();

    if(QFile(selectedFileName).exists())
    {
        openedImage = imread(selectedFileName.toStdString());
        qDebug()<<openedImage.channels();
        //cv::resize(openedImage, openedImage, Size(512, 384), 0, 0, INTER_LINEAR);
        cv::cvtColor(openedImage,image,CV_BGR2RGB);               //QT reads in RGB while CV reads in BGR
    }
    QImage displayImage((uchar*)image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
    qDebug()<<"going back to mainwindow";
    return displayImage;
}

QImage MainWindow::histogramEqualize()
{
    qDebug()<<"histogram equalize called";
    qDebug()<<"NO. of channels:"<<openedImage.channels();

    cvtColor(openedImage,result,CV_BGR2YCrCb);

    split(result,channels);

    equalizeHist(channels[0], channels[0]);

    merge(channels,result);

    cvtColor(result,result,CV_YCrCb2BGR);
    qDebug()<<"process completed";

    cvtColor(result,result,CV_BGR2RGB);
    QImage enhancedImage((uchar*)result.data, result.cols, result.rows, result.step, QImage::Format_RGB888);
    qDebug()<<"going back";
    return enhancedImage;
}

QImage MainWindow::convertToGray()
{
    cvtColor(openedImage, grayImage, CV_BGR2GRAY);

    static QVector<QRgb> sColorTable;
    // only create our color table once
    if ( sColorTable.isEmpty() )
    {
        for ( int i = 0; i < 256; ++i )
            sColorTable.push_back( qRgb( i, i, i ) );
    }

    QImage qGrayImage((uchar*)grayImage.data, grayImage.cols, grayImage.rows, grayImage.step, QImage::Format_Indexed8 );
    qGrayImage.setColorTable( sColorTable );

    return qGrayImage;
}

QImage MainWindow::colorBalanceFunction()
{
    percent = 50;
    assert(openedImage.channels() == 3);
    assert(percent > 0 && percent < 100);

    float half_percent = percent / 200.0f;

    split(openedImage,tmpsplit);
    for(int i=0;i<3;i++) {
        //find the low and high precentile values (based on the input percentile)
        Mat flat;
        tmpsplit[i].reshape(1,1).copyTo(flat);
        cv::sort(flat,flat,CV_SORT_EVERY_ROW + CV_SORT_ASCENDING);
        int lowval = flat.at<uchar>(cvFloor(((float)flat.cols) * half_percent));
        int highval = flat.at<uchar>(cvCeil(((float)flat.cols) * (1.0 - half_percent)));
        //cout << lowval << " " << highval << endl;

        //saturate below the low percentile and above the high percentile
        tmpsplit[i].setTo(lowval,tmpsplit[i] < lowval);
        tmpsplit[i].setTo(highval,tmpsplit[i] > highval);

        //scale the channel
        normalize(tmpsplit[i],tmpsplit[i],0,255,NORM_MINMAX);
    }
    merge(tmpsplit,out);
    cvtColor(out,out,CV_BGR2RGB);
    QImage balancedImage((uchar*)out.data, out.cols, out.rows, out.step, QImage::Format_RGB888);
    return balancedImage;
}

void MainWindow::on_histogramEnhance_pressed()
{
    labelStack->setCurrentIndex(1);
    displayImage_1 = histogramEqualize();
    qDebug()<<"Image returned";
    label_2->setPixmap(QPixmap::fromImage(displayImage_1));
    qDebug()<<"image set";
}

void MainWindow::on_backButton_1_pressed()
{
    stack->setCurrentIndex(0);
}

void MainWindow::on_toolsButton_pressed()
{
    //label->clear();
}

void MainWindow::on_enhancementsButton_pressed()
{
    stack->setCurrentIndex(2);
}

void MainWindow::on_filtersButton_pressed()
{
    stack->setCurrentIndex(3);
}

void MainWindow::on_backButton_2_pressed()
{
    stack->setCurrentIndex(1);
}

void MainWindow::on_grayScale_pressed()
{
    displayImage_2 = convertToGray();
    qDebug()<<"Image returned";
    label_3->setPixmap(QPixmap::fromImage(displayImage_2));
    labelStack->setCurrentIndex(2);
    qDebug()<<"image set";
}

void MainWindow::on_brightnessEnhance_pressed()
{

}

void MainWindow::on_colorBalance_pressed()
{
    qDebug()<<"color balance pressed";
    displayImage_3 = colorBalanceFunction();
    qDebug()<<"Image Returned";
    label_4->setPixmap(QPixmap::fromImage(displayImage_3));
    labelStack->setCurrentIndex(3);
    qDebug()<<"Image set";
}

void MainWindow::on_backButton_3_pressed()
{
    stack->setCurrentIndex(1);
}

void MainWindow::on_sepiaFilter_pressed()
{
    Mat_<float> sepia(3,3);

    sepia << .131,.534,.272    // bgr (rows as well as cols swapped)
            ,.168,.686,.349
            ,.189,.769,.393;

    cv::transform(openedImage,sepiaImage,sepia);
    cvtColor(sepiaImage,sepiaImage,CV_BGR2RGB);
    QImage outputSepiaImage((uchar*)sepiaImage.data, sepiaImage.cols, sepiaImage.rows, sepiaImage.step, QImage::Format_RGB888);
    label_4->setPixmap(QPixmap::fromImage(outputSepiaImage));
    labelStack->setCurrentIndex(3);
    qDebug()<<"Image Set";

}

void MainWindow::on_pencilSketch_pressed()
{
    double alpha = 0.9; double beta;

    Mat pencilGrayImage;
    Mat invertImage;
    Mat dst;
    Mat blurImage;
    Mat finalImage;
    cvtColor(openedImage,pencilGrayImage,CV_BGR2GRAY);
    bitwise_not(pencilGrayImage,invertImage);

    beta = ( 1.0 - alpha );
    addWeighted( invertImage, alpha, invertImage, beta, 0.0, dst);

    GaussianBlur(dst,blurImage,Size(9,9),0,0);
    cvtColor(blurImage,blurImage,CV_GRAY2BGR);

    addWeighted(openedImage, 0.7, blurImage, 0.3, 0.0, finalImage);

    QImage pencilImage((uchar*)finalImage.data, finalImage.cols, finalImage.rows, finalImage.step, QImage::Format_RGB888);
    label_4->setPixmap(QPixmap::fromImage(pencilImage));
    labelStack->setCurrentIndex(3);
    qDebug()<<"image set";
}

void MainWindow::on_edgeDetect_pressed()
{
    Mat edgeGray;
    Mat edge;
    cvtColor(openedImage, edgeGray, CV_BGR2GRAY);
    Canny(edgeGray, edge, 50, 150, 3);

    QImage edgeImage((uchar*)edge.data, edge.cols, edge.rows, edge.step, QImage::Format_Indexed8);
    label_4->setPixmap(QPixmap::fromImage(edgeImage));
    labelStack->setCurrentIndex(3);
    qDebug()<<"image set";
}

void MainWindow::on_imageSegment_pressed()
{
    // Change the background from white to black, since that will help later to extract
    // better results during the use of Distance Transform
    for( int a = 0; a < openedImage.rows; a++ ) {
      for( int b = 0; b < openedImage.cols; b++ ) {
          if ( openedImage.at<Vec3b>(a, b) == Vec3b(255,255,255) ) {
            openedImage.at<Vec3b>(a, b)[0] = 0;
            openedImage.at<Vec3b>(a, b)[1] = 0;
            openedImage.at<Vec3b>(a, b)[2] = 0;
          }
        }
    }
    // Create a kernel that we will use for accuting/sharpening our image
    Mat kernel = (Mat_<float>(3,3) <<
            1,  1, 1,
            1, -8, 1,
            1,  1, 1); // an approximation of second derivative, a quite strong kernel

    // do the laplacian filtering as it is
    // well, we need to convert everything in something more deeper then CV_8U
    // because the kernel has some negative values,
    // and we can expect in general to have a Laplacian image with negative values
    // BUT a 8bits unsigned int (the one we are working with) can contain values from 0 to 255
    // so the possible negative number will be truncated
    Mat imgLaplacian;
    Mat sharp = openedImage; // copy source image to another temporary one
    filter2D(sharp, imgLaplacian, CV_32F, kernel);
    sharp.convertTo(sharp, CV_32F);
    Mat imgResult = sharp - imgLaplacian;

    // convert back to 8bits gray scale
    imgResult.convertTo(imgResult, CV_8UC3);
    imgLaplacian.convertTo(imgLaplacian, CV_8UC3);

    // Create binary image from source image
    Mat bw;
    cvtColor(openedImage, bw, CV_BGR2GRAY);
    threshold(bw, bw, 40, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

    // Perform the distance transform algorithm
    Mat dist;
    distanceTransform(bw, dist, CV_DIST_L2, 3);

    // Normalize the distance image for range = {0.0, 1.0}
    // so we can visualize and threshold it
    normalize(dist, dist, 0, 1., NORM_MINMAX);
    // Threshold to obtain the peaks
    // This will be the markers for the foreground objects
    threshold(dist, dist, .4, 1., CV_THRESH_BINARY);

    // Dilate a bit the dist image
    Mat kernel1 = Mat::ones(3, 3, CV_8UC1);
    dilate(dist, dist, kernel1);

    // Create the CV_8U version of the distance image
    // It is needed for findContours()
    Mat dist_8u;
    dist.convertTo(dist_8u, CV_8U);

    // Find total markers
    vector<vector<Point> > contours;
    findContours(dist_8u, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    // Create the marker image for the watershed algorithm
    Mat markers = Mat::zeros(dist.size(), CV_32SC1);

    // Draw the foreground markers
    for (size_t i = 0; i < contours.size(); i++)
        drawContours(markers, contours, static_cast<int>(i), Scalar::all(static_cast<int>(i)+1), -1);

    // Draw the background marker
    circle(markers, Point(5,5), 3, CV_RGB(255,255,255), -1);

    // Perform the watershed algorithm
    watershed(openedImage, markers);

    Mat mark = Mat::zeros(markers.size(), CV_8UC1);
    markers.convertTo(mark, CV_8UC1);
    bitwise_not(mark, mark);

    // Generate random colors
    vector<Vec3b> colors;
    for (size_t i = 0; i < contours.size(); i++)
    {
        int b = theRNG().uniform(0, 255);
        int g = theRNG().uniform(0, 255);
        int r = theRNG().uniform(0, 255);
        colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
    }
    // Create the result image
    Mat dst = Mat::zeros(markers.size(), CV_8UC3);
    // Fill labeled objects with random colors
    for (int i = 0; i < markers.rows; i++)
    {
        for (int j = 0; j < markers.cols; j++)
        {
            int index = markers.at<int>(i,j);
            if (index > 0 && index <= static_cast<int>(contours.size()))
                dst.at<Vec3b>(i,j) = colors[index-1];
            else
                dst.at<Vec3b>(i,j) = Vec3b(0,0,0);
        }
    }

    QImage segementedImage((uchar*)dst.data, dst.rows, dst.cols, dst.step, QImage::Format_RGB888);
    label_4->setPixmap(QPixmap::fromImage(segementedImage));
    labelStack->setCurrentIndex(3);
}

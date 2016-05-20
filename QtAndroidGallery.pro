#-------------------------------------------------
#
# http://www.amin-ahmadi.com
#
#-------------------------------------------------

QT += core gui androidextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtAndroidGallery
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

INCLUDEPATH += "$$_PRO_FILE_PWD_/OpenCV-android-sdk/sdk/native/jni/include"
android {
    LIBS += \
        -L"$$_PRO_FILE_PWD_/OpenCV-android-sdk/sdk/native/3rdparty/libs/armeabi-v7a"\
        -L"$$_PRO_FILE_PWD_/OpenCV-android-sdk/sdk/native/libs/armeabi-v7a"\
        -llibtiff\
        -llibjpeg\
        -llibjasper\
        -llibpng\
        -lIlmImf\
        -ltbb\
        -lopencv_core\
        -lopencv_androidcamera\
        -lopencv_flann\
        -lopencv_imgproc\
        -lopencv_highgui\
        -lopencv_features2d\
        -lopencv_calib3d\
        -lopencv_ml\
        -lopencv_objdetect\
        -lopencv_video\
        -lopencv_contrib\
        -lopencv_photo\
        -lopencv_java\
        -lopencv_legacy\
        -lopencv_ocl\
        -lopencv_stitching\
        -lopencv_superres\
        -lopencv_ts\
        -lopencv_videostab

    ANDROID_PACKAGE_SOURCE_DIR=$$_PRO_FILE_PWD_/android-sources
}

HEADERS  += mainwindow.h \
    mainsetup.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

DISTFILES += \
    android-sources/AndroidManifest.xml \
    android-sources/src/com/amin/QtAndroidGallery/QtAndroidGallery.java

#ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources

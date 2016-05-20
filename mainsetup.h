#ifndef MAINSETUP
#define MAINSETUP

#include <QSize>
#include <QObject>
#include <QScreen>
#include <QGuiApplication>

class MainSetup : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QSize size READ size)
public:
    QSize size()
    {
        QSize size = qApp->screens()[0]->size();
        return size;
    }
};

#endif // MAINSETUP

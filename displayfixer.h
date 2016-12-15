#ifndef DISPLAYFIXER_H
#define DISPLAYFIXER_H
#include <windows.h>
#include <WinUser.h>

#include <QObject>

class DisplayFixer : public QObject
{
    Q_OBJECT
public:
    explicit DisplayFixer(QObject *parent = 0);

signals:

public slots:
    void fixit();
private:
    wchar_t *getMonitor();
};

#endif // DISPLAYFIXER_H

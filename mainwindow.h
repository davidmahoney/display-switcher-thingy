#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <memory>
#include <nativeeventfilter.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void quit_action(bool);

private:
    std::unique_ptr<QSystemTrayIcon> m_trayIcon;
    std::unique_ptr<QMenu> m_menu;
    void registerHotKey();
    std::unique_ptr<NativeEventFilter> m_nef;
    unsigned short m_hotkeyId;
};

#endif // MAINWINDOW_H

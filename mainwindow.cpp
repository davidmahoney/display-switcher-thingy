#include "mainwindow.h"
#include <QSystemTrayIcon>
#include <QMenu>
#include <memory>
#include <QDebug>
#include <QApplication>
#include "displayfixer.h"
#include "nativeeventfilter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_trayIcon = std::unique_ptr<QSystemTrayIcon>(new QSystemTrayIcon());
    QMenu *menu = new QMenu(this);
    DisplayFixer *fixer = new DisplayFixer;
    menu->setTitle("Display Switcher Thingy");
    auto fix = menu->addAction("Fix Display");
    auto quit = menu->addAction("Quit");
    connect(quit, &QAction::triggered, this, &MainWindow::quit_action);
    connect(fix, &QAction::triggered, [=] (bool) { fixer->fixit(); });
    registerHotKey();
    connect(m_nef.get(), &NativeEventFilter::hotkeyReceived, [=] () { fixer->fixit(); });
    m_trayIcon->setIcon(QIcon(":/icon/icon.svg"));
    m_trayIcon->setContextMenu(menu);
    m_trayIcon->show();
}

void MainWindow::registerHotKey()
{
    wchar_t appName[24] = L"display_switcher_thingy";
    m_hotkeyId = GlobalAddAtom(appName);
    if (m_hotkeyId == 0)
        qDebug() << "Failed to get hotkey ID";
    if (RegisterHotKey(NULL, m_hotkeyId, MOD_ALT | MOD_SHIFT | MOD_NOREPEAT, 0x44))
        qDebug() << "Registered hotkey mod-shift-d";
    m_nef = std::make_unique<NativeEventFilter>();
}

MainWindow::~MainWindow()
{
    UnregisterHotKey(NULL, m_hotkeyId);
    GlobalDeleteAtom(m_hotkeyId);
}

void MainWindow::quit_action(bool)
{
    qDebug() << "Quit triggered";
    QApplication::exit();
}

#include "displayfixer.h"
#include <QDebug>
#include <windows.h>
#include <winuser.h>

DisplayFixer::DisplayFixer(QObject *parent) : QObject(parent)
{

}

void DisplayFixer::fixit()
{
    bool ok = true;
    auto device = getMonitor();
    PDEVMODE mode = new DEVMODE;
    ok = EnumDisplaySettings(device, ENUM_CURRENT_SETTINGS, mode);
//    POINTL pos;
//    pos.x = 0;
//    pos.y = 0;
//    mode->dmBitsPerPel = 3
//    mode->dmPelsHeight = 1024;
//    mode->dmPelsWidth = 1280;
//    mode->dmDisplayFrequency = 60;
//    mode->dmPosition = pos;
//    mode->dmDisplayFlags = 0;
//    mode->dmSize = sizeof mode;
    auto result = ChangeDisplaySettingsEx(device, mode, NULL, CDS_RESET, NULL);
    if (result == DISP_CHANGE_BADMODE)
        qDebug() << "Bad mode";
}

// \brief Return the name of the last monitor
wchar_t *DisplayFixer::getMonitor()
{
    wchar_t *result = 0;
    PDISPLAY_DEVICE p = new DISPLAY_DEVICE;
    PDISPLAY_DEVICE p1 = new DISPLAY_DEVICE;
    QString name;
    p->cb = sizeof(*p);
    p1->cb = sizeof(*p);
    unsigned long i = 0;
    while (EnumDisplayDevices(NULL, i++, p, NULL))
    {
        qDebug() << QString("Found device ") << QString::fromWCharArray(p->DeviceString);
        unsigned long j = 0;
        while (EnumDisplayDevices(p->DeviceName, j++, p1, NULL))
        {
            result = static_cast<wchar_t*>(calloc(sizeof p1->DeviceName, sizeof(wchar_t) + 1));
            wcsncpy(result, p->DeviceName, sizeof p1->DeviceName);
            PDEVMODE mode = new DEVMODE;
            mode->dmSize = sizeof(DEVMODE);
            bool ok = EnumDisplaySettings(p->DeviceName, ENUM_CURRENT_SETTINGS, mode);
            qDebug() << "monitor: " << QString::fromWCharArray(p1->DeviceString);
        }
    }

    delete p;
    return result;
}

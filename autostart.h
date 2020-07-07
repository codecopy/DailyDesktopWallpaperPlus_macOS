#ifndef AUTOSTART_H
#define AUTOSTART_H

#include <QString>

class autostart
{
public:
    void no_autostart();
    void set_autostart();

private:
    void setup_plistFile();
    QString mainApp;
    QString mainApp_name;
    QString _file_content;

    void MainAppDef();
    void set_autostartLocation();
    void check_dir();
};

#endif // AUTOSTART_H

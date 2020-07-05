#include "autostart.h"

#include <QFile>
#include <QDir>
#include <QApplication>
#include <QTextStream>
#include <QProcess>
#include <QDebug>
#include <QtGlobal>

void autostart::setup_plistFile()
{
    mainApp = QApplication::applicationFilePath();
    mainApp_name = QApplication::applicationName();
    _file_content = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n"
            "<plist version=\"1.0\">\n"
            "<dict>\n"
                "<key>ProgramArguments</key>\n"
                "<array>\n"
                    "<string>"+mainApp+"</string>\n"
                "</array>\n"
                "<key>RunAtLoad</key>\n"
                "<true/>\n"
                "<key>Label</key>\n"
                "<string>com.yourcompany."+mainApp_name+"</string>\n"
            "</dict>\n"
            "</plist>\n";
}

void autostart::no_autostart()
{
    QString mainApp_name = QApplication::applicationName();
    QString _autostart_dir = QDir::homePath()+"/Library/LaunchAgents";
    QString _filename = "com.yourcompany."+mainApp_name+".plist";
    QFile autostart_file(_autostart_dir+"/"+_filename);
    autostart_file.remove();
}

void autostart::set_autostart()
{
    setup_plistFile();
    QString _autostart_dir = QDir::homePath()+"/Library/LaunchAgents";
    QString _filename = "com.yourcompany."+mainApp_name+".plist";

    QFile autostart_file(_autostart_dir+"/"+_filename);
    if(autostart_file.exists())
    {
        QFile _plist_file(_autostart_dir+"/"+_filename);
        _plist_file.remove();
    }

    // write .plist file
    if (autostart_file.open(QIODevice::Append))
    {
        QTextStream stream(&autostart_file);
        stream <<_file_content<<endl;
    }
}

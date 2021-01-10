#include "setwallpaper.h"

#include <QProcess>
#include <QDebug>
#include <QPixmap>
#include <QApplication>
#include <QFile>
#include <QSettings>
#include <QTextStream>
#include <QDir>

void setWallpaper::_read_settings()
{
    QString _iniFilePath = QDir::homePath()+"/.DailyDesktopWallpaperPlus/settings.ini";

    QSettings settings(_iniFilePath, QSettings::IniFormat);

    settings.beginGroup("SETTINGS");
    _WallpaperDir = settings.value("WallpaperDir","").toString();
    _OldWallpaperDir = settings.value("OldWallpaperDir","").toString();
    settings.endGroup();

    settings.beginGroup("SETWALLPAPER");
    _AutoChange = settings.value("AutoChange","").toBool();
    _Parameter = settings.value("Parameter","").toInt();
    settings.endGroup();
}

void setWallpaper::_set_wallpaper()
{
    _read_settings();

    if(_AutoChange==true)
    {
        QDir wallDir(_WallpaperDir);
        QFileInfoList WallpaperList = wallDir.entryInfoList(QStringList() << "*.jpg", QDir::Files);
        int totalfiles = WallpaperList.size();
        int minFile = 1;

        //check if a file is in the wallpaper directory to avoid a crash
        if (!(minFile > totalfiles))
        {
            _wallpaperfile = _WallpaperDir+"/"+WallpaperList[0].baseName()+".jpg";
            //check if a file is a wallpaperfile of DailyDesktopWallpaperPlus
            if(_wallpaperfile.contains("-background.jpg"))
            {
                QProcess setWallpaper;
                _create_bashfile();
                setWallpaper.execute("/bin/bash "+_scriptfile);
                _remove_bashfile();
            }

        }
    }
}

void setWallpaper::_create_bashfile()
{
    // Create a scriptfile

    _scriptfile = QDir::homePath()+"/.DailyDesktopWallpaperPlus/cw.sh";

    QFile set_wallpaper_script(_scriptfile);
    if(!set_wallpaper_script.exists(_scriptfile))
    {
        QString content = "#!/bin/bash\n"
                " \n"
                "osascript -e 'tell application \"System Events\" to tell every desktop to set picture to \""+_wallpaperfile+"\"'";

        if (set_wallpaper_script.open(QIODevice::Append))
        {
            QTextStream stream(&set_wallpaper_script);
            stream <<content<<endl;
        }
    }
}

void setWallpaper::_remove_bashfile()
{
    QFile sr(_scriptfile);
    sr.remove();
}

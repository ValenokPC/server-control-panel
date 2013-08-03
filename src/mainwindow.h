/*
    WPN-XM Server Control Panel

    WPN-XM SCP is a tool to manage Nginx, PHP and MariaDb daemons under windows.
    It's a fork of Easy WEMP originally written by Yann Le Moigne and (c) 2010.
    WPN-XM SCP is written by Jens-Andre Koch and (c) 2011 - onwards.

    This file is part of WPN-XM Serverpack for Windows.

    WPN-XM SCP is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    WPN-XM SCP is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with WPN-XM SCP. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// local includes
#include "version.h"
#include "tray.h"

// global includes
#include <QMainWindow>
#include <QAction>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT  // Enables signals and slots

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setVisible(bool visible);

    QString getPHPVersion();
    QString getNginxVersion();
    QString getMariaVersion();
    QString getMongoVersion();
    QString getMemcachedVersion();

    QString parseVersionNumber(QString stringWithVersion);

    bool bAutostartDaemons;

    // Global
    QString cfgLogsDir;

    // PHP
    QString cfgPhpDir;
#define PHPCGI_EXEC "/php-cgi.exe"
    QString cfgPhpConfig;
    QString cfgPhpFastCgiHost;
    QString cfgPhpFastCgiPort;

    // NGINX
    QString cfgNginxDir;
#define NGINX_EXEC "/nginx.exe"
    QString cfgNginxConfig;
    QString cfgNginxSites;

    // MySQL
    QString cfgMariaDBDir;
#define MARIADB_EXEC "/mysqld.exe"
#define MARIADB_CLIENT_EXEC "/mysql.exe"
    QString cfgMariaDBConfig;
    QString cfgMariaDBClientExec;

    // MongoDB
    QString cfgMongoDBDir;
#define MONGODB_EXEC "/mongod.exe"

    // Memcached
    QString cfgMemcachedDir;
#define MEMCACHED_EXEC "/memcached.exe"

    // Process Monitoring
    QProcess* processNginx;
    QProcess* processPhp;
    QProcess* processMariaDB;
    QProcess* processMongoDB;
    QProcess* processMemcached;

public slots:

    void goToWebsite();
    void goToGoogleGroup();
    void goToReportIssue();
    void goToDonate();

    void openToolPHPInfo();
    void openToolPHPMyAdmin();
    void openToolWebgrind();
    void openToolAdminer();

    void openProjectFolderInBrowser();
    void openProjectFolderInExplorer();

    void openConfigurationDialog();
    void openHelpDialog();
    void openAboutDialog();

    void openConfigurationDialogNginx();
    void openConfigurationDialogPHP();
    void openConfigurationDialogMariaDB();

    void openLogNginxAccess();
    void openLogNginxError();
    void openLogPHP();
    void openLogMariaDB();

    void setLabelStatusActive(QString label, bool enabled);
    void enableToolsPushButtons(bool enabled);

private:
    Ui::MainWindow *ui;

    QSystemTrayIcon *trayIcon;

    QAction *minimizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    void checkAlreadyActiveDaemons();
    void createActions();
    void createTrayIcon();
    void startMonitoringDaemonProcesses();

    // Returns full path to project folder (appPath + www).
    QString getProjectFolder() const;
    void showPushButtonsOnlyForInstalledTools();

    // The settings manager.
    Settings settings;

private slots:

     // when tray icon is activated
     void iconActivated(QSystemTrayIcon::ActivationReason reason);

protected:
    void closeEvent(QCloseEvent *event);
    void changeEvent(QEvent *event);

};

#endif // MAINWINDOW_H

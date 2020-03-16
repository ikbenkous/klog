#ifndef FILEMANAGER_H
#define FILEMANAGER_H

/***************************************************************************
                          filemanager.h  -  description
                             -------------------
    begin                : sept 2011
    copyright            : (C) 2011 by Jaime Robles
    email                : jaime@robles.es
 ***************************************************************************/

/*****************************************************************************
 * This file is part of KLog.                                             *
 *                                                                           *
 *    KLog is free software: you can redistribute it and/or modify        *
 *    it under the terms of the GNU General Public License as published by   *
 *    the Free Software Foundation, either version 3 of the License, or      *
 *    (at your option) any later version.                                    *
 *                                                                           *
 *    KLog is distributed in the hope that it will be useful,             *
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *    GNU General Public License for more details.                           *
 *                                                                           *
 *    You should have received a copy of the GNU General Public License      *
 *    along with KLog.  If not, see <https://www.gnu.org/licenses/>.       *
 *                                                                           *
 *****************************************************************************/

#include <QObject>
//#include <QtWidgets>

#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QSqlQuery>
#include <QStringList>
#include <QSqlRecord>
#include <QProgressDialog>
#include <QMessageBox>
#include <QDateTime>
#include "world.h"
#include "awards.h"
#include "database.h"
#include "dataproxy_sqlite.h"
#include "dataproxy_sqlite.h"
#include "utilities.h"



enum
{
    CQZones = 40,
    ITUZones = 90,
    DXCCEntities = 521 // http://www.adif.org/adif302.htm#Country%20Codes
};

class FileManager : public QWidget
{
    Q_OBJECT
public:
    FileManager(DataProxy_SQLite *dp);
    //FileManager(DataProxy_SQLite *dp, const QString _klogDir);
    FileManager(DataProxy_SQLite *dp, const QString _klogDir, const QString _softVersion);
    //FileManager(DataProxy_SQLite *dp, const QString _softVersion);
    ~FileManager();
    //bool readAdif(const QString& tfileName, const int logN);
    bool adifReadLog(const QString& tfileName, const int logN);
    bool adifLoTWReadLog(const QString& tfileName);
    QList<int> adifLoTWLogExport(const QString& _fileName,const QString &_callsign, const int _logN, bool emptyCall=false);
    bool adifLogExport(const QString& _fileName, const int _logN);
    bool adifLogExportMarked(const QString& _fileName);
    bool adifReqQSLExport(const QString& _fileName);
    bool cabrilloLogExport(const QString& _fileName, const QString &_contestType, const int logNconst);
    bool modifySetupFile(const QString& _filename, const QString &_field, const QString &_value);
    void setVersion(const QString &_version);
    QDateTime getDateTimeOfLastBackup();
    void setStationCallSign(const QString& _st);




private:    
    bool adifLogExportToFile(const QString& _fileName, const int _logN, bool justMarked, bool _qslRequested, bool _lotw);
    bool cabrilloLogExportToFile(const QString& _fileName, const int logNconst);
    bool cabrilloLogExportCQWWToFile(const QString& _fileName, const int logNconst);
    //bool adifCheckMoreThanOneLog(QFile &_f);
    int howManyLogsInFile(QFile & _f);
    bool fillHashLog(QFile & _f);
    QStringList getListOfLogsInFile(QFile & _f);
    bool writeBackupDate();

    void showError (const QString &_txt);


    //QString checkAndFixASCIIinADIF(_data);

    bool processQsoReadingADIF(const QStringList &_line, const int logNumber, const bool _keepLogsInFile);
    void queryPreparation(const int _logN);

    bool checkADIFValidFormat(const QStringList &_qs);

    QStringList readAdifField (const QString &_field);
    QString prepareStringLog();


    bool dbCreated;
    DataBase *db;
    //float softwareVersion;
    //DataProxy_SQLite *dataProxy;
    DataProxy_SQLite *dataProxy;//, *dataProxyPrepared;

    Utilities *util;    

    bool rstTXDefault, rstRXDefault; // If true and a log is not including RST, 59 is automatically added


    //bool printQs(const QString _q, const QStringList _line);
    bool printQs(const QStringList &_line);
    //int confirmed;
    QString klogDir;
    QString klogVersion;
    QString defaultStationCallsign;
    //QProgressBar *progressBar;
    bool ignoreUnknownAlways;   // When importing ADIF, ignore all unknown fields.
    bool usePreviousStationCallsignAnswerAlways;   // When importing ADIF, ignore all unknown fields.
    bool noMoreQso;

    World *world;
    Awards *awards;
    //QSqlDatabase db;

    QHash<int, int> hashLogs;  // to create different logs when importing a ADIF file

    QSqlQuery preparedQuery;

    int constrid; // Just an id for the constructor to check who is being executed at one specific time


signals:
    void queryError(QString _functionFailed, QString errorCodeS, int errorCodeN, QString failedQuery); // To alert about any failed query execution

};
#endif // FILEMANAGER_H

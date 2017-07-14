#include <QCoreApplication>
#include <QMetaEnum>
#include <QTextStream>

#include "Server/game.h"
#include "Server/deck.h"

#include <QDir>
#include <QSettings>
#include "httpserver/httplistener.h"
#include "requestmapper.h"

using namespace stefanfrings;

QString searchConfigFile()
{
    QString binDir=QCoreApplication::applicationDirPath();
    QString appName=QCoreApplication::applicationName();
    QString fileName(appName+".ini");

    QStringList searchList;
    //searchList.append(binDir);
    searchList.append(binDir+"/../../dev");
    searchList.append(binDir+"/../../branch_1");
    /*searchList.append(binDir+"/etc");
    searchList.append(binDir+"/../etc");
    searchList.append(binDir+"/../../etc"); // for development without shadow build
    searchList.append(binDir+"/../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../../../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../../../../"+appName+"/etc"); // for development with shadow build
    searchList.append(QDir::rootPath()+"etc/opt");
    searchList.append(QDir::rootPath()+"etc");*/

    foreach (QString dir, searchList)
    {
        QFile file(dir+"/"+fileName);
        if (file.exists())
        {
            // found
            fileName=QDir(file.fileName()).canonicalPath();
            qDebug("Using config file %s",qPrintable(fileName));
            return fileName;
        }
    }

    // not found
    foreach (QString dir, searchList)
    {
        qWarning("%s/%s not found",qPrintable(dir),qPrintable(fileName));
    }
    qFatal("Cannot find config file %s",qPrintable(fileName));
    return 0;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //QTextStream qcin(stdin);
    QTextStream qcout(stdout);

    qcout << "Server started" << endl;

    Deck deck;

    for (QString& card : deck.toStringList())
    {
        qcout << card << endl;
    }

    deck.shake();

    for (QString& card : deck.toStringList())
    {
        qcout << card << endl;
    }

    Game game;

    game.newRound();

    qcout.flush();



    QString configFileName=searchConfigFile();

    QSettings* listenerSettings=new QSettings(configFileName, QSettings::IniFormat, &a);
    listenerSettings->beginGroup("listener");
    new HttpListener(listenerSettings, new RequestMapper(&a), &a);

    return a.exec();
}

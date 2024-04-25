#ifndef ELFREADER_H
#define ELFREADER_H

#include <QObject>
#ifdef Q_OS_WINDOWS
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QHttpMultiPart>
#include <QEventLoop>
#include <QTimer>
#endif
#include "varreaderinterface.h"

class ElfReader : public QObject, VarReadInterfacePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.S.debuger.ElfReader" FILE "pluginElfReader.json")
    Q_INTERFACES(VarReadInterfacePlugin)

public:
    explicit ElfReader(QObject *parent = nullptr);

    QString getName() { return QString("ELF file"); }

    QString getFileExtensions() {return QString("*.elf");}

    QIODevice::OpenModeFlag allowMode() {return QIODevice::ReadOnly;}

    varloc_node_t *readTree(QString fileName);

    int saveTree(varloc_node_t* tree, QString fileName) {return -1;}
#ifdef Q_OS_WINDOWS
    QString getBackendIp() const;
    void setBackendIp(const QString &newBackendIp);
private:
    QString backendIp;
#endif

signals:

};

#endif // ELFREADER_H

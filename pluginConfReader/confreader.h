#ifndef ELFREADER_H
#define ELFREADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QHttpMultiPart>
#include <QEventLoop>
#include <QTimer>
#include "varreaderinterface.h"

class ConfReader : public QObject, VarReadInterfacePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.S.debuger.ConfReader" FILE "pluginConfReader.json")
    Q_INTERFACES(VarReadInterfacePlugin)

public:
    explicit ConfReader(QObject *parent = nullptr);

    QString getName() { return QString("ELF file"); }

    QString getFileExtensions() {return QString("*.elf");}

    QIODevice::OpenModeFlag allowMode() {return QIODevice::ReadOnly;}

    varloc_node_t *readTree(QString fileName);

    int saveTree(varloc_node_t* tree, QString fileName) {return -1;}
    QString getBackendIp() const;
    void setBackendIp(const QString &newBackendIp);
private:
    QString backendIp;
signals:

};

#endif // ELFREADER_H

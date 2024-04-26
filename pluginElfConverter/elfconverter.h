#ifndef ELFCONVERTER_H
#define ELFCONVERTER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QHttpMultiPart>
#include <QEventLoop>
#include <QMessageBox>
#include <QTimer>
#include "varreaderinterface.h"

class ElfConverter : public QObject, VarReadInterfacePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.S.debuger.ElfConverter" FILE "pluginElfConverter.json")
    Q_INTERFACES(VarReadInterfacePlugin)

public:
    explicit ElfConverter(QObject *parent = nullptr);

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

#endif // ELFCONVERTER_H

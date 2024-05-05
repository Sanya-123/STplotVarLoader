#ifndef CONFREADER_H
#define CONFREADER_H

#include <QObject>
#include "varreaderinterface.h"

class ConfReader : public QObject, VarReadInterfacePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.S.debuger.ConfReader" FILE "pluginConfReader.json")
    Q_INTERFACES(VarReadInterfacePlugin)

public:
    explicit ConfReader(QObject *parent = nullptr);

    QString getName() { return QString("conf file"); }

    QString getFileExtensions() {return QString("*.conf");}

    QIODevice::OpenModeFlag allowMode() {return QIODevice::ReadWrite;}

    varloc_node_t *readTree(QString fileName);

    int saveTree(varloc_node_t* tree, QString fileName);

    unsigned int getPriority() {return 3;}

signals:

};

#endif // CONFREADER_H

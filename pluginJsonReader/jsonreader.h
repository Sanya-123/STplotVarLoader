#ifndef JSONREADER_H
#define JSONREADER_H

#include <QObject>
#include "varreaderinterface.h"

class JsonReader : public QObject, VarReadInterfacePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.S.debuger.JsonReader" FILE "pluginJsonReader.json")
    Q_INTERFACES(VarReadInterfacePlugin)

public:
    explicit JsonReader(QObject *parent = nullptr);

    QString getName() { return QString("json file"); }

    QString getFileExtensions() {return QString("*.json");}

    QIODevice::OpenModeFlag allowMode() {return QIODevice::ReadWrite;}

    varloc_node_t *readTree(QString fileName);

    int saveTree(varloc_node_t* tree, QString fileName);

    unsigned int getPriority() {return 2;}

signals:

};

#endif // JSONREADER_H

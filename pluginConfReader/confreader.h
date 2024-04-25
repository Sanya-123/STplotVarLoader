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

    QString getName() { return QString("ELFCONF file"); }

    QString getFileExtensions() {return QString("*.elfconf");}

    QIODevice::OpenModeFlag allowMode() {return QIODevice::ReadOnly;}

    varloc_node_t *readTree(QString fileName);

    int saveTree(varloc_node_t* tree, QString fileName) {return -1;}

signals:

};

#endif // CONFREADER_H

#ifndef ELFREADER_H
#define ELFREADER_H

#include <QObject>
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

#ifdef Q_OS_WINDOWS
    QIODevice::OpenModeFlag allowMode() {return QIODevice::NotOpen;}
#else
    QIODevice::OpenModeFlag allowMode() {return QIODevice::ReadOnly;}
#endif

    varloc_node_t *readTree(QString fileName);

    int saveTree(varloc_node_t* tree, QString fileName) {return -1;}

#ifdef Q_OS_WINDOWS
    QString getInfo();
#endif

    unsigned int getPriority() {return 5;}

signals:

};

#endif // ELFREADER_H

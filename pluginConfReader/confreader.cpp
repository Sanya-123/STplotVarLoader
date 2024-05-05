#include "confreader.h"
#include "conf2var.h"

ConfReader::ConfReader(QObject *parent) : QObject(parent)
{
}

varloc_node_t *ConfReader::readTree(QString fileName)
{
    return conf2var(fileName.toLocal8Bit().data());
}

int ConfReader::saveTree(varloc_node_t *tree, QString fileName)
{
    return var2conf(tree, fileName.toLocal8Bit().data());
}

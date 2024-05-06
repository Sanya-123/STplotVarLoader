#include "jsonreader.h"
#include "json2var.h"

JsonReader::JsonReader(QObject *parent) : QObject(parent)
{
}

varloc_node_t *JsonReader::readTree(QString fileName)
{
    return json2var(fileName.toLocal8Bit().data());
}

int JsonReader::saveTree(varloc_node_t *tree, QString fileName)
{
    return var2json(tree, fileName.toLocal8Bit().data());
}

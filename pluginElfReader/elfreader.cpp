#include "elfreader.h"
#include "elf2var.h"

ElfReader::ElfReader(QObject *parent) : QObject(parent)
{
}

varloc_node_t *ElfReader::readTree(QString fileName)
{
    return varloc_open_elf(fileName.toLocal8Bit().data());
}

#include "memorymap.h"

MemoryMap::MemoryMap(QObject *parent)
    : QAbstractTableModel (parent)
{

}

int MemoryMap::rowCount(const QModelIndex &/*parent*/) const
{
    return 20;
}

int MemoryMap::columnCount(const QModelIndex &/*parent*/) const
{
    return 10;
}

QVariant MemoryMap::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return QString("Row%1, Column%2")
                .arg(index.row() + 1)
                .arg(index.column() +1);
    }
    return QVariant();
}

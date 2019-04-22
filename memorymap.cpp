#include "memorymap.h"

#include <QDebug>

MemoryMap::MemoryMap(QObject *parent)
    : QAbstractTableModel (parent)
    , m_map(200)
{
    //    m_map.reserve(200);
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
        int aux = (index.row() * 10) + index.column();

        if (aux < 200) {
            return m_map.at(aux);
        }
    }

    return QVariant();
}

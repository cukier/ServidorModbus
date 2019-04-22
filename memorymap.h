#ifndef MEMORYMAP_H
#define MEMORYMAP_H

#include <QAbstractTableModel>

class MemoryMap : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit MemoryMap(QObject *parent);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

//private:
};

#endif // MEMORYMAP_H

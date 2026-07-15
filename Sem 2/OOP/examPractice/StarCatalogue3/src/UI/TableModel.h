#pragma once

#include <QAbstractTableModel>
#include <vector>

#include "Service.h"
#include "Star.h"
using std::vector;

class TableModel: public QAbstractTableModel{
    Astronomer astronomer;
    Service& serv;

public:
    TableModel(Astronomer astronomer, Service& serv, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void updateData();
};
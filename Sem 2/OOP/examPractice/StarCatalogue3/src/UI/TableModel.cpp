#include "TableModel.h"

TableModel::TableModel(Astronomer _astronomer, Service& _serv, QObject *parent): astronomer(_astronomer), serv(_serv), QAbstractTableModel(parent){
}

int TableModel::rowCount(const QModelIndex& parent) const{
    return serv.getStars().size();
}

int TableModel::columnCount(const QModelIndex& parent) const{
    return 5;
}

QVariant TableModel::data(const QModelIndex& index, int role) const{
    if(!index.isValid() || role != Qt::DisplayRole || index.row() >= serv.getStars().size()){
        return QVariant();
    }
    switch(index.column()){
        case 0: return QString::fromStdString(serv.getStars()[index.row()].getName());
        case 1: return QString::fromStdString(serv.getStars()[index.row()].getConstellation());
        case 2: return QString::number(serv.getStars()[index.row()].getRa());
        case 3: return QString::number(serv.getStars()[index.row()].getDec());
        case 4: return QString::number(serv.getStars()[index.row()].getDiam());
    }
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(role != Qt::DisplayRole || orientation != Qt::Horizontal){
        return QVariant();
    }
    switch(section){
        case 0: return QString("Name");
        case 1: return QString("Constellation");
        case 2: return QString("RA");
        case 3: return QString("Dec");
        case 4: return QString("Diameter");
    }

    return QVariant{};
}

void TableModel::updateData(){
    beginResetModel();
    endResetModel();
}
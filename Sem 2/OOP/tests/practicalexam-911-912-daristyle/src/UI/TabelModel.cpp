#include "TabelModel.h"

TabelModel::TabelModel(Service& _serv, QObject *parent): serv(_serv), QAbstractTableModel(parent){

}

int TabelModel::rowCount(const QModelIndex &parent) const{
    return serv.getIdeas().size();
}

int TabelModel::columnCount(const QModelIndex &parent) const{
    return 5;
}

QVariant TabelModel::data(const QModelIndex& index, int role) const{
    if(!index.isValid() || index.row() >= serv.getIdeas().size() || role != Qt::DisplayRole) return QVariant();
    switch(index.column()){
        case 0: return QString::fromStdString(serv.getIdeas()[index.row()].getTitle());
        case 1: return QString::fromStdString(serv.getIdeas()[index.row()].getStatus());
        case 2: return QString::fromStdString(serv.getIdeas()[index.row()].getCreator());
        case 3: return QString::number(serv.getIdeas()[index.row()].getDuration());
        default: return QVariant();
    }
}

QVariant TabelModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(role != Qt::DisplayRole || orientation != Qt::Orientation::Horizontal) return QVariant();
    switch(section){
        case 0: return "Title";
        case 1: return "Status";
        case 2: return "Creator";
        case 3: return "Duration";
        default: return QVariant();
    }
}

Qt::ItemFlags TabelModel::flags(const QModelIndex& index) const{
    return QAbstractTableModel::flags(index) | Qt::ItemIsSelectable;
}

void TabelModel::addIdea(string title, string description, string status, string creator, int duration){
    serv.addIdea(title, description, status, creator, duration);
    beginResetModel();
    endResetModel();
    emit dataChanged(createIndex(0, 0), createIndex(serv.getIdeas().size() - 1, 4));
}

void TabelModel::acceptIdea(const QModelIndex &index){
    string title = serv.getIdeas()[index.row()].getTitle();
    string creator = serv.getIdeas()[index.row()].getCreator();
    int duration = serv.getIdeas()[index.row()].getDuration();
    serv.acceptIdea(title, creator, duration);
    beginResetModel();
    endResetModel();
    emit dataChanged(createIndex(0, 0), createIndex(serv.getIdeas().size() - 1, 4));
}

bool TabelModel::hasAcceptedIdeas(Researcher researcher){
    return this->serv.hasAcceptedIdeas(researcher);
}

vector<Idea> TabelModel::getIdeas(){
    return this->serv.getIdeas();
}

void TabelModel::saveAll(){
    this->serv.saveAll();
}

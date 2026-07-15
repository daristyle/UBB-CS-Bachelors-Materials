//
// Created by bejan on 5/23/26.
//

#include "TutorialTabelModel.h"

#include <qdatetime.h>

TutorialTabelModel::TutorialTabelModel(std::vector<Tutorial> _tutorials, QObject* parent): tutorials(_tutorials), QAbstractTableModel(parent){
}

int TutorialTabelModel::rowCount(const QModelIndex& parent) const{
    return tutorials.size();
}

int TutorialTabelModel::columnCount(const QModelIndex& parent) const{
    return 5;
}

QVariant TutorialTabelModel::data(const QModelIndex& index, int role) const{
    if(!index.isValid() || index.row() >= tutorials.size()){
        return QVariant{};
    }

    if(role == Qt::DisplayRole){
        switch(index.column()){
            case 0: return QString::fromStdString(tutorials[index.row()].get_title());
            case 1: return QString::fromStdString(tutorials[index.row()].get_presenter());
            case 2: return QTime{0, tutorials[index.row()].get_duration().get_minutes(), tutorials[index.row()].get_duration().get_seconds()}.toString("mm:ss");
            case 3: return QString::number(tutorials[index.row()].get_likes());
            case 4: return QString::fromStdString(tutorials[index.row()].get_url());
            default: return QVariant{};
        }
    }

    return QVariant{};
}

QVariant TutorialTabelModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole){
        switch(section){
            case 0: return "Title";
            case 1: return "Presenter";
            case 2: return "Duration";
            case 3: return "Likes";
            case 4: return "URL";
            default: return QVariant{};
        }
    }
    return QVariant{};
}

void TutorialTabelModel::updateData(const std::vector<Tutorial>& _tutorials){
    beginResetModel();
    tutorials = _tutorials;
    endResetModel();
}

Tutorial TutorialTabelModel::at(int index) const{
    if(index < 0 || index >= tutorials.size()){
        return Tutorial{};
    }
    return tutorials[index];
}
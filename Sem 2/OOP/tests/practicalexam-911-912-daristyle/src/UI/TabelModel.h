#pragma once

#include <QAbstractTableModel>
#include "src/Service/Service.h"

class TabelModel:public QAbstractTableModel{
private:
    Service& serv;

public:
    TabelModel(Service& serv, QObject* parent = nullptr);
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void addIdea(string title, string description, string status, string creator, int duration);
    void acceptIdea(const QModelIndex &index);
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool hasAcceptedIdeas(Researcher researcher);
    vector<Idea> getIdeas();
    void saveAll();
};
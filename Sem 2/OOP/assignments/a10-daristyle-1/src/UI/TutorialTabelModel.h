#pragma once

#include "Tutorial.h"

#include <QAbstractTableModel>


class TutorialTabelModel: public QAbstractTableModel{
    Q_OBJECT
private:
    std::vector<Tutorial> tutorials;

public:
    TutorialTabelModel(std::vector<Tutorial> _tutorials, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void updateData(const std::vector<Tutorial>& tutorials);

    Tutorial at(int index) const;
};

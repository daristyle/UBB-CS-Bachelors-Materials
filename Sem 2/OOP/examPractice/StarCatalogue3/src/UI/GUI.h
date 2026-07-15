#pragma once

#include <QWidget>

#include "Service.h"
#include "TableModel.h"


QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QWidget {
Q_OBJECT

private:
    Astronomer astronomer;
    Service& serv;
    TableModel* tableModel;

public:
    explicit GUI(Astronomer astronomer, Service& service,QWidget *parent = nullptr);
    ~GUI() override;

private:
    Ui::GUI *ui;
};
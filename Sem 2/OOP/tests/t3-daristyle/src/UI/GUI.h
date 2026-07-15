#pragma once

#include "../Service/Service.h"

#include <QWidget>


class QListWidget;
QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QWidget {
Q_OBJECT

private:
    Ui::GUI *ui;
    Service& serv;

    void populateList(QListWidget* list, vector<Flight> flights);
    void connectSignals();

public:
    explicit GUI(Service& serv, QWidget *parent = nullptr);
    ~GUI() override;
};

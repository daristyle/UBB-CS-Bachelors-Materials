#pragma once

#include <QWidget>
#include "../Service/Service.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QWidget {
Q_OBJECT

private:
    Ui::GUI *ui;
    Service& serv;

    void populateList();
public:
    explicit GUI(Service& serv , QWidget *parent = nullptr);
    ~GUI() override;
};
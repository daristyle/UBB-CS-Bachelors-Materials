#include "GUI.h"
#include "ui_GUI.h"
#include <QWidget>


GUI::GUI(Astronomer _astronomer, Service& _serv,QWidget *parent) :
    astronomer(_astronomer), serv(_serv), QWidget(parent), ui(new Ui::GUI) {
    ui->setupUi(this);
    this->tableModel = new TableModel(astronomer, serv, this);
    this->ui->starsTableView->setModel(tableModel);
    this->setWindowTitle(QString::fromStdString(astronomer.getName()));
}

GUI::~GUI() {
    delete ui;
}

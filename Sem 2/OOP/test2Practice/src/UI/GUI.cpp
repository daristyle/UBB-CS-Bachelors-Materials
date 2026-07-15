//
// Created by bejan on 5/27/26.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GUI.h" resolved

#include "GUI.h"

#include <iostream>

#include "ui_GUI.h"


GUI::GUI(Service& _serv, QWidget *parent):
    QWidget(parent), ui(new Ui::GUI), serv{_serv} {
    ui->setupUi(this);
    this->ui->paidBox->setCheckState(Qt::Checked);
    this->ui->unpaidBox->setCheckState(Qt::Checked);
    connect(this->ui->paidBox, &QCheckBox::checkStateChanged, this, [this](){populateList();});
    connect(this->ui->unpaidBox, &QCheckBox::checkStateChanged, this, [this](){populateList();});
    connect(this->ui->calculateButton, &QPushButton::clicked, this, [this](){
        try{
            string company = this->ui->companyInput->text().trimmed().toStdString();
            double amount = serv.totalUnpaid(company);
            this->ui->label->setText(QString::number(amount));
        }catch(const std::exception& e){
            this->ui->label->setText("Error: " + QString::fromStdString(e.what()));
        }
    });
    connect(this->ui->exitButton, &QPushButton::clicked, this, [this](){qApp->quit();});
    populateList();
}

GUI::~GUI() {
    delete ui;
}

void GUI::populateList(){
    this->ui->listWidget->clear();
    bool paid = this->ui->paidBox->checkState() == Qt::Checked;
    bool unpaid = this->ui->unpaidBox->checkState() == Qt::Checked;
    int i = 1;
    for(const auto& bill : serv.getBillsSorted()){
        if((bill.isPaid() && !paid) || (!bill.isPaid() && !unpaid)) continue;
        this->ui->listWidget->addItem(QString::number(i) + ". " + QString::fromStdString(bill.getCompany()) + " " + QString::number(bill.getAmount()));
        this->ui->listWidget->item(i - 1)->setBackground(QBrush(bill.isPaid() ? Qt::green : Qt::red));
        ++i;
    }
}
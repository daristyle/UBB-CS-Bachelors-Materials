//
// Created by bejan on 6/19/26.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DeveloperGUI.h" resolved

#include "DeveloperGUI.h"
#include "DeveloperGUI.h"

#include <iostream>

#include "ui_DeveloperGUI.h"


DeveloperGUI::DeveloperGUI(Idea _idea, QWidget *parent) :
    idea(_idea),QWidget(parent), ui(new Ui::DeveloperGUI) {
    ui->setupUi(this);
    ui->titleLable->setText(QString::fromStdString(idea.getTitle()));
    ui->durationLable->setText(QString::number(idea.getDuration()) + " years");
    ui->lineEdit->setText(QString::fromStdString(idea.getDescription()));
    connect(ui->savePushButton, &QPushButton::clicked, this, [this]{
        idea.setDescription(ui->lineEdit->text().trimmed().toStdString());
        idea.save();
        close();
    });
}

DeveloperGUI::~DeveloperGUI() {
    delete ui;
}

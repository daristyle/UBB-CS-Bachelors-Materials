//
// Created by bejan on 6/19/26.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GUI.h" resolved

#include "GUI.h"

#include <iostream>

#include "ui_GUI.h"
#include <QMessageBox>
#include <unistd.h>

#include "DeveloperGUI.h"

GUI::GUI(TabelModel* _tabelModel, Researcher _researcher, QWidget *parent) :
    tabelModel(_tabelModel), researcher(_researcher), QWidget(parent), ui(new Ui::GUI) {
    this->ui->setupUi(this);
    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    this->ui->tableView->setModel(this->tabelModel);
    this->setWindowTitle(QString::fromStdString(this->researcher.getName()));
    if(researcher.getPosition() != "senior"){
        this->ui->acceptPushButton->hide();
        this->ui->saveAllPushButton->hide();
    }
    developButtonUpdate();
    connectButtons();
}

void GUI::connectButtons(){
    connect(this->ui->addPushButton, &QPushButton::clicked, [this](){
        try{
            string title = this->ui->titleLineEdit->text().trimmed().toStdString();
            string description = this->ui->descriptionLineEdit->text().trimmed().toStdString();
            string durationStr = this->ui->durationLineEdit->text().trimmed().toStdString();
            int duration = std::stoi(durationStr);
            this->tabelModel->addIdea(title, description, "proposed", this->researcher.getName(), duration);
        }catch(std::exception& e){
            string error = e.what();
            if(error == "stoi"){
                error = "Duration must be a number";
            }
            QMessageBox::warning(this, "Error", QString::fromStdString(error));
        }
    });

    connect(this->ui->acceptPushButton, &QPushButton::clicked, [this]{
        if(this->researcher.getPosition() != "senior") return;
        auto selectedIndexes = this->ui->tableView->selectionModel()->selectedIndexes();
        if(selectedIndexes.empty()) return;
        this->tabelModel->acceptIdea(selectedIndexes[0]);
    });

    connect(this->tabelModel, &QAbstractTableModel::dataChanged, this, &GUI::developButtonUpdate);

    connect(this->ui->developPushButton, &QPushButton::clicked, this, [this]{
        for(const auto& idea: this->tabelModel->getIdeas()){
            if(idea.getCreator() == this->researcher.getName() && idea.getStatus() == "accepted"){
                auto newWindow = new DeveloperGUI(idea);
                newWindow->show();
            }
        }
    });
    connect(this->ui->saveAllPushButton, &QPushButton::clicked, this, [this]{
        this->tabelModel->saveAll();
    });
}

void GUI::developButtonUpdate(){
    if(this->tabelModel->hasAcceptedIdeas(this->researcher)){
        this->ui->developPushButton->show();
    }else{
        this->ui->developPushButton->hide();
    }
}

GUI::~GUI() {
    delete ui;
}

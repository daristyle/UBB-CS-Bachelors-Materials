#include "GUI.h"

#include "ui_GUI.h"

#include <QMessageBox>
#include <iostream>

GUI::GUI(Service& _serv, QWidget *parent) :
    QWidget(parent), ui(new Ui::GUI), serv(_serv) {
    ui->setupUi(this);
    this->ui->filterLineEdit->setPlaceholderText("Filter by delay");
    this->ui->destinationLineEdit->setPlaceholderText("Destination");
    this->ui->timeLineEdit->setPlaceholderText("Time");
    this->ui->label->setText("Total delay");
    connectSignals();
    populateList(this->ui->mainListWidget, serv.getFlightsSorted());
}

void GUI::populateList(QListWidget* list, vector<Flight> flights){
    list->clear();
    int i = 1;
    for(const auto& flight: flights){
        list->addItem(QString::fromStdString(std::to_string(i) + ". " + std::to_string(flight.getHour()) + ":" +
            std::to_string(flight.getMinute()) + " - " + flight.getType() + " - " + flight.getDestination() +
            " - " + std::to_string(flight.getDelay())));
        i++;
    }
}

void GUI::connectSignals(){
    connect(this->ui->filterButton, &QPushButton::clicked, this, [this](){
        try{
            string input = this->ui->filterLineEdit->text().trimmed().toStdString();
            int delay = stoi(input);

            populateList(this->ui->mainListWidget, serv.getDelayedFlights(delay));

            this->ui->filterLineEdit->clear();
        }catch(std::exception& e){
            string message = e.what();
            if(message == "stoi"){
                message = "Invalid input!";
            }
            QMessageBox::warning(this, "Error", message.c_str());
        }
    });
    connect(this->ui->showButton, &QPushButton::clicked, this, [this](){
        try{
            string destination = this->ui->destinationLineEdit->text().trimmed().toStdString();
            string time = this->ui->timeLineEdit->text().trimmed().toStdString();
            std::stringstream ss{time};
            string hour, minute;
            getline(ss, hour, ':');
            getline(ss, minute);

            auto result=  serv.getFlightsAndTotalDelay(destination, stoi(hour), stoi(minute));
            auto flights = result.first;
            auto totalDelay = result.second;

            if(!flights.empty()){
                this->ui->label->setText(QString("Total Delay: ") + QString::number(totalDelay));
                populateList(this->ui->secondaryListWidget, flights);
            }else{
                this->ui->label->setText("There are no such flights!");
                this->ui->secondaryListWidget->clear();
            }

            this->ui->destinationLineEdit->clear();
            this->ui->timeLineEdit->clear();
        }catch(std::exception& e){
            string message = e.what();
            if(message == "stoi"){
                message = "Invalid input!";
            }
            QMessageBox::warning(this, "Error", message.c_str());
        }
    });
}

GUI::~GUI() {
    delete ui;
}

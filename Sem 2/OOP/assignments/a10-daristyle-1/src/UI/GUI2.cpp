#include "GUI2.h"
#include "ui_GUI2.h"

#include <iostream>
#include <string>
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QShortcut>

#include "GUI.h"

using std::string;

GUI2::GUI2(QWidget *parent, InterfaceRepository *_repository, InterfaceRepository *_watchlist) :
    QWidget(parent), ui(new Ui::GUI2), UI(_repository, _watchlist) {
    ui->setupUi(this);

    this->ui->likesInput->setValidator(new QIntValidator(0, 1e9, this));

    this->userTabelModel = new TutorialTabelModel(this->service.getWatchlist(), this);

    this->setUpTable(this->ui->adminTable);
    this->setUpTable(this->ui->userTableView, this->userTabelModel);
    this->createPiechart();
    this->addConnections();
}

GUI2::~GUI2() {
    delete ui;
}

void GUI2::addConnections(){
    QObject::connect(ui->adminMenuButton, &QPushButton::clicked, this, [this]{
        this->ui->titleInput->clear(); this->ui->presenterInput->clear(); this->ui->durationInput->setTime(QTime{0, 0}); this->ui->likesInput->clear(); this->ui->urlInput->clear();

        populateTable(this->ui->adminTable, this->service.getAllFromRepo());

        this->ui->pages->setCurrentWidget(this->ui->adminMenu);
    });
    QObject::connect(ui->userMenuButton, &QPushButton::clicked, this, [this]{
        this->ui->searchUserInput->clear();

        QMessageBox typeMessageBox;
        typeMessageBox.setWindowTitle("Confirm");
        typeMessageBox.setText("Do you want an HTML or an CSV watchlist?");
        QPushButton* csvButton = typeMessageBox.addButton("CSV", QMessageBox::AcceptRole);
        QPushButton* htmlButton = typeMessageBox.addButton("HTML", QMessageBox::AcceptRole);
        typeMessageBox.setDefaultButton(csvButton);
        typeMessageBox.exec();

        if(typeMessageBox.clickedButton() == csvButton){
            this->service.switchToCSV();
        }else{
            this->service.switchToHTML();
        }

        tutorials = this->service.getAllFromRepo();
        index = tutorials.size();
        showVideo();

        userTabelModel->updateData(service.getWatchlist());

        this->ui->pages->setCurrentWidget(this->ui->userMenu);
    });
    QObject::connect(ui->exitMenuButton, &QPushButton::clicked, qApp, &QApplication::quit);

    QObject::connect(ui->addAdminButton, &QPushButton::clicked, this, [this]{
        try{
            string title = this->ui->titleInput->text().trimmed().toStdString();
            string presenter = this->ui->presenterInput->text().trimmed().toStdString();
            QTime time = this->ui->durationInput->time();
            Duration d = Duration{time.minute(), time.second()};
            QString likesString = this->ui->likesInput->text().trimmed();
            int likes = likesString.isEmpty() ? -1 : likesString.toInt();
            string url = this->ui->urlInput->text().trimmed().toStdString();

            this->service.addToRepo(Tutorial{title, presenter, d, likes, url});
            populateTable(this->ui->adminTable, this->service.getAllFromRepo());

            this->ui->titleInput->clear(); this->ui->presenterInput->clear(); this->ui->durationInput->setTime(QTime{0, 0}); this->ui->likesInput->clear(); this->ui->urlInput->clear();
        }catch(const std::exception& e){
            QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
        }
    });
    QObject::connect(ui->updateAdminButton, &QPushButton::clicked, this, [this]{
        try{
            string title = this->ui->titleInput->text().trimmed().toStdString();
            string presenter = this->ui->presenterInput->text().trimmed().toStdString();
            QTime time = this->ui->durationInput->time();
            Duration d = Duration{time.minute(), time.second()};
            QString likesString = this->ui->likesInput->text().trimmed();
            int likes = likesString.isEmpty() ? -1 : likesString.toInt();
            string url = this->ui->urlInput->text().trimmed().toStdString();

            this->service.updateInRepo(Tutorial{title, presenter, d, likes, url});
            populateTable(this->ui->adminTable, this->service.getAllFromRepo());

            this->ui->titleInput->clear(); this->ui->presenterInput->clear(); this->ui->durationInput->setTime(QTime{0, 0}); this->ui->likesInput->clear(); this->ui->urlInput->clear();
        }catch(const std::exception& e){
            QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
        }
    });
    QObject::connect(ui->removeAdminButton, &QPushButton::clicked, this, [this]{
        try{
            string title = this->ui->titleInput->text().trimmed().toStdString();
            string presenter = this->ui->presenterInput->text().trimmed().toStdString();


            this->service.removeFromRepo(Tutorial{title, presenter, {0, 1}, 0, "0.0"});
            populateTable(this->ui->adminTable, this->service.getAllFromRepo());

            this->ui->titleInput->clear(); this->ui->presenterInput->clear(); this->ui->durationInput->setTime(QTime{0, 0}); this->ui->likesInput->clear(); this->ui->urlInput->clear();
        }catch(const std::exception& e){
            QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
        }
    });
    QObject::connect(ui->exitAdminButton, &QPushButton::clicked, this, [this]{this->ui->pages->setCurrentWidget(this->ui->mainMenu);});

    QObject::connect(ui->adminTable, &QTableWidget::itemSelectionChanged, this, [this]{
        int selectedRow = ui->adminTable->currentRow();
        if(selectedRow < 0){
            this->ui->titleInput->clear(); this->ui->presenterInput->clear(); this->ui->durationInput->setTime(QTime{0, 0}); this->ui->likesInput->clear(); this->ui->urlInput->clear();
            return;
        }

        auto titleItem = ui->adminTable->item(selectedRow, 0);
        if(!titleItem || titleItem->text().isEmpty()){
            this->ui->titleInput->clear(); this->ui->presenterInput->clear(); this->ui->durationInput->setTime(QTime{0, 0}); this->ui->likesInput->clear(); this->ui->urlInput->clear();
            return;
        }

        ui->titleInput->setText(ui->adminTable->item(selectedRow, 0)->text());
        ui->presenterInput->setText(ui->adminTable->item(selectedRow, 1)->text());
        ui->durationInput->setTime(QTime::fromString(ui->adminTable->item(selectedRow, 2)->text(), "mm:ss"));
        ui->likesInput->setText(ui->adminTable->item(selectedRow, 3)->text());
        ui->urlInput->setText(ui->adminTable->item(selectedRow, 4)->text());
    });

    QObject::connect(this->ui->undoButton, &QPushButton::clicked, this, [this]{
        try{
            this->service.undo();
            populateTable(this->ui->adminTable, this->service.getAllFromRepo());
        }catch(const std::exception& e){
            QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
        }
    });
    this->ui->undoButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z));
    QObject::connect(this->ui->redoButton, &QPushButton::clicked, this, [this]{
        try{
           this->service.redo();
           populateTable(this->ui->adminTable, this->service.getAllFromRepo());
       }catch(const std::exception& e){
           QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
       }
    });
    this->ui->redoButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Y));

    QObject::connect(this->ui->piechartButton, &QPushButton::clicked, this, [this]{
        updatePiechart();
        this->ui->pages->setCurrentWidget(this->ui->pieChartPage);
    });


    QObject::connect(ui->nextUserButton, &QPushButton::clicked, this, [this]{showVideo();});
    QObject::connect(ui->searchUserButton, &QPushButton::clicked, this, [this]{
        string presenter = this->ui->searchUserInput->text().trimmed().toStdString();
        tutorials = presenter.empty() ? this->service.getAllFromRepo() : this->service.getPresentedBy(presenter);
        index = tutorials.size();
        showVideo();
    });
    QObject::connect(ui->addUserButton, &QPushButton::clicked, this, [this]{
        if (tutorials.empty() || index >= tutorials.size()) {
            QMessageBox::warning(this, "Error", "No tutorial to add.");
            return;
        }
        try{
            this->service.addToWatchlist(tutorials[index]);
            userTabelModel->updateData(service.getWatchlist());
        }catch(const std::exception& e){
            QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
        }
    });
    QObject::connect(ui->removeUserButton, &QPushButton::clicked, this, [this]{
        try{
            /*
            int currentRow = this->ui->userTable->currentRow();
            auto titleItem = this->ui->userTable->item(currentRow, 0);
            auto presenterItem = this->ui->userTable->item(currentRow, 1);
            if(!titleItem || !presenterItem || titleItem->text().isEmpty() || presenterItem->text().isEmpty()){
                return;
            }
            string title = titleItem->text().toStdString();
            string presenter = presenterItem->text().toStdString();
            this->service.removeFromWatchlist(Tutorial{title, presenter, {0, 1}, 0, "0.0"});
            */
            QItemSelectionModel *selection_model = this->ui->userTableView->selectionModel();
            if(!selection_model->hasSelection()){
                return;
            }

            int currentRow = selection_model->currentIndex().row();
            this->service.removeFromWatchlist(this->userTabelModel->at(currentRow));

            QMessageBox::StandardButton liked = QMessageBox::question(this, "Confirm", "Did you like the tutorial?", QMessageBox::Yes | QMessageBox::No);
            if(liked == QMessageBox::Yes){
                this->service.likeTutorial(tutorials[index]);
                tutorials = this->service.getAllFromRepo();
            }
            userTabelModel->updateData(service.getWatchlist());
        }catch(const std::exception& e){
            QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
        }
    });
    QObject::connect(ui->openUserButton, &QPushButton::clicked, this, [this]{this->service.openWatchlist();});
    QObject::connect(ui->exitUserButton, &QPushButton::clicked, this, [this]{this->ui->pages->setCurrentWidget(this->ui->mainMenu);});
}

void GUI2::
setUpTable(QTableWidget* table){
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels({"Title", "Presenter", "Duration", "Likes", "URL"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void GUI2::setUpTable(QTableView* table, TutorialTabelModel* model){
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setModel(model);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
}

void GUI2::populateTable(QTableWidget* table, const std::vector<Tutorial>& tutorials){
    table->clearContents();
    table->setRowCount(tutorials.size() + 1);
    for(int i = 0; i < tutorials.size(); i++){
        table->setItem(i, 0, new QTableWidgetItem{QString::fromStdString(tutorials[i].get_title())});
        table->setItem(i, 1, new QTableWidgetItem{QString::fromStdString(tutorials[i].get_presenter())});
        table->setItem(i, 2, new QTableWidgetItem(QTime{0, tutorials[i].get_duration().get_minutes(), tutorials[i].get_duration().get_seconds()}.toString("mm:ss")));
        table->setItem(i, 3, new QTableWidgetItem{QString::number(tutorials[i].get_likes())});
        table->setItem(i, 4, new QTableWidgetItem{QString::fromStdString(tutorials[i].get_url())});
    }
}

void GUI2::showVideo(){
    if(tutorials.empty()){
        const QString notFoundPage = R"(
        <style>
            body {
                background-color: #24243e;
                color: #ffffff;
                font-family: 'Segoe UI', sans-serif;
                display: flex;
                flex-direction: column;
                justify-content: center;
                align-items: center;
                height: 100vh;
                margin: 0;
            }
            h1 { color: #bb86fc; }
        </style>
        <body>
            <h1>No tutorials found</h1>
        </body>
        )";
        this->ui->webEngine->setHtml(notFoundPage);
    }else{
        ++index;
        if(index >= tutorials.size()){
            index = 0;
        }
        this->ui->webEngine->setUrl(QUrl(QString::fromStdString(tutorials[index].get_url())));
    }
}

void GUI2::createPiechart(){
    QChart *chart = new QChart();
    chart->setTitle("Tutorials Likes");
    chart->legend()->show();
    chart->setAnimationOptions(QChart::SeriesAnimations);
    ui->piechartView->setChart(chart);
    ui->piechartView->setRenderHint(QPainter::Antialiasing);
}

void GUI2::updatePiechart(){
    QPieSeries* series = new QPieSeries();
    for(const auto& tutorial: service.getAllFromRepo()){
        series->append(QString::fromStdString(tutorial.get_title()), tutorial.get_likes())->setLabelVisible(true);
    }

    this->ui->piechartView->chart()->removeAllSeries();
    this->ui->piechartView->chart()->addSeries(series);
}

void GUI2::run(){
    ui->pages->setCurrentIndex(0);
    this->show();
}
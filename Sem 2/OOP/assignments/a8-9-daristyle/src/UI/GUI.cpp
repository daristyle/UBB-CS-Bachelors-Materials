#include "GUI.h"

#include <QApplication>

GUI::GUI(InterfaceRepository *_repository, InterfaceRepository *_watchlist): UI(_repository, _watchlist){
    QVBoxLayout* layout = new QVBoxLayout{this};

    stackedWidget = new QStackedWidget{};
    layout->addWidget(this->stackedWidget);

    this->setUpMainMenu();
    this->setUpAdminMenu();
    this->setUpAdminAddMenu();
    this->setUpAdminRemoveMenu();
    this->setUpAdminUpdateMenu();
    this->setUpAdminListMenu();

    this->stackedWidget->addWidget(this->mainWidget);
    this->stackedWidget->addWidget(this->adminWidget);
    this->stackedWidget->addWidget(this->adminAddWidget);
    this->stackedWidget->addWidget(this->adminRemoveWidget);
    this->stackedWidget->addWidget(this->adminUpdateWidget);
    this->stackedWidget->addWidget(this->adminListWidget);

    this->stackedWidget->setCurrentIndex(0);
}

void GUI::setUpMainMenu(){
    this->mainWidget = new QWidget{};
    QVBoxLayout* layout = new QVBoxLayout{this->mainWidget};

    QLabel* title = new QLabel{"Main Menu\n"};
    title->setAlignment(Qt::AlignCenter);
    QFont titleFont = title->font();
    titleFont.setPointSize(24);
    titleFont.setBold(true);
    title->setFont(titleFont);

    this->menuAdminButton = new QPushButton{"Admin Menu"};
    this->menuUserButton = new QPushButton{"User Menu"};
    this->menuExitButton = new QPushButton{"Exit"};
    this->menuAdminButton->setFixedWidth(250);
    this->menuUserButton->setFixedWidth(250);
    this->menuExitButton->setFixedWidth(250);

    layout->addStretch();
    layout->addWidget(title, 0, Qt::AlignHCenter);
    layout->addSpacing(30);
    layout->addWidget(this->menuAdminButton, 0, Qt::AlignHCenter);
    layout->addSpacing(5);
    layout->addWidget(this->menuUserButton, 0, Qt::AlignHCenter);
    layout->addSpacing(30);
    layout->addWidget(this->menuExitButton, 0, Qt::AlignHCenter);
    layout->addStretch();

    connect(this->menuAdminButton, &QPushButton::clicked, this, [this]{this->stackedWidget->setCurrentIndex(1);});
    connect(this->menuExitButton, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(this->menuUserButton, &QPushButton::clicked, this, []{});
}

void GUI::setUpAdminMenu(){
    this->adminWidget = new QWidget{};
    QVBoxLayout* layout = new QVBoxLayout{this->adminWidget};

    QLabel* title = new QLabel{"Admin Menu\n"};
    title->setAlignment(Qt::AlignCenter);
    QFont titleFont = title->font();
    titleFont.setPointSize(24);
    titleFont.setBold(true);
    title->setFont(titleFont);

    this->adminAddButton = new QPushButton{"Add Tutorial"};
    this->adminRemoveButton = new QPushButton{"Remove Tutorial"};
    this->adminUpdateButton = new QPushButton{"Update Tutorial"};
    this->adminListButton = new QPushButton{"List Tutorials"};
    this->adminExitButton = new QPushButton{"Exit"};
    this->adminAddButton->setFixedWidth(250);
    this->adminRemoveButton->setFixedWidth(250);
    this->adminUpdateButton->setFixedWidth(250);
    this->adminListButton->setFixedWidth(250);
    this->adminExitButton->setFixedWidth(250);

    layout->addStretch();
    layout->addWidget(title, 0, Qt::AlignHCenter);
    layout->addSpacing(30);
    layout->addWidget(this->adminAddButton, 0, Qt::AlignHCenter);
    layout->addSpacing(5);
    layout->addWidget(this->adminRemoveButton, 0, Qt::AlignHCenter);
    layout->addSpacing(5);
    layout->addWidget(this->adminUpdateButton, 0, Qt::AlignHCenter);
    layout->addSpacing(5);
    layout->addWidget(this->adminListButton, 0, Qt::AlignHCenter);
    layout->addSpacing(30);
    layout->addWidget(this->adminExitButton, 0, Qt::AlignHCenter);
    layout->addStretch();

    connect(this->adminAddButton, &QPushButton::clicked, this, [this]{this->stackedWidget->setCurrentIndex(2);});
    connect(this->adminRemoveButton, &QPushButton::clicked, this, [this]{this->stackedWidget->setCurrentIndex(3);});
    connect(this->adminUpdateButton, &QPushButton::clicked, this, [this]{this->stackedWidget->setCurrentIndex(4);});
    connect(this->adminListButton, &QPushButton::clicked, this, [this]{
        this->populateList();
        this->stackedWidget->setCurrentIndex(5);
    });
    connect(this->adminExitButton, &QPushButton::clicked, qApp, &QApplication::quit);
}

void GUI::setUpAdminAddMenu(){
    this->adminAddWidget = new QWidget{};
    QVBoxLayout* layout = new QVBoxLayout{this->adminAddWidget};
    QFormLayout* formLayout = new QFormLayout{};

    QLabel* menuTitle = new QLabel{"Add Tutorial"};
    menuTitle->setAlignment(Qt::AlignCenter);
    QFont titleFont = menuTitle->font();
    titleFont.setPointSize(24);
    titleFont.setBold(true);
    menuTitle->setFont(titleFont);

    QLabel* result = new QLabel{};
    result->setAlignment(Qt::AlignCenter);
    QFont resultFont = result->font();
    resultFont.setPointSize(16);
    result->setFont(resultFont);


    QLineEdit* title = new QLineEdit{};
    title->setPlaceholderText("Title");
    QLineEdit* presenter = new QLineEdit{};
    presenter->setPlaceholderText("Presenter");
    QTimeEdit* duration = new QTimeEdit{};
    duration->setDisplayFormat("mm:ss");
    duration->setTime(QTime{0, 0, 0});
    QLineEdit* url = new QLineEdit{};
    url->setPlaceholderText("URL");
    QIntValidator* likesValidator = new QIntValidator{0, (int)2e9, this};
    QLineEdit* likes = new QLineEdit{};
    likes->setPlaceholderText("Likes");
    likes->setValidator(likesValidator);

    formLayout->addRow("Title:", title);
    formLayout->addRow("Presenter:", presenter);
    formLayout->addRow("Duration:", duration);
    formLayout->addRow("Link:", url);
    formLayout->addRow("Likes:", likes);


    this->submitAddButton = new QPushButton{"Add"};
    this->backAddButton = new QPushButton{"Back"};
    this->submitAddButton->setFixedWidth(250);
    this->backAddButton->setFixedWidth(250);

    layout->addStretch();
    layout->addWidget(menuTitle, 0, Qt::AlignHCenter);
    layout->addSpacing(15);
    layout->addWidget(result, 0, Qt::AlignHCenter);
    layout->addSpacing(45);
    layout->addLayout(formLayout);
    layout->addSpacing(30);
    layout->addWidget(this->submitAddButton, 0, Qt::AlignHCenter);
    layout->addSpacing(10);
    layout->addWidget(this->backAddButton, 0, Qt::AlignHCenter);
    layout->addStretch();

    connect(this->backAddButton, &QPushButton::clicked, this,
        [this, title, presenter, duration, url, likes, result]{
            title->clear(); presenter->clear(); duration->setTime(QTime{0, 0, 0}); url->clear(); likes->clear();result->clear();
            this->stackedWidget->setCurrentIndex(1);
    });

    connect(this->submitAddButton, &QPushButton::clicked, this,
        [this, title, presenter, duration, url, likes, result]{
            std::string msg;
            try{
                int numberOfLikes = likes->text().trimmed().isEmpty() ? -1: likes->text().trimmed().toInt();
                Duration time{duration->time().minute(), duration->time().second()};
                Tutorial t{title->text().trimmed().toStdString(), presenter->text().trimmed().toStdString(),
                        time, numberOfLikes, url->text().trimmed().toStdString()};
                this->service.addToRepo(t);
                msg = "Tutorial added!";
                title->clear(); presenter->clear(); duration->setTime(QTime{0, 0, 0}); url->clear(); likes->clear();
            }catch(const std::exception& e){
                msg = e.what();
            }
            result->setText(QString::fromStdString(msg));
    });
}

void GUI::setUpAdminUpdateMenu(){
    this->adminUpdateWidget = new QWidget{};
    QVBoxLayout* layout = new QVBoxLayout{this->adminUpdateWidget};
    QFormLayout* formLayout = new QFormLayout{};

    QLabel* menuTitle = new QLabel{"Update Tutorial"};
    menuTitle->setAlignment(Qt::AlignCenter);
    QFont titleFont = menuTitle->font();
    titleFont.setPointSize(24);
    titleFont.setBold(true);
    menuTitle->setFont(titleFont);

    QLabel* result = new QLabel{};
    result->setAlignment(Qt::AlignCenter);
    QFont resultFont = result->font();
    resultFont.setPointSize(16);
    result->setFont(resultFont);


    QLineEdit* title = new QLineEdit{};
    title->setPlaceholderText("Title");
    QLineEdit* presenter = new QLineEdit{};
    presenter->setPlaceholderText("Presenter");
    QTimeEdit* duration = new QTimeEdit{};
    duration->setDisplayFormat("mm:ss");
    duration->setTime(QTime{0, 0, 0});
    QLineEdit* url = new QLineEdit{};
    url->setPlaceholderText("URL");
    QIntValidator* likesValidator = new QIntValidator{0, (int)2e9, this};
    QLineEdit* likes = new QLineEdit{};
    likes->setPlaceholderText("Likes");
    likes->setValidator(likesValidator);

    formLayout->addRow("Title:", title);
    formLayout->addRow("Presenter:", presenter);
    formLayout->addRow("New Duration:", duration);
    formLayout->addRow("New Link:", url);
    formLayout->addRow("New Likes:", likes);


    this->submitUpdateButton = new QPushButton{"Update"};
    this->backUpdateButton = new QPushButton{"Back"};
    this->submitUpdateButton->setFixedWidth(250);
    this->backUpdateButton->setFixedWidth(250);

    layout->addStretch();
    layout->addWidget(menuTitle, 0, Qt::AlignHCenter);
    layout->addSpacing(15);
    layout->addWidget(result, 0, Qt::AlignHCenter);
    layout->addSpacing(45);
    layout->addLayout(formLayout);
    layout->addSpacing(30);
    layout->addWidget(this->submitUpdateButton, 0, Qt::AlignHCenter);
    layout->addSpacing(10);
    layout->addWidget(this->backUpdateButton, 0, Qt::AlignHCenter);
    layout->addStretch();

    connect(this->backUpdateButton, &QPushButton::clicked, this,
        [this, title, presenter, duration, url, likes, result]{
            title->clear(); presenter->clear(); duration->setTime(QTime{0, 0, 0}); url->clear(); likes->clear(); result->clear();
            this->stackedWidget->setCurrentIndex(1);
    });

    connect(this->submitUpdateButton, &QPushButton::clicked, this,
       [this, title, presenter, duration, url, likes, result]{
           std::string msg;
           try{
               int numberOfLikes = likes->text().trimmed().isEmpty() ? -1: likes->text().trimmed().toInt();
               Duration time{duration->time().minute(), duration->time().second()};
               Tutorial t{title->text().trimmed().toStdString(), presenter->text().trimmed().toStdString(),
                       time, numberOfLikes, url->text().trimmed().toStdString()};
               this->service.updateInRepo(t);
               msg = "Tutorial updated!";
               title->clear(); presenter->clear(); duration->setTime(QTime{0, 0, 0}); url->clear(); likes->clear();
           }catch(const std::exception& e){
               msg = e.what();
           }
           result->setText(QString::fromStdString(msg));
   });
}

void GUI::setUpAdminRemoveMenu(){
    this->adminRemoveWidget = new QWidget{};
    QVBoxLayout* layout = new QVBoxLayout{this->adminRemoveWidget};
    QFormLayout* formLayout = new QFormLayout{};

    QLabel* menuTitle = new QLabel{"Remove Tutorial"};
    menuTitle->setAlignment(Qt::AlignCenter);
    QFont titleFont = menuTitle->font();
    titleFont.setPointSize(24);
    titleFont.setBold(true);
    menuTitle->setFont(titleFont);

    QLabel* result = new QLabel{};
    result->setAlignment(Qt::AlignCenter);
    QFont resultFont = result->font();
    resultFont.setPointSize(16);
    result->setFont(resultFont);


    QLineEdit* title = new QLineEdit{};
    title->setPlaceholderText("Title");
    QLineEdit* presenter = new QLineEdit{};
    presenter->setPlaceholderText("Presenter");

    formLayout->addRow("Title:", title);
    formLayout->addRow("Presenter:", presenter);


    this->submitRemoveButton = new QPushButton{"Remove"};
    this->backRemoveButton = new QPushButton{"Back"};
    this->submitRemoveButton->setFixedWidth(250);
    this->backRemoveButton->setFixedWidth(250);

    layout->addStretch();
    layout->addWidget(menuTitle, 0, Qt::AlignHCenter);
    layout->addSpacing(15);
    layout->addWidget(result, 0, Qt::AlignHCenter);
    layout->addSpacing(45);
    layout->addLayout(formLayout);
    layout->addSpacing(30);
    layout->addWidget(this->submitRemoveButton, 0, Qt::AlignHCenter);
    layout->addSpacing(10);
    layout->addWidget(this->backRemoveButton, 0, Qt::AlignHCenter);
    layout->addStretch();

    connect(this->backRemoveButton, &QPushButton::clicked, this,
        [this, title, presenter, result]{
            title->clear(); presenter->clear();result->clear();
            this->stackedWidget->setCurrentIndex(1);
    });

    connect(this->submitRemoveButton, &QPushButton::clicked, this,
       [this, title, presenter, result]{
           std::string msg;
           try{
               Tutorial t{title->text().trimmed().toStdString(), presenter->text().trimmed().toStdString(),
                       Duration{0, 1}, 0, "1.1"};
               this->service.removeFromRepo(t);
               msg = "Tutorial removed!";
               title->clear(); presenter->clear();
           }catch(const std::exception& e){
               msg = e.what();
           }
           result->setText(QString::fromStdString(msg));
   });
}

void GUI::setUpAdminListMenu(){
    this->adminListWidget = new QWidget{};
    QVBoxLayout* layout = new QVBoxLayout{this->adminListWidget};

    this->listWidget = new QListWidget{};
    this->populateList();

    QLabel* menuTitle = new QLabel{"Tutorials"};
    menuTitle->setAlignment(Qt::AlignCenter);
    QFont titleFont = menuTitle->font();
    titleFont.setPointSize(24);
    titleFont.setBold(true);
    menuTitle->setFont(titleFont);

    this->backListButton = new QPushButton{"Back"};
    this->backListButton->setFixedWidth(250);

    layout->addWidget(menuTitle, 0, Qt::AlignHCenter);
    layout->addSpacing(30);
    layout->addWidget(this->listWidget);
    layout->addSpacing(30);
    layout->addWidget(this->backListButton, 0, Qt::AlignHCenter);

    connect(this->backListButton, &QPushButton::clicked, this, [this]{this->stackedWidget->setCurrentIndex(1);});
}

void GUI::populateList(){
    this->listWidget->clear();
    for(const auto tutorial: this->service.getAllFromRepo()){
        this->listWidget->addItem(QString::fromStdString(tutorial.to_string()));
    }
}

void GUI::run(){
    this->stackedWidget->setCurrentIndex(0);
    this->show();
}
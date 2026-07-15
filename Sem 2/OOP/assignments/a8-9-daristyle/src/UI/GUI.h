#pragma once

#include "UI.h"
#include "InterfaceRepository.h"
#include "MemoryRepository.h"

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QFormLayout>
#include <QLineEdit>
#include <QTimeEdit>
#include <QIntValidator>
#include <QListWidget>

class GUI: public QWidget, public UI{
private:
    QStackedWidget* stackedWidget;
    QWidget* mainWidget;
    QWidget* adminWidget;
    QWidget* adminAddWidget;
    QWidget* adminRemoveWidget;
    QWidget* adminUpdateWidget;
    QWidget* adminListWidget;
    QPushButton* menuAdminButton;
    QPushButton* menuUserButton;
    QPushButton* menuExitButton;
    QPushButton* adminAddButton;
    QPushButton* adminRemoveButton;
    QPushButton* adminUpdateButton;
    QPushButton* adminListButton;
    QPushButton* adminExitButton;
    QPushButton* submitAddButton;
    QPushButton* backAddButton;
    QPushButton* submitRemoveButton;
    QPushButton* backRemoveButton;
    QPushButton* submitUpdateButton;
    QPushButton* backUpdateButton;
    QPushButton* backListButton;
    QListWidget* listWidget;

    void setUpMainMenu();
    void setUpAdminMenu();
    void setUpAdminAddMenu();
    void setUpAdminRemoveMenu();
    void setUpAdminUpdateMenu();
    void setUpAdminListMenu();

    void populateList();
public:
    ~GUI() override = default;
    GUI(InterfaceRepository* _repository = new MemoryRepository(), InterfaceRepository* _watchlist = new MemoryRepository());

    void run() override;
};
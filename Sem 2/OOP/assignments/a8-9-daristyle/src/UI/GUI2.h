#pragma once

#include "UI.h"

#include <QWidget>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class GUI2; }
QT_END_NAMESPACE

class GUI2 : public QWidget, public UI {
Q_OBJECT

private:
    Ui::GUI2 *ui;
    vector<Tutorial> tutorials;
    int index;

    void addConnections();
    void setUpTable(QTableWidget* table);
    void populateTable(QTableWidget* t, const std::vector<Tutorial>& tutorials);
    void showVideo();
    void createPiechart();
    void updatePiechart();

public:
    explicit GUI2(QWidget *parent = nullptr, InterfaceRepository *_repository = new MemoryRepository(), InterfaceRepository *_watchlist = new MemoryRepository());
    ~GUI2() override;

    void run() override;
};
#pragma once

#include <QWidget>
#include "src/UI/TabelModel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QWidget {
Q_OBJECT

private:
    TabelModel* tabelModel;
    Ui::GUI *ui;
    Researcher researcher;

    void connectButtons();
    void developButtonUpdate();
public:
    explicit GUI(TabelModel* tabelModel, Researcher researcher, QWidget *parent = nullptr);
    ~GUI() override;
};
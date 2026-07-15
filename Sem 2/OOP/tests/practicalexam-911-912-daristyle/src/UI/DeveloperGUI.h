//
// Created by bejan on 6/19/26.
//

#ifndef PRACTICALEXAM_911_912_DARISTYLE_DEVELOPERGUI_H
#define PRACTICALEXAM_911_912_DARISTYLE_DEVELOPERGUI_H

#include <QWidget>
#include "src/Domain/Idea.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DeveloperGUI; }
QT_END_NAMESPACE

class DeveloperGUI : public QWidget {
Q_OBJECT

public:
    explicit DeveloperGUI(Idea idea, QWidget *parent = nullptr);
    ~DeveloperGUI() override;

private:
    Idea idea;
    Ui::DeveloperGUI *ui;
};


#endif //PRACTICALEXAM_911_912_DARISTYLE_DEVELOPERGUI_H

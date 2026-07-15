#include "UI/GUI.h"
#include <QApplication>

int main(int argc, char** argv){
    QApplication app{argc, argv};
    Repository repo{"bills.txt"};
    Service serv{repo};
    GUI gui{serv};
    gui.show();

    return app.exec();
}
#include <QApplication>
#include "UI/GUI.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    Repository repo("flights.txt");
    Service serv(repo);
    GUI gui(serv);

    gui.show();

    return app.exec();
}
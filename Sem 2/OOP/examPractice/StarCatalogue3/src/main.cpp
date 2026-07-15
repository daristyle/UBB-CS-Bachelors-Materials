#include <QApplication>
#include "GUI.h"

int main(int argc, char** argv){
    QApplication app(argc, argv);
    AstronomerRepository astroRepo{"astronomers.txt"};
    StarRepository starRepo{"stars.txt"};
    Service serv{astroRepo, starRepo};
    auto astronomers = serv.getAstronomers();
    int windows = astronomers.size();
    vector<GUI*> guis;
    for(int i = 0; i < windows; i++){
        guis.push_back(new GUI(astronomers[i], serv));
        guis[i]->show();
    }
    int retval = app.exec();
    for(auto gui : guis){
        delete gui;
    }
    return retval;
}
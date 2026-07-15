#include <QApplication>

#include "Repository/IdeaRepository.h"
#include "Repository/ResercherRepository.h"
#include "Service/Service.h"
#include "src/UI/GUI.h"
#include "UI/TabelModel.h"

int main(int argc, char **argv){
    QApplication app{argc, argv};
    ResercherRepository resercherRepo{"resercher.txt"};
    IdeaRepository ideaRepo{"ideas.txt"};
    Service serv{resercherRepo, ideaRepo};
    TabelModel* model = new TabelModel(serv);
    vector<GUI*> windows;
    for(auto r: resercherRepo.getResearchers()){
        windows.push_back(new GUI(model, r));
        windows.back()->show();
    }

    int ret = app.exec();
    for(auto a: windows){
        delete a;
    }
    delete model;

    return ret;
}

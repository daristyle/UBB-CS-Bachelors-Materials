#include "CUI.h"
#include "GUI.h"
#include "GUI2.h"
#include "Tests.h"
#include "TextFileRepository.h"
#include "SQLiteRepository.h"
#include "HTMLFileRepository.h"
#include "CSVFileRepository.h"
#include <QApplication>

int main(int argc, char** argv){
    //testAll();
    QApplication app{argc, argv};
    GUI2 gui{nullptr, new SQLiteRepository{"tutorials.db"}};
    gui.run();

    return app.exec();
}
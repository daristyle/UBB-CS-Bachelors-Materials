#include "UI/UI.h"
#include "Tests/Tests.h"
#include "TextFileRepository.h"
#include "SQLiteRepository.h"
#include "HTMLFileRepository.h"
#include "CSVFileRepository.h"

int main(){
    //testAll();
    UI(new SQLiteRepository{"tutorials.db"}).run();

    return 0;
}
#pragma once

#include "src/Service/Service.h"

class UI{
private:
    Service service;

    std::string readString(const std::string& msg);
    int readInt(const std::string& msg);
    Duration readDuration();
    Tutorial readTutorialDetailed();
    Tutorial readTutorialSimplified();

    void printTutorials(const vector<Tutorial>& tutorials);
    void printMenuAdmin();
    void addToRepo();
    void removeFromRepo();
    void updateInRepo();
    void showAllFromRepo();
    void runAdmin();

    void printMenuUser();
    void printViewMenu();
    void addToWatchlist(const Tutorial& tutorial);
    void removeFromWatchlist(const Tutorial& tutorial);
    void showWatchlist();
    void viewTutorials(const std::string& presenter);
    void runUser();

public:
    void run();
};

#pragma once

#include "Service.h"

#include <string>
#include <functional>

using std::string, std::function;

class UI{
private:
    Service service;

    //std::string readString(const std::string& msg);
    static string readString(const string& msg, const function<void(string)>& validator = [](const string&){});
    //static int readInt(const std::string& msg);
    static int readInt(const string& msg, const function<void(int)>& validator = [](const int&){});
    static Duration readDuration();
    static Tutorial readTutorialDetailed();
    static Tutorial readTutorialSimplified();

    static void printTutorials(const vector<Tutorial>& tutorials);
    static void printMenuAdmin();

    void addToRepo();
    void removeFromRepo();
    void updateInRepo();
    void showAllFromRepo();

    void runAdmin();

    static void printMenuUser();
    static void printViewMenu();

    void addToWatchlist(const Tutorial& tutorial);
    void removeFromWatchlist(const Tutorial& tutorial);
    void showWatchlist();
    void viewTutorials(const std::string& presenter);

    void runUser();

public:
    UI() = default;

    UI(InterfaceRepository* _repository = new MemoryRepository(), InterfaceRepository* _watchlist = new MemoryRepository());


    void run();
};

#include "CUI.h"
#include "TutorialValidator.h"

#include <iostream>
#include <functional>

using std::string, std::function;

CUI::CUI(InterfaceRepository *_repository, InterfaceRepository *_watchlist): UI(_repository, _watchlist){
}
/*
string UI::readString(const string& msg){
    std::cout << msg << std::flush;
    std::string input;
    getline(std::cin, input);
    return input;
}*/

string CUI::readString(const string& msg, const function<void(string)>& validator){
    try{
        std::cout << msg << std::flush;
        std::string input;
        getline(std::cin, input);
        validator(input);
        return input;
    }catch(const std::exception& e){
        std::cout << e.what() << std::endl;
        return readString(msg, validator);
    }
}

int CUI::readInt(const string& msg, const function<void(int)>& validator){
    int result = 0;
    bool valid = false;

    while(!valid){
        std::string input = readString(msg);

        try{
            size_t pos;
            result = std::stoi(input, &pos);

            if(pos == input.size()){
                if(result >= 0){
                    valid = true;
                }else{
                    std::cout << "Invalid input! Enter a positive number\n" << std::flush;
                }
            }else{
                std::cout << "Invalid input! Enter only numbers\n" << std::flush;
            }
        }catch(const std::invalid_argument&){
            std::cout << "Invalid input! Enter only numbers\n" << std::flush;
        }catch(const std::out_of_range&){
            std::cout << "Invalid input! Number is too large\n" << std::flush;
        }
    }

    try{
        validator(result);
        return result;
    }catch(const std::exception& e){
        std::cout << e.what() << std::endl;
        return readInt(msg, validator);
    }
}

Duration CUI::readDuration(){
    std::cout << "Enter the duration in minutes and seconds\n" << std::flush;
    int minutes = readInt("Minutes: ");
    int seconds = readInt("Seconds: ");
    Duration duration{minutes, seconds};
    try{
        TutorialValidator::validateDuration(duration);
    }catch(const std::exception& e){
        std::cout << e.what() << std::endl;
        return readDuration();
    }
    return duration;
}

Tutorial CUI::readTutorialDetailed(){
    std::string title = readString("Enter the title: ", TutorialValidator::validateTitle);
    std::string presenter = readString("Enter the presenter: ", TutorialValidator::validatePresenter);
    Duration duration = readDuration();
    int likes = readInt("Enter the number of likes: ", TutorialValidator::validateLikes);
    std::string url = readString("Enter the link: ", TutorialValidator::validateUrl);

    return {title, presenter, duration, likes, url};
}

Tutorial CUI::readTutorialSimplified(){
    std::string title = readString("Enter the title: ", TutorialValidator::validateTitle);
    std::string presenter = readString("Enter the presenter: ", TutorialValidator::validatePresenter);

    return {title, presenter, {0, 0}, 0, ""};
}

void CUI::printMenuAdmin(){
    std::cout << "MENU ADMIN\n"
              << "1. Add a tutorial\n"
              << "2. Remove a tutorial\n"
              << "3. Update a tutorial\n"
              << "4. List tutorials\n"
              << "0. Exit\n" << std::flush;
}

void CUI::printTutorials(const vector<Tutorial>& tutorials){
    int i = 0;
    for(const auto& tutorial : tutorials){
        std::cout << i + 1 << ". " << tutorial << std::endl;
        ++i;
    }
}

void CUI::showAllFromRepo(){
    auto tutorials = this->service.getAllFromRepo();
    if(tutorials.empty()){
        std::cout << "No tutorials found!" << std::endl;
    }else{
        printTutorials(tutorials);
    }
}

void CUI::addToRepo(){
    this->service.addToRepo(this->readTutorialDetailed());
}

void CUI::removeFromRepo(){
    this->service.removeFromRepo(this->readTutorialSimplified());

}

void CUI::updateInRepo(){
    this->service.updateInRepo(this->readTutorialDetailed());
}

void CUI::runAdmin(){
    bool exited = false;
    while(!exited){
        try{
            printMenuAdmin();
            switch(readInt("Enter your choice: ")){
            case 1:
                this->addToRepo();
                std::cout << "Tutorial added to repository!" << std::endl;
                break;
            case 2:
                this->removeFromRepo();
                std::cout << "Tutorial removed from repository!" << std::endl;
                break;
            case 3:
                this->updateInRepo();
                std::cout << "Tutorial updated in repository!" << std::endl;
                break;
            case 4:
                this->showAllFromRepo();
                break;
            case 0:
                exited = true;
                break;
            default:
                std::cout << "Invalid choice!" << std::endl;
            }
        }catch(const std::exception& e){
            std::cout << e.what() << std::endl;
        }
    }
}

void CUI::printMenuUser(){
    std::cout << "MENU USER\n"
              << "1. List tutorials presented by\n"
              << "2. Remove from watchlist\n"
              << "3. Show watchlist\n"
              << "4. Open watchlist\n"
              << "0. Exit" << std::endl;
}

void CUI::printViewMenu(){
    std::cout << "MENU VIEW\n"
              << "1. Next\n"
              << "2. Add to watchlist\n"
              << "0. Exit" << std::endl;
}

void CUI::addToWatchlist(const Tutorial& tutorial){
    this->service.addToWatchlist(tutorial);
}

void CUI::viewTutorials(const std::string& presenter){
    auto tutorials = presenter != "" ? this->service.getPresentedBy(presenter) : this->service.getAllFromRepo();
    if(tutorials.empty()){
        std::cout << "No tutorials found!" << std::endl;
        return;
    }

    auto it = tutorials.begin();
    bool exited = false;
    while(!exited){
        try{
            it->play();
            std::cout << *it << std::endl;

            printViewMenu();
            switch(readInt("Enter your choice: ")){
            case 1:
                break;
            case 2:
                this->addToWatchlist(*it);
                std::cout << "Tutorial added to watchlist!" << std::endl;
                break;
            case 0:
                exited = true;
                break;
            default:
                std::cout << "Invalid choice!" << std::endl;
            }

            ++it;
            if(it == tutorials.end()){
                it = tutorials.begin();
            }
        }catch(const std::exception& e){
            std::cout << e.what() << std::endl;
        }
    }
}

void CUI::removeFromWatchlist(const Tutorial& tutorial){
    this->service.removeFromWatchlist(tutorial);
    std::cout << "Tutorial removed from watchlist!" << std::endl;
    bool exited = false;
    while(!exited){
        auto response = readString("Do you want to like it? (yes/no): ");
        if(response == "yes"){
            this->service.likeTutorial(tutorial);
            exited = true;
        }else if(response == "no"){
            exited = true;
        }else{
            std::cout << "Invalid response!" << std::endl;
        }
    }
}

void CUI::showWatchlist(){
    auto tutorials = this->service.getWatchlist();
    if(tutorials.empty()){
        std::cout << "No tutorials in watchlist!" << std::endl;
    }else{
        printTutorials(tutorials);
    }
}

void CUI::runUser(){
    string watchlistType = readString("Do you want to save the watchlsit as a CSV file or a HTML File?(CSV/HTML): ",
        [](const string& input){
            if(input != "CSV" && input != "HTML"){
                throw ValidationException("Invalid input! Enter CSV or HTML");
            }
        });

    if(watchlistType == "CSV"){
        this->service.switchToCSV();
    }else{
        this->service.switchToHTML();
    }

    bool exited = false;
    while(!exited){
        try{
            printMenuUser();
            switch(readInt("Enter your choice: ")){
            case 1:
                this->viewTutorials(readString("Enter the presenter: "));
                break;
            case 2:
                this->removeFromWatchlist(this->readTutorialSimplified());
                break;
            case 3:
                this->showWatchlist();
                break;
            case 4:
                this->service.openWatchlist();
                break;
            case 0:
                exited = true;
                break;
            default:
                std::cout << "Invalid choice!" << std::endl;
            }
        }catch(const std::exception& e){
            std::cout << e.what() << std::endl;
        }
    }
}

void CUI::run(){
    bool exited = false;
    while(!exited){
        std::cout << "1. Administrator Mode\n"
                  << "2. User Mode\n"
                  << "0. Exit" << std::endl;
        switch(readInt("Enter your choice: ")){
            case 1:
                this->runAdmin();
                break;
            case 2:
                this->runUser();
                break;
            case 0:
                exited = true;
                break;
            default:
                std::cout << "Invalid choice!" << std::endl;
        }
    }
}
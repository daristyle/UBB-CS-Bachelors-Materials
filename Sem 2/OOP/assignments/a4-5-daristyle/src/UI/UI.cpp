#include "UI.h"

#include <iostream>
#include <ostream>

std::string UI::readString(const std::string& msg){
    std::cout << msg << std::flush;
    std::string input;
    getline(std::cin, input);
    return input;
}

int UI::readInt(const std::string& msg){
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

    return result;
}

Duration UI::readDuration(){
    std::cout << "Enter the duration in minutes and seconds\n" << std::flush;
    int minutes = readInt("Minutes: ");
    int seconds = readInt("Seconds: ");
    return {minutes, seconds};
}

Tutorial UI::readTutorialDetailed(){
    std::string title = readString("Enter the title: ");
    std::string presenter = readString("Enter the presenter: ");
    Duration duration = readDuration();
    int likes = readInt("Enter the number of likes: ");
    std::string url = readString("Enter the link: ");

    return {title, presenter, duration, likes, url};
}

Tutorial UI::readTutorialSimplified(){
    std::string title = readString("Enter the title: ");
    std::string presenter = readString("Enter the presenter: ");

    return {title, presenter, {0, 0}, 0, ""};
}

void UI::printMenuAdmin(){
    std::cout << "MENU ADMIN\n"
              << "1. Add a tutorial\n"
              << "2. Remove a tutorial\n"
              << "3. Update a tutorial\n"
              << "4. List tutorials\n"
              << "0. Exit\n" << std::flush;
}

void UI::printTutorials(const vector<Tutorial>& tutorials){
    for(int i = 0; i < tutorials.size(); i++){
        std::cout << i + 1 << ". " << tutorials[i].to_string() << std::endl;
    }
}

void UI::showAllFromRepo(){
    auto tutorials = this->service.getAllFromRepo();
    if(tutorials.empty()){
        std::cout << "No tutorials found!" << std::endl;
    }else{
        printTutorials(tutorials);
    }
}

void UI::addToRepo(){
    if(!this->service.addToRepo(this->readTutorialDetailed())){
        std::cout << "Tutorial already exists!" << std::endl;
    }else{
        std::cout << "Tutorial added!" << std::endl;
    }
}

void UI::removeFromRepo(){
    if(!this->service.removeFromRepo(this->readTutorialSimplified())){
        std::cout << "Tutorial not found!" << std::endl;
    }else{
        std::cout << "Tutorial removed!" << std::endl;
    }
}

void UI::updateInRepo(){
    if(!this->service.updateInRepo(this->readTutorialDetailed())){
        std::cout << "Tutorial not found!" << std::endl;
    }else{
        std::cout << "Tutorial updated!" << std::endl;
    }
}

void UI::runAdmin(){
    bool exited = false;
    while(!exited){
        printMenuAdmin();
        switch(readInt("Enter your choice: ")){
            case 1:
                this->addToRepo();
                break;
            case 2:
                this->removeFromRepo();
                break;
            case 3:
                this->updateInRepo();
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
    }
}

void UI::printMenuUser(){
    std::cout << "MENU USER\n"
              << "1. List tutorials presented by\n"
              << "2. Remove from watchlist\n"
              << "3. Show watchlist\n"
              << "0. Exit" << std::endl;
}

void UI::printViewMenu(){
    std::cout << "MENU VIEW\n"
              << "1. Next\n"
              << "2. Add to watchlist\n"
              << "0. Exit" << std::endl;
}

void UI::addToWatchlist(const Tutorial& tutorial){
    if(!this->service.addToWatchlist(tutorial)){
        std::cout << "Tutorial already in watchlist!" << std::endl;
    }else{
        std::cout << "Tutorial added to watchlist!" << std::endl;
    }
}

void UI::viewTutorials(const std::string& presenter){
    auto tutorials = presenter != "" ? this->service.getPresentedBy(presenter) : this->service.getAllFromRepo();
    if(tutorials.empty()){
        std::cout << "No tutorials found!" << std::endl;
        return;
    }

    int i = 0;
    bool exited = false;
    while(!exited){
        tutorials[i].play();
        std::cout << tutorials[i].to_string() << std::endl;
        printViewMenu();
        switch(readInt("Enter your choice: ")){
            case 1:
                break;
            case 2:
                this->addToWatchlist(tutorials[i]);
                break;
            case 0:
                exited = true;
                break;
            default:
                std::cout << "Invalid choice!" << std::endl;
        }
        ++i;
        if(i >= tutorials.size()){
            i = 0;
        }
    }
}

void UI::removeFromWatchlist(const Tutorial& tutorial){
    if(!this->service.removeFromWatchlist(tutorial)){
        std::cout << "Tutorial not in watchlist!" << std::endl;
    }else{
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
}

void UI::showWatchlist(){
    auto tutorials = this->service.getWatchlist();
    if(tutorials.empty()){
        std::cout << "No tutorials in watchlist!" << std::endl;
    }else{
        printTutorials(tutorials);
    }
}

void UI::runUser(){
    bool exited = false;
    while(!exited){
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
            case 0:
                exited = true;
                break;
            default:
                std::cout << "Invalid choice!" << std::endl;
        }
    }
}

void UI::run(){
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
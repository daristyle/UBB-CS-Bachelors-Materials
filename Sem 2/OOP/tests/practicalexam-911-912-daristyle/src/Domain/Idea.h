#pragma once

#include <string>
using std::string;

class Idea {
private:
    string title;
    string description;
    string status;
    string creator;
    int duration;

public:
    Idea(string title, string description, string status, string creator, int duration);

    string getTitle() const;
    string getDescription() const;
    string getStatus() const;
    string getCreator() const;
    int getDuration() const;
    void accept();
    void save() const;
    void setDescription(string str);
};
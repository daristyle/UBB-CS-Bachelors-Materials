#include "Tutorial.h"

#include <unistd.h>

Duration::Duration(int _minutes, int _seconds): minutes(_minutes + _seconds / 60), seconds(_seconds % 60){
}

int Duration::get_minutes(){
    return this->minutes;
}

int Duration::get_seconds(){
    return this->seconds;
}

void Duration::set_minutes(int _minutes){
    this->minutes = _minutes;
}

void Duration::set_seconds(int _seconds){
    this->minutes += _seconds / 60;
    this->seconds = _seconds % 60;
}

std::string Duration::to_string(){
    return std::to_string(this->minutes) + ":" + std::to_string(this->seconds);
}

bool Duration::operator==(const Duration& duration) const{
    return this->minutes == duration.minutes && this->seconds == duration.seconds;
}

Tutorial::Tutorial(): title(""), presenter(""), duration(0, 0), likes(0), url(""){
}

Tutorial::Tutorial(const std::string& _title, const std::string& _presenter, const Duration& _duration, int _likes, const std::string& _url):
    title(_title), presenter(_presenter), duration(_duration), likes(_likes), url(_url){
}

std::string Tutorial::get_title(){
    return this->title;
}

std::string Tutorial::get_presenter(){
    return this->presenter;
}

Duration Tutorial::get_duration(){
    return this->duration;
}

int Tutorial::get_likes(){
    return this->likes;
}

std::string Tutorial::get_url(){
    return this->url;
}

void Tutorial::set_title(const std::string& _title){
    this->title = _title;
}

void Tutorial::set_presenter(const std::string& _presenter){
    this->presenter = _presenter;
}

void Tutorial::set_duration(const Duration& _duration){
    this->duration = _duration;
}

void Tutorial::set_likes(int _likes){
    this->likes = _likes;
}

void Tutorial::set_url(const std::string& _url){
    this->url = _url;
}

bool Tutorial::operator==(const Tutorial& tutorial) const{
    return this->title == tutorial.title && this->presenter == tutorial.presenter;
}

std::string Tutorial::to_string(){
    return this->title + " - " + this->presenter + " - " + this->duration.to_string() + " - " + std::to_string(this->likes)
    + " likes - " + this->url;
}

void Tutorial::like(){
    ++this->likes;
}

void Tutorial::play(){
    if(fork() == 0){
        execl("/usr/bin/firefox", "firefox", this->url.c_str(), NULL);
        exit(1);
    }
}

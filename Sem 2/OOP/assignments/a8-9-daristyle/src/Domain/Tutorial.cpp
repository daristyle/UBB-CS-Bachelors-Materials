#include "Tutorial.h"
#include <iostream>
#include <unistd.h>

Duration::Duration(int _minutes, int _seconds): minutes(_minutes + _seconds / 60), seconds(_seconds % 60){
}

int Duration::get_minutes() const{
    return this->minutes;
}

int Duration::get_seconds() const{
    return this->seconds;
}

void Duration::set_minutes(int _minutes){
    this->minutes = _minutes;
}

void Duration::set_seconds(int _seconds){
    this->minutes += _seconds / 60;
    this->seconds = _seconds % 60;
}

std::string Duration::to_string() const{
    return std::to_string(this->minutes) + ":" + std::to_string(this->seconds);
}

bool Duration::operator==(const Duration& duration) const{
    return this->minutes == duration.minutes && this->seconds == duration.seconds;
}

std::ostream& operator<<(std::ostream& os, const Duration& duration){
    os << duration.minutes << ":" << (duration.seconds <= 9 ? "0" : "")<< duration.seconds;
    return os;
}

std::istream& operator>>(std::istream& is, Duration& duration){
    char separator;
    if(is >> duration.minutes >> separator >> duration.seconds){
        if(separator != ':'){
            is.setstate(std::ios::failbit);
        }
    }

    return is;
}

Tutorial::Tutorial(): title(""), presenter(""), duration(0, 0), likes(0), url(""){
}

Tutorial::Tutorial(const std::string& _title, const std::string& _presenter, const Duration& _duration, int _likes, const std::string& _url):
    title(_title), presenter(_presenter), duration(_duration), likes(_likes), url(_url){
}

std::string Tutorial::get_title() const{
    return this->title;
}

std::string Tutorial::get_presenter() const{
    return this->presenter;
}

Duration Tutorial::get_duration() const{
    return this->duration;
}

int Tutorial::get_likes() const{
    return this->likes;
}

std::string Tutorial::get_url() const{
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

std::string Tutorial::to_string() const {
    return this->title + " - " + this->presenter + " - " + this->duration.to_string() + " - " + std::to_string(this->likes)
    + " likes - " + this->url;
}

void Tutorial::like(){
    ++this->likes;
}

void Tutorial::play(){
    if(fork() == 0){
        execlp("firefox", "firefox", this->url.c_str(), NULL);
        exit(1);
    }
}

std::ostream& operator<<(std::ostream& os, const Tutorial& tutorial){
    os << tutorial.title << " - " << tutorial.presenter << " - " << tutorial.duration << " - " << tutorial.likes
        << " likes - " << tutorial.url;

    return os;
}

std::istream& operator>>(std::istream& is, Tutorial& tutorial){
    if(getline(is >> std::ws, tutorial.title, '-')){
        if(!tutorial.title.empty() && tutorial.title.back() == ' '){
            tutorial.title.pop_back();
        }
        getline(is>>std::ws, tutorial.presenter, '-');
        if(!tutorial.presenter.empty() && tutorial.presenter.back() == ' '){
            tutorial.presenter.pop_back();
        }
        char dash;
        std::string likes;
        is >> std::ws >> tutorial.duration >> dash >> tutorial.likes >> likes >> dash >> tutorial.url;
    }

    return is;
}
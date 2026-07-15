#pragma once
#include <string>

class Duration{
private:
    int minutes;
    int seconds;
public:
    Duration(int _minutes, int _seconds);
    Duration(const Duration& other) = default;
    ~Duration() = default;

    int get_minutes();
    int get_seconds();

    void set_minutes(int _minutes);
    void set_seconds(int _seconds);

    std::string to_string();
    bool operator==(const Duration& duration) const;
};

class Tutorial{
private:
    std::string title;
    std::string presenter;
    Duration duration;
    int likes;
    std::string url;
public:
    Tutorial();
    Tutorial(const std::string& _title, const std::string& _presenter,const Duration& _duration, int _likes, const std::string& _url);
    Tutorial(const Tutorial& other) = default;
    ~Tutorial() = default;

    std::string get_title();
    std::string get_presenter();
    Duration get_duration();
    int get_likes();
    std::string get_url();

    void set_title(const std::string& _title);
    void set_presenter(const std::string& _presenter);
    void set_duration(const Duration& _duration);
    void set_likes(int _likes);
    void set_url(const std::string& _url);

    bool operator==(const Tutorial& tutorial) const;

    /*
     * Returns a string containing information about the Tutorial
     */
    std::string to_string();

    /*
     * Increases the number of likes of the this tutorial by one
     */
    void like();
    /*
     * Plays the tutorial in the browser
     */
    void play();
};

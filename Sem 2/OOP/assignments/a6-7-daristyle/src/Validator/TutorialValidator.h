#pragma once

#include "Tutorial.h"
#include <string>
#include <exception>
#include <stdexcept>

using std::string;

class ValidationException: public std::runtime_error{
public:
    ValidationException(const string& msg);
};

class TutorialValidator{

public:
    static void validateTitle(const string& title);
    static void validatePresenter(const string& presenter);
    static void validateDuration(const Duration& duration);
    static void validateLikes(int likes);
    static void validateUrl(const string& url);
    static void validate(const Tutorial& tutorial);
};

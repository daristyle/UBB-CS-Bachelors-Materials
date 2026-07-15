#include "TutorialValidator.h"

#include <regex>

ValidationException::ValidationException(const string& msg): runtime_error(msg){
}

void TutorialValidator::validateTitle(const std::string& title){
    if(title.empty()){
        throw ValidationException("Title cannot be empty");
    }
}

void TutorialValidator::validatePresenter(const std::string& presenter){
    if(presenter.empty()){
        throw ValidationException("Presenter cannot be empty");
    }
}

void TutorialValidator::validateDuration(const Duration& duration){
    if(duration.get_minutes() < 0 || duration.get_seconds() < 0){
        throw ValidationException("Duration cannot be negative");
    }
}

void TutorialValidator::validateUrl(const std::string& url){
    if(url.empty()){
        return;
    }
    const std::regex urlRegex(R"(^(https?://)?[^ $#,;_]+\.[^ $#,;_]+$)");
    if(!std::regex_match(url, urlRegex)){
        throw ValidationException("URL is not valid");
    }
}

void TutorialValidator::validateLikes(int likes){
    if(likes < 0){
        throw ValidationException("Likes cannot be negative");
    }
}

void TutorialValidator::validate(const Tutorial& tutorial){
    validateTitle(tutorial.get_title());
    validatePresenter(tutorial.get_presenter());
    validateDuration(tutorial.get_duration());
    validateUrl(tutorial.get_url());
    validateLikes(tutorial.get_likes());
}

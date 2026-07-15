#pragma once
#include "src/Repository/Repository.h"

class Service{
private:
    Repository repo;
    Repository watchlist{false};

public:
    Service();

    /*
     * Adss tutorial to the repository
     */
    bool addToRepo(const Tutorial& tutorial);
    /*
     * Removes tutorial from the repository
     */
    bool removeFromRepo(const Tutorial& tutorial);
    /*
     * Updates tutorial in the repository
     */
    bool updateInRepo(const Tutorial& tutorial);
    /*
     * Returns a vector containing all the Tutorials in the Repository
     */
    vector<Tutorial> getAllFromRepo();

    /*
     * Returns a vector containing all the Tutorials in the Repository with the specified presenter
     */
    vector<Tutorial> getPresentedBy(const std::string& presenter);
    /*
     * Adds the given tutorial to the watchlist
     */
    bool addToWatchlist(const Tutorial& tutorial);
    /*
     * Removes the given tutorial from the watchlist
     */
    bool removeFromWatchlist(const Tutorial& tutorial);
    /*
     * Returns a vector containing all the Tutorials in the Watchlist
     */
    vector<Tutorial> getWatchlist();

    /*
     * Increases the number of likes of the specified tutorial by one
     */
    void likeTutorial(const Tutorial& tutorial);
};

#pragma once
#include <memory>

#include "InterfaceRepository.h"
#include "MemoryRepository.h"
#include "Operation.h"

class ServiceException: public std::runtime_error{
public:
    ServiceException(const std::string& msg);
};

class Service{
private:
    InterfaceRepository* repo;
    InterfaceRepository* watchlist;
    vector<std::unique_ptr<Operation>> operationStack;
    int stackPointer;

    void cleanStack();

public:
    Service(InterfaceRepository* _repository, InterfaceRepository* _watchlist);
    ~Service();

    /*
     * Adss tutorial to the repository
     */
    void addToRepo(const Tutorial& tutorial);
    /*
     * Removes tutorial from the repository
     */
    void removeFromRepo(const Tutorial& tutorial);
    /*
     * Updates tutorial in the repository
     */
    void updateInRepo(const Tutorial& tutorial);
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
    void addToWatchlist(const Tutorial& tutorial);
    /*
     * Removes the given tutorial from the watchlist
     */
    void removeFromWatchlist(const Tutorial& tutorial);
    /*
     * Returns a vector containing all the Tutorials in the Watchlist
     */
    vector<Tutorial> getWatchlist();

    /*
     * Increases the number of likes of the specified tutorial by one
     */
    void likeTutorial(const Tutorial& tutorial);

    void switchToHTML();

    void switchToCSV();

    void openWatchlist();

    void undo();

    void redo();
};

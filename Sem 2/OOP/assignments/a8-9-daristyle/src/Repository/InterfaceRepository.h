#pragma once

#include <stdexcept>
#include <vector>
#include <string>

#include "Tutorial.h"

using std::vector;

class RepositoryException: public std::runtime_error{
public:
    RepositoryException(const std::string& msg): runtime_error(msg){}
};

class InterfaceRepository{
public:
    virtual ~InterfaceRepository() = default;
    InterfaceRepository() = default;
    /*
     * Adds the Tutorial tutorial in the repository if there is not already there and returns true or just returns false if it is already there
     */
    virtual void add(const Tutorial& tutorial) = 0;
    /*
     * Removes the Tutorial tutorial from the repository if it is in the repository and returns true or just returns false if it is not there
     */
    virtual void remove(const Tutorial& tutorial) = 0;
    /*
     * Updates the value of the first Tutorial equal to tutorial
     */
    virtual void update(const Tutorial& tutorial) = 0;
    /*
     * Returns a vector that contains all the Tutorials in the repository
     */
    virtual vector<Tutorial> getAll() const = 0;
    /*
     * Increases the number of likes of the specified tutorial by one
     */
    virtual void likeTutorial(const Tutorial& tutorial) = 0;

    /*
    * Returns the position of the first Tutorial equal to the tutorial or -1 if there is no such a Tutorial
    */
    virtual int find(const Tutorial& tutorial) const = 0;

    virtual void clear() = 0;

    virtual void open() = 0;
};

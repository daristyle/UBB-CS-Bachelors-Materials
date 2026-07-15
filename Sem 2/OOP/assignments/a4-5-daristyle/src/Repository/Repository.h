#pragma once

#include <src/Utilities/vector.h>
#include <src/Domain/Tutorial.h>

class Repository{
private:
    vector<Tutorial> tutorials;


public:
    Repository(bool hard_coded_elements = true);
    /*
     * Adds the Tutorial tutorial in the repository if there is not already there and returns true or just returns false if it is already there
     */
    bool add(const Tutorial& tutorial);
    /*
     * Removes the Tutorial tutorial from the repository if it is in the repository and returns true or just returns false if it is not there
     */
    bool remove(const Tutorial& tutorial);
    /*
     * Updates the value of the first Tutorial equal to tutorial
     */
    bool update(const Tutorial& tutorial);
    /*
     * Returns a vector that contains all the Tutorials in the repository
     */
    vector<Tutorial> getAll();
    /*
     * Increases the number of likes of the specified tutorial by one
     */
    void likeTutorial(const Tutorial& tutorial);

    /*
    * Returns the position of the first Tutorial equal to the tutorial or -1 if there is no such a Tutorial
    */
    int find(const Tutorial& tutorial);
};

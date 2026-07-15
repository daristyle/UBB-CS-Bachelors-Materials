#pragma once

#include "InterfaceRepository.h"
#include "MemoryRepository.h"
#include <sqlite3.h>
#include <string>

using std::string;

class SQLiteRepository: public InterfaceRepository{
private:
    MemoryRepository* repo;
    sqlite3* db;
    string filename;

    void initDatabase();
    void load();
public:
    SQLiteRepository(string _filename);
    ~SQLiteRepository();

    /*
     * Adds the Tutorial tutorial in the repository if there is not already there and returns true or just returns false if it is already there
     */
    void add(const Tutorial& tutorial) override;
    /*
     * Removes the Tutorial tutorial from the repository if it is in the repository and returns true or just returns false if it is not there
     */
    void remove(const Tutorial& tutorial) override;
    /*
     * Updates the value of the first Tutorial equal to tutorial
     */
    void update(const Tutorial& tutorial) override;
    /*
     * Returns a vector that contains all the Tutorials in the repository
     */
    vector<Tutorial> getAll() const override;
    /*
     * Increases the number of likes of the specified tutorial by one
     */
    void likeTutorial(const Tutorial& tutorial) override;

    /*
    * Returns the position of the first Tutorial equal to the tutorial or -1 if there is no such a Tutorial
    */
    int find(const Tutorial& tutorial) const override;

    void clear() override;

    void open() override;
};
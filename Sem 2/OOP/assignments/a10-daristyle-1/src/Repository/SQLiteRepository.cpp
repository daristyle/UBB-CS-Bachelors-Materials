#include "SQLiteRepository.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
using std::string;

void SQLiteRepository::initDatabase(){
    string sqlCode = R"(
        CREATE TABLE IF NOT EXISTS TUTORIALS (
            TITLE TEXT PRIMARY KEY,
            PRESENTER TEXT NOT NULL,
            MINUTES INTEGER NOT NULL,
            SECONDS INTEGER NOT NULL,
            LIKES INTEGER NOT NULL,
            URL TEXT NOT NULL
        );
    )";

    char *errMsg;
    sqlite3_exec(this->db, sqlCode.c_str(), nullptr, nullptr, &errMsg);
    if(errMsg != NULL){
        string errMsgStr(errMsg);
        sqlite3_free(errMsg);
        throw RepositoryException(errMsgStr);
    }
}

void SQLiteRepository::load(){
    string sqlCode = R"(SELECT TITLE, PRESENTER, MINUTES, SECONDS, LIKES, URL FROM TUTORIALS;)";
    sqlite3_stmt *statement;
    sqlite3_prepare_v2(this->db, sqlCode.c_str(), -1, &statement, nullptr);

    while(sqlite3_step(statement) == SQLITE_ROW){
        string title{(const char*)sqlite3_column_text(statement, 0)};
        string presenter{(const char*)sqlite3_column_text(statement, 1)};
        int minutes = sqlite3_column_int(statement, 2);
        int seconds = sqlite3_column_int(statement, 3);
        int likes = sqlite3_column_int(statement, 4);
        string url{(const char*)sqlite3_column_text(statement, 5)};

        this->repo->add(Tutorial(title, presenter, Duration(minutes, seconds), likes, url));
    }

    sqlite3_finalize(statement);
}

SQLiteRepository::SQLiteRepository(string _filename): filename(_filename), repo(new MemoryRepository()){
    int exitCode = sqlite3_open(this->filename.c_str(), &this->db);
    if(exitCode != SQLITE_OK){
        throw RepositoryException("Could not open database!" + string(sqlite3_errmsg(db)));
    }

    initDatabase();

    load();
}

SQLiteRepository::~SQLiteRepository(){
    sqlite3_close(this->db);
    delete this->repo;
}

void SQLiteRepository::add(const Tutorial& tutorial){
    string sqlCode = R"(
        INSERT INTO TUTORIALS (TITLE, PRESENTER, MINUTES, SECONDS ,LIKES, URL) VALUES (?, ?, ?, ?, ?, ?);
    )";

    sqlite3_stmt *statement;
    sqlite3_prepare_v2(db, sqlCode.c_str(), -1, &statement, nullptr);

    sqlite3_bind_text(statement, 1, tutorial.get_title().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 2, tutorial.get_presenter().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(statement, 3, tutorial.get_duration().get_minutes());
    sqlite3_bind_int(statement, 4, tutorial.get_duration().get_seconds());
    sqlite3_bind_int(statement, 5, tutorial.get_likes());
    sqlite3_bind_text(statement, 6, tutorial.get_url().c_str(), -1, SQLITE_TRANSIENT);

    int stepResult = sqlite3_step(statement);
    sqlite3_finalize(statement);

    if(stepResult != SQLITE_DONE){
        throw RepositoryException("Could not add tutorial to database! Likely it already is there");
    }

    repo->add(tutorial);
}

void SQLiteRepository::remove(const Tutorial& tutorial){
    string sqlCode = R"(
        DELETE FROM TUTORIALS WHERE TITLE = ? AND PRESENTER = ?;
    )";

    sqlite3_stmt *statement;
    sqlite3_prepare_v2(db, sqlCode.c_str(), -1, &statement, nullptr);

    sqlite3_bind_text(statement, 1, tutorial.get_title().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 2, tutorial.get_presenter().c_str(), -1, SQLITE_TRANSIENT);

    int stepResult = sqlite3_step(statement), rowsModified = sqlite3_changes(db);
    sqlite3_finalize(statement);

    if(stepResult != SQLITE_DONE){
        throw RepositoryException("Could not remove tutorial from database!");
    }
    if(rowsModified == 0){
        throw RepositoryException("Tutorial not found!");
    }

    repo->remove(tutorial);
}

void SQLiteRepository::update(const Tutorial& tutorial){
    string sqlCode = R"(
        UPDATE TUTORIALS
        SET MINUTES = ?, SECONDS = ?, LIKES = ?, URL = ?
        WHERE TITLE = ? AND PRESENTER = ?;
    )";

    sqlite3_stmt *statement;
    sqlite3_prepare_v2(db, sqlCode.c_str(), -1, &statement, nullptr);

    sqlite3_bind_int(statement, 1, tutorial.get_duration().get_minutes());
    sqlite3_bind_int(statement, 2, tutorial.get_duration().get_seconds());
    sqlite3_bind_int(statement, 3, tutorial.get_likes());
    sqlite3_bind_text(statement, 4, tutorial.get_url().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 5, tutorial.get_title().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 6, tutorial.get_presenter().c_str(), -1, SQLITE_TRANSIENT);

    int stepResult = sqlite3_step(statement), rowsModified = sqlite3_changes(db);
    sqlite3_finalize(statement);

    if(stepResult != SQLITE_DONE){
        throw RepositoryException("Could not update tutorial in database!");
    }
    if(rowsModified == 0){
        throw RepositoryException("Tutorial not found!");
    }

    repo->update(tutorial);
}

int SQLiteRepository::find(const Tutorial& tutorial) const{
    return repo->find(tutorial);
}

void SQLiteRepository::likeTutorial(const Tutorial& tutorial){
    Tutorial newTutorial = tutorial;
    newTutorial.like();
    this->update(newTutorial);
}

vector<Tutorial> SQLiteRepository::getAll() const{
    return repo->getAll();
}

void SQLiteRepository::clear(){
    string sqlCode = R"(DELETE FROM TUTORIALS;)";

    sqlite3_stmt *statement;
    sqlite3_prepare_v2(db, sqlCode.c_str(), -1, &statement, nullptr);

    int stepResult = sqlite3_step(statement);
    sqlite3_finalize(statement);

    if(stepResult != SQLITE_DONE){
        throw RepositoryException("Could not clear database!");
    }

    repo->clear();
}

void SQLiteRepository::open(){
    std::cout << "SQLiteRepository can't be opened!" << std::endl;
}

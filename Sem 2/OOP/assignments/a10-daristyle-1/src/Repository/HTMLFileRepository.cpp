#include "HTMLFileRepository.h"
#include <fstream>
#include <iostream>
#include <unistd.h>

HTMLFileRepository::HTMLFileRepository(string _filename): FileRepository(_filename){
}

void HTMLFileRepository::save() const{
    std::ofstream fout{this->filename};
    fout << "<!DOCTYPE html>\n"
         << "<html>\n"
         << "<head>\n"
         << "\t<title>Tutorials</title>\n"
         << "</head>\n"
         << "<body>\n"
         << R"(<table border="1">)" << '\n'
         << "\t<tr>\n"
         << "\t\t<td>Title</td>\n"
         << "\t\t<td>Presenter</td>\n"
         << "\t\t<td>Duration</td>\n"
         << "\t\t<td>Likes</td>\n"
         << "\t\t<td>Link</td>\n";

    for(const auto& tutorial: this->repo->getAll()){
        fout << "\t<tr>\n"
             << "\t\t<td>" << tutorial.get_title() << "</td>\n"
             << "\t\t<td>" << tutorial.get_presenter() << "</td>\n"
             << "\t\t<td>" << tutorial.get_duration() << "</td>\n"
             << "\t\t<td>" << tutorial.get_likes() << "</td>\n"
             << "\t\t<td><a href=\"" << tutorial.get_url() << "\">Link</a></td>\n"
             << "\t</tr>\n";
    }

    fout << "</table>\n"
         << "</body>\n"
         << "</html>";
}

void HTMLFileRepository::load(){
    this->repo->clear();
}

void HTMLFileRepository::open(){
    if(fork() == 0){
        execlp("firefox", "firefox", this->filename.c_str(), NULL);
        exit(1);
    }
}
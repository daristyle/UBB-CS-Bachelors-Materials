#include "Repository.h"
#include <string>

using namespace std;

void Repository::addSong(const Song& s)
{
	this->songs.push_back(s);
}

Song Repository::findByArtistAndTitle(const std::string& artist, const std::string& title)
{
	auto val = std::find_if(this->songs.begin(), this->songs.end(), [artist, title](const Song& s){
		return s.getArtist() == artist && s.getTitle() == title;
	});
	if (val != this->songs.end()){
		return *val;
	}
	return Song{};
}
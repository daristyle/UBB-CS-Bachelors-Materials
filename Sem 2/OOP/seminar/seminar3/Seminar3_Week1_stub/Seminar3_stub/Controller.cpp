#include "Controller.h"
#include <algorithm>
#include <vector>
#include <iterator>
#include <string>
#include <PlayList.h>
#include <ranges>

void Controller::addSongToRepository(const std::string& artist, const std::string& title, double minutes, double seconds, const std::string& source)
{
	Song s{ artist, title, Duration{minutes, seconds}, source };
	this->repo.addSong(s);
}

void Controller::addSongToPlaylist(const Song& song)
{
	this->playlist.add(song);
}

void Controller::addAllSongsByArtistToPlaylist(const std::string& artist)
{
	// get all the songs from the repository
	vector<Song> songs = this->repo.getSongs();
	for(const auto& s: songs | std::views::filter([artist](const Song& s) { return s.getArtist() == artist; }))
		this->playlist.add(s);
	// use STL algorithms and lambdas
}
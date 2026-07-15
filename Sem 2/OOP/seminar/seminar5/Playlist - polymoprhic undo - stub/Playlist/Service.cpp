#include "Service.h"
#include <algorithm>

#include "ActionRemove.h"
#include "ActionUpdate.h"
#include "FilePlaylist.h"
#include "RepositoryExceptions.h"
#include "Utils.h"

using namespace std;

void Service::addSongToRepository(const std::string& artist, const std::string& title, double minutes, double seconds, const std::string& source)
{
	Song s{ artist, title, Duration{minutes, seconds}, source };
	this->validator.validate(s);
	this->repo.addSong(s);

	this->undoStack.push(make_unique<ActionAdd>(s, repo));
	clear(this->redoStack);
}

void Service::removeSongFromRepository(const std::string & artist, const std::string & title)
{
	Song s = this->repo.findByArtistAndTitle(artist, title);
	this->repo.removeSong(s);

	this->undoStack.push(make_unique<ActionRemove>(s, repo));
	clear(this->redoStack);
}

void Service::updateSong(const Song& oldSong, const Song& newSong){
	this->repo.removeSong(oldSong);
	this->repo.addSong(newSong);

	this->undoStack.push(make_unique<ActionUpdate>(oldSong, newSong, repo));
	clear(this->redoStack);
}

void Service::addSongToPlaylist(const Song& song)
{
	if (this->playList == nullptr)
		return;
	this->playList->add(song);
}

void Service::addAllSongsByArtistToPlaylist(const std::string& artist)
{
	vector<Song> songs = this->repo.getSongs();
	int nSongs = static_cast<int>(count_if(songs.begin(), songs.end(),
		[artist](const Song& s)
		{
			return s.getArtist() == artist;
		}));

	vector<Song> songsByArtist(nSongs);
	copy_if(songs.begin(), songs.end(), songsByArtist.begin(),
		[artist](const Song& s)
		{
			return s.getArtist() == artist;
		});

	for (auto s : songsByArtist)
		this->playList->add(s);
}

void Service::startPlaylist()
{
	if (this->playList == nullptr)
		return;
	this->playList->play();
}

void Service::nextSongPlaylist()
{
	if (this->playList == nullptr)
		return;
	this->playList->next();
}

void Service::savePlaylist(const std::string& filename)
{
	if (this->playList == nullptr)
		return;

	this->playList->setFilename(filename);
	this->playList->writeToFile();
}

void Service::openPlaylist() const
{
	if (this->playList == nullptr)
		return;

	this->playList->displayPlaylist();
}

void Service::undo()
{
	if (this->undoStack.empty())
		throw runtime_error{"nothing to undo"};
	this->undoStack.top()->executeUndo();
	this->redoStack.push(std::move(this->undoStack.top()));
	this->undoStack.pop();
}

void Service::redo(){
	if (this->redoStack.empty())
		throw runtime_error{"nothing to redo"};
	this->redoStack.top()->executeRedo();
	this->undoStack.push(std::move(this->redoStack.top()));
	this->redoStack.pop();
}
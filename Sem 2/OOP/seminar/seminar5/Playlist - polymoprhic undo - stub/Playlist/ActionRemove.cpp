#include "ActionRemove.h"

ActionRemove::ActionRemove(Song s, Repository& r): deletedSong{s}, repo{r}{}

void ActionRemove::executeUndo(){
    repo.addSong(this->deletedSong);
}

void ActionRemove::executeRedo(){
    repo.removeSong(this->deletedSong);
}
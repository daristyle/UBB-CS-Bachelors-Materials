#include "ActionAdd.h"

void ActionAdd::executeUndo(){
    repo.removeSong(this->addedSong);
}

void ActionAdd::executeRedo(){
    repo.addSong(this->addedSong);
}

ActionAdd::ActionAdd(Song s, Repository& r): addedSong{s}, repo{r}{
}

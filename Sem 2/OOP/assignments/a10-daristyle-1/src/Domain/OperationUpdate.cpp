#include "OperationUpdate.h"

OperationUpdate::OperationUpdate(Tutorial _oldTutorial, Tutorial _newTutorial, InterfaceRepository *_repo): oldTutorial(_oldTutorial), newTutorial(_newTutorial), repo(_repo){
}

void OperationUpdate::undo(){
    this->repo->update(oldTutorial);
}

void OperationUpdate::redo(){
    this->repo->update(newTutorial);
}
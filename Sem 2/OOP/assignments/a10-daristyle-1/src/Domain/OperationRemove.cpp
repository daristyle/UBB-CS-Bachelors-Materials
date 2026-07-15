#include "OperationRemove.h"

OperationRemove::OperationRemove(Tutorial _tutorial, InterfaceRepository *_repo): tutorial(_tutorial), repo(_repo){
}

void OperationRemove::undo(){
    repo->add(tutorial);
}

void OperationRemove::redo(){
    repo->remove(tutorial);
}
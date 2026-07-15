#include "OperationAdd.h"

OperationAdd::OperationAdd(Tutorial _tutorial, InterfaceRepository *_repo): tutorial(_tutorial), repo(_repo){
}

void OperationAdd::undo(){
    repo->remove(tutorial);
}

void OperationAdd::redo(){
    repo->add(tutorial);
}
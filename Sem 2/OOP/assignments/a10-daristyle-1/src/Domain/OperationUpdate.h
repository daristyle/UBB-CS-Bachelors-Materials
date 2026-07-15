#pragma once

#include <memory>

#include "InterfaceRepository.h"
#include "Operation.h"
#include "Tutorial.h"

class OperationUpdate : public Operation {
private:
    Tutorial oldTutorial, newTutorial;
    InterfaceRepository* repo;

public:
    OperationUpdate(Tutorial _oldTutorial, Tutorial _newTutorial, InterfaceRepository* _repo);

    void undo() override;
    void redo() override;

    ~OperationUpdate() override = default;
};

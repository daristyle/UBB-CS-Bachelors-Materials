#pragma once

#include <memory>

#include "InterfaceRepository.h"
#include "Operation.h"
#include "Tutorial.h"

class OperationRemove : public Operation {
private:
    Tutorial tutorial;
    InterfaceRepository* repo;

public:
    OperationRemove(Tutorial _tutorial, InterfaceRepository* _repo);

    void undo() override;
    void redo() override;

    ~OperationRemove() override = default;
};

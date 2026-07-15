#pragma once

#include <memory>

#include "InterfaceRepository.h"
#include "Operation.h"
#include "Tutorial.h"

class OperationAdd : public Operation {
private:
    Tutorial tutorial;
    InterfaceRepository* repo;

public:
    OperationAdd(Tutorial _tutorial, InterfaceRepository* _repo);

    void undo() override;
    void redo() override;

    ~OperationAdd() override = default;
};

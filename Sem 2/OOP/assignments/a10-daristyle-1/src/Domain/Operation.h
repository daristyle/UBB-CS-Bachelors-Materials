#pragma once

class Operation {
public:
    virtual void undo() = 0;
    virtual void redo() = 0;

    virtual ~Operation() = default;
};
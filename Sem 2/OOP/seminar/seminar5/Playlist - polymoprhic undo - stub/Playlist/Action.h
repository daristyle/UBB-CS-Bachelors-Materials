#pragma once

class Action {
public:
    virtual void executeUndo() = 0;
    virtual void executeRedo() = 0;

    virtual ~Action() = default;
};
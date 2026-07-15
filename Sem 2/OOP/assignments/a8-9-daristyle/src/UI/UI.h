#pragma once

#include "Service.h"

class UI {
protected:
    Service service;

public:
    UI(InterfaceRepository* _repository = new MemoryRepository(), InterfaceRepository* _watchlist = new MemoryRepository());

    virtual void run() = 0;

    virtual ~UI() = default;
};
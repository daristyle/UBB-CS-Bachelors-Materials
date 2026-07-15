#pragma once

#include "FileRepository.h"

class HTMLFileRepository: public FileRepository{
protected:
    void save() const override;
    void load() override;

public:
    HTMLFileRepository(string _filename);
    ~HTMLFileRepository() override = default;

    void open() override;
};
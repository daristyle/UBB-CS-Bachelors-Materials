#pragma once

#include <vector>
#include "FileRepository.h"
#include "MemoryRepository.h"
#include "Tutorial.h"

using std::vector, std::string;

class TextFileRepository: public FileRepository{
protected:
    void save() const override;
    void load() override;

public:
    TextFileRepository(string _filename);
    ~TextFileRepository() override = default;

    void open() override;
};

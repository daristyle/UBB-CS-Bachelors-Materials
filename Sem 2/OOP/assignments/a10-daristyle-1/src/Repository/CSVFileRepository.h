#pragma once

#include "FileRepository.h"

class CSVFileRepository: public FileRepository{
protected:
    void save() const override;
    void load() override;

public:
    CSVFileRepository(string _filename);
    ~CSVFileRepository() override = default;

    void open() override;
};
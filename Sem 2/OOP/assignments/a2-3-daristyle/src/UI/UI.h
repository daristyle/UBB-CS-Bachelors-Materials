#pragma once

#include "../Services/service.h"

#define DEBUG 0

typedef struct{
    service* service;
}UI;

UI* createUI();
void run(UI* ui);
void destroyUI(UI* ui);
#include <stdio.h>
#include "UI/UI.h"
#include "Tests/tests.h"

#define TESTING 0

int main(){
    if(TESTING){
        testAll();
        puts("All tests passed!");
        return 0;
    }
    UI* ui = createUI();
    run(ui);
    destroyUI(ui);
    return 0;
}
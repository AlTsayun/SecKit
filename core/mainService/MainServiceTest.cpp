//
// Created by RedmiBook on 14.12.2020.
//

#include "MainService.h"
int main(){
    auto *mainService = MainService::getInstance();
    auto * records = mainService->findRecordsBySearchQuery("search");

    return 0;
}
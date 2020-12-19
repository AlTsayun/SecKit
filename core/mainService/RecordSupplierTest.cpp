//
// Created by RedmiBook on 14.12.2020.
//

#include <iostream>
#include "RecordSupplier.h"
int main(){
    auto *mainService = MainService::getInstance();
    for (auto *record : *mainService->findRecordsBySearchQuery("name")){
        record->manipulate("application:app");
        mainService->saveRecord(record);
        std::cout << record->getInfo();

    }
    for (auto folder : *mainService->findFoldersBySearchQuery("")){
        std::cout << folder << std::endl;
    }
    for (auto *typeInfo : *mainService->findTypesBySearchQuery("")){
        std::cout << typeInfo->getName() << std::endl;
    }

    return 0;
}
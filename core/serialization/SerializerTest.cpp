//
// Created by RedmiBook on 12.12.2020.
//

#include <deque>
#include <iostream>
#include "Serializer.h"
#include "../record/PasswordRecord.h"

int main(){
//    auto* record = new PasswordRecord();
//    record->initialize("{\"id\":1,\"name\":\"name\",\"url\":\"url\",\"application\":\"application\",\"login\":\"login\",\"password\":\"password\",\"note\":\"note\"}");
//
//    auto * entryDeque = new std::deque<Record*>();
//    entryDeque->push_front(record);
//
//    auto *typeIdentifierToEntryConstructor = new std::unordered_map<std::string, Record::RecordConstructor>();
//
//    Record::RecordConstructor constructor = [](){return (Record*) new PasswordRecord();};
//    typeIdentifierToEntryConstructor->insert(std::make_pair("simple_password", constructor));
//
//    auto *serializer = new Serializer(typeIdentifierToEntryConstructor);
//    std::string data = serializer->serialize(entryDeque);
//    delete(entryDeque);
//    std::cout << data;
//    entryDeque = serializer->deserialize(data);
    return 0;
}
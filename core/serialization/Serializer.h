//
// Created by RedmiBook on 11.12.2020.
//

#ifndef SECKIT_SERIALIZER_H
#define SECKIT_SERIALIZER_H


#include <string>
#include <list>
#include <unordered_map>
#include "../record/Record.h"

class Serializer {
private:
    static const std::string delimiter;
    std::unordered_map<std::string, Record::RecordConstructor>* typeIdentifierToRecordConstructor;
public:

    explicit Serializer(std::unordered_map<std::string, Record::RecordConstructor>* typeIdentifierToEntryConstructor);
    std::string serialize(std::deque<Record*>*);
    std::deque<Record*>* deserialize(std::string);
};


#endif //SECKIT_SERIALIZER_H

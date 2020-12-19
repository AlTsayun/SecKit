//
// Created by RedmiBook on 11.12.2020.
//

#include <sstream>
#include <deque>
#include "Serializer.h"

const std::string Serializer::delimiter = ";";

std::string Serializer::serialize(std::deque<Record*>* records){
    std::ostringstream oss;
    for(Record* record : *records){
        auto typeIdentifier =  record->getTypeInfo()->getIdentifier();
        auto serializationData = record->getSerializationData();
        oss << typeIdentifier
            << delimiter
            << serializationData
            << delimiter;
    }
    return oss.str();
}

std::deque<Record*>* Serializer::deserialize(std::string input) {
    size_t tokenPos = 0;
    size_t dataPos = 0;

    std::string token;
    std::string data;

    auto *items = new std::deque<Record*>();

    while ((tokenPos = input.find(delimiter)) != std::string::npos) {
        token = input.substr(0, tokenPos);
        input.erase(0, tokenPos + delimiter.length());

        //Reading from string
        dataPos = input.find(delimiter);
        if (dataPos == std::string::npos) throw;
        data = input.substr(0, dataPos);
        input.erase(0, dataPos + delimiter.length());

        bool isSerialized = false;
        std::vector<std::string> keys;

        //todo:replace for-loop with find on map
        for (const auto& pair: *typeIdentifierToRecordConstructor)
            keys.push_back(pair.first);

        for (const auto& key : keys)
        {
            if(token.compare(key) == 0) {
                auto *item = typeIdentifierToRecordConstructor->at(key)();
                item->initialize(data);
                items->push_back(item);
                isSerialized = true;
                break;
            }
        }

        if (!isSerialized) throw;

    }
    return items;
}

Serializer::Serializer(std::unordered_map<std::string, Record::RecordConstructor> *typeIdentifierToEntryConstructor) {
    this->typeIdentifierToRecordConstructor = typeIdentifierToEntryConstructor;
}

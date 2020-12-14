//
// Created by RedmiBook on 10.12.2020.
//

#include "Record.h"

const std::string &RecordTypeInfo::getIdentifier() const {
    return identifier;
}

const std::string &RecordTypeInfo::getName() const {
    return name;
}

const std::string &RecordTypeInfo::getDescription() const {
    return description;
}

Record::RecordConstructor RecordTypeInfo::getConstructor() const {
    return constructor;
}

const std::string &RecordTypeInfo::getSearchMeta() const {
    return searchMeta;
}

RecordTypeInfo::RecordTypeInfo(const std::string &identifier,
                               const std::string &name,
                               const std::string &description,
                               const Record::RecordConstructor &constructor,
                               const std::string &searchMeta)
        :
        identifier(identifier),
        name(name),
        description(description),
        constructor(constructor),
        searchMeta(searchMeta){}

std::string Record::getId() {
    return id;
}

void Record::setId(std::string idParam) {
    this->id = idParam;
}


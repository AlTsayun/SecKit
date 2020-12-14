//
// Created by RedmiBook on 11.12.2020.
//

#include "PasswordRecord.h"
#include <google/protobuf/util/json_util.h>


std::string PasswordRecord::getSearchMeta() {
    return protoItem->name();
}

void PasswordRecord::manipulate(std::string input) {
//    protoItem->se
}

void PasswordRecord::initialize(std::string data) {
    google::protobuf::util::JsonStringToMessage(data, protoItem);
}

std::string PasswordRecord::getSerializationData() {
    std::string res;
    google::protobuf::util::MessageToJsonString(*protoItem, &res);
    return res;
}

PasswordRecord::PasswordRecord() {
    protoItem = new serialization::Password();
}

std::string PasswordRecord::getFolder() {
    return protoItem->folder();
}

std::string PasswordRecord::getInfo() {
    //todo: implement getInfo()
    return "not implemented getInfo function!!!";
}


RecordTypeInfo *PasswordRecord::typeInfo = new RecordTypeInfo("simple_password",
                                                              "Password",
                                                              "Stores simple pair of login and password for web-site/application",
                                                              [](){return (Record*) new PasswordRecord();},
                                                              "searchMeta");

PasswordRecord::~PasswordRecord() {

}

RecordTypeInfo * PasswordRecord::getTypeInfo() {
    return typeInfo;
}

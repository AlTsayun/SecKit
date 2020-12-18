//
// Created by RedmiBook on 11.12.2020.
//

#include "PasswordRecord.h"
#include <google/protobuf/util/json_util.h>
#include <sstream>
#include <iomanip>


const std::string PasswordRecord::delimiter = ":";

std::string PasswordRecord::getSearchMeta() {
    return protoItem->name();
}

void PasswordRecord::manipulate(std::string input) {

    size_t tokenPos;
    std::string token;
    if ((tokenPos = input.find(delimiter)) != std::string::npos){
        token = input.substr(0, tokenPos);
        input.erase(0, tokenPos + delimiter.length());

        if(token == "login") {
            protoItem->set_login(input);
        }else if(token == "name"){
            protoItem->set_name(input);
        }else if(token == "url"){
            protoItem->set_url(input);
        }else if(token == "folder"){
            protoItem->set_folder(input);
        }else if(token == "application"){
            protoItem->set_application(input);
        }else if(token == "note"){
            protoItem->set_note(input);
        }else if(token == "password"){
            protoItem->set_password(input);
        } else{
            *lastOperationInfo << "Unknown command: \"" << input << "\"" << std::endl;
        }

    } else {
        if (input == "show"){
            isPasswordShown = true;
        } else {
            *lastOperationInfo << "Unknown command: \"" << input << "\"" << std::endl;
        }
    }
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
    std::ostringstream oss;

    oss << lastOperationInfo->str() << std::endl
    <<std::setw(15) << std::right << "name: " << protoItem->name() << std::endl
    <<std::setw(15) << std::right << "url: " << protoItem->url() << std::endl
    <<std::setw(15) << std::right << "application: " << protoItem->application() << std::endl
    <<std::setw(15) << std::right << "folder: " << protoItem->folder() << std::endl
    <<std::setw(15) << std::right << "login: " << protoItem->login() << std::endl
    <<std::setw(15) << std::right << "password: " << (isPasswordShown ? protoItem->password() : std::string(protoItem->password().length(), '*')) << std::endl
    <<std::setw(15) << std::right << "note: " << std::endl << protoItem->note() << std::endl
    ;

    lastOperationInfo->clear();

    return oss.str();
}


RecordTypeInfo *PasswordRecord::typeInfo = new RecordTypeInfo("simple_password",
                                                              "Password",
                                                              "Stores simple pair of login and password for web-site/application",
                                                              [](){return (Record*) new PasswordRecord();},
                                                              "simple password login url");

PasswordRecord::~PasswordRecord() {

}

RecordTypeInfo * PasswordRecord::getTypeInfo() {
    return typeInfo;
}

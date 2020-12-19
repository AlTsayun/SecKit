//
// Created by RedmiBook on 19.12.2020.
//

#include "AddressRecord.h"

//
// Created by RedmiBook on 11.12.2020.
//
#include <google/protobuf/util/json_util.h>
#include <sstream>
#include <iomanip>


const std::string AddressRecord::delimiter = ":";

std::string AddressRecord::getSearchMeta() {
    return protoItem->name();
}

void AddressRecord::manipulate(std::string input) {

    size_t tokenPos;
    std::string token;
    if ((tokenPos = input.find(delimiter)) != std::string::npos){
        token = input.substr(0, tokenPos);
        input.erase(0, tokenPos + delimiter.length());

        if(token == "name") {
            protoItem->set_name(input);
        }else if(token == "country"){
            protoItem->set_country(input);
        }else if(token == "region"){
            protoItem->set_region(input);
        }else if(token == "locality"){
            protoItem->set_locality(input);
        }else if(token == "building"){
            protoItem->set_building(input);
        }else if(token == "apartment"){
            protoItem->set_apartment(input);
        }else if(token == "postindex"){
            protoItem->set_postindex(input);
        }else if(token == "note"){
            protoItem->set_note(input);
        }else if(token == "folder"){
            protoItem->set_folder(input);
        } else{
            *lastOperationInfo << "Unknown token: \"" << token << "\"" << std::endl;
        }

    } else {
        *lastOperationInfo << "Unknown command: \"" << input << "\"" << std::endl;
    }
}

void AddressRecord::initialize(std::string data) {
    google::protobuf::util::JsonStringToMessage(data, protoItem);
}

std::string AddressRecord::getSerializationData() {
    std::string res;
    google::protobuf::util::MessageToJsonString(*protoItem, &res);
    return res;
}

AddressRecord::AddressRecord() {
    protoItem = new serialization::Address();
    protoItem->set_name("<new address>");
}

std::string AddressRecord::getFolder() {
    return protoItem->folder();
}

std::string AddressRecord::getInfo() {
    std::ostringstream oss;

    oss << lastOperationInfo->str() << std::endl
        <<std::setw(15) << std::right << "name: " << protoItem->name() << std::endl
        <<std::setw(15) << std::right << "country: " << protoItem->country() << std::endl
        <<std::setw(15) << std::right << "region: " << protoItem->region() << std::endl
        <<std::setw(15) << std::right << "locality: " << protoItem->locality() << std::endl
        <<std::setw(15) << std::right << "building: " << protoItem->building() << std::endl
        <<std::setw(15) << std::right << "apartment: " << protoItem->apartment() << std::endl
        <<std::setw(15) << std::right << "post index: " << protoItem->postindex() << std::endl
        <<std::setw(15) << std::right << "note: " << protoItem->note() << std::endl << std::endl
        <<std::setw(15) << std::right << "folder: " << protoItem->folder() << std::endl
        ;

    lastOperationInfo->str("");
    lastOperationInfo->clear();

    return oss.str();
}


RecordTypeInfo *AddressRecord::typeInfo = new RecordTypeInfo("simple_address",
                                                              "Address",
                                                              "Stores information about some place, building, neighborhood etc.",
                                                              [](){return (Record*) new AddressRecord();},
                                                              "simple address place post");

AddressRecord::~AddressRecord() {

}

RecordTypeInfo * AddressRecord::getTypeInfo() {
    return typeInfo;
}

std::string AddressRecord::getName() {
    return protoItem->name();
}

//
// Created by RedmiBook on 19.12.2020.
//

#ifndef SECKIT_ADDRESSRECORD_H
#define SECKIT_ADDRESSRECORD_H

#include <sstream>
#include "Record.h"
#include "../serialization/generated/address.pb.h"

class AddressRecord  : public Record {
private:
    serialization::Address* protoItem;
    static const std::string delimiter;
public:
    static RecordTypeInfo* typeInfo;

    RecordTypeInfo * getTypeInfo() override;

    AddressRecord();
    std::string getSearchMeta() override;
    void manipulate(std::string input) override;
    void initialize(std::string data) override;
    std::string getSerializationData() override;
    std::string getFolder() override;
    std::string getInfo() override;

    std::string getName() override;

    ~AddressRecord() override;

    std::ostringstream *lastOperationInfo= new std::ostringstream();
};


#endif //SECKIT_ADDRESSRECORD_H

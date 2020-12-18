//
// Created by RedmiBook on 11.12.2020.
//

#ifndef SECKIT_PASSWORDRECORD_H
#define SECKIT_PASSWORDRECORD_H

#include <sstream>
#include "Record.h"
#include "../serialization/generated/password.pb.h"

class PasswordRecord : public Record {
private:
    serialization::Password* protoItem;
    static RecordTypeInfo* typeInfo;
    static const std::string delimiter;
    bool isPasswordShown = false;
public:
    RecordTypeInfo * getTypeInfo() override;

    PasswordRecord();
    std::string getSearchMeta() override;
    void manipulate(std::string input) override;
    void initialize(std::string data) override;
    std::string getSerializationData() override;
    std::string getFolder() override;
    std::string getInfo() override;

    ~PasswordRecord() override;

    std::ostringstream *lastOperationInfo= new std::ostringstream();
};


#endif //SECKIT_PASSWORDRECORD_H

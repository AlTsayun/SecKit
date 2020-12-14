//
// Created by RedmiBook on 10.12.2020.
//

#ifndef SECKIT_RECORD_H
#define SECKIT_RECORD_H


#include <string>

class RecordTypeInfo;

class Record {
protected:
    std::string id;
public:
    typedef Record* (*RecordConstructor) ();

    virtual RecordTypeInfo* getTypeInfo() = 0;

    virtual std::string getSearchMeta() = 0;
    virtual std::string getId();
    virtual void setId(std::string idParam);
    virtual void manipulate(std::string input) = 0;
    virtual void initialize(std::string data) = 0;
    virtual std::string getSerializationData() = 0;
    virtual std::string getInfo() = 0;
    virtual std::string getFolder() = 0;

    virtual ~Record() = default;
};


class RecordTypeInfo {
private:
    const std::string identifier;
    const std::string name;
    const std::string description;
    const Record::RecordConstructor constructor;
    const std::string searchMeta;
public:
    const std::string &getIdentifier() const;

    const std::string &getName() const;

    const std::string &getDescription() const;

    Record::RecordConstructor getConstructor() const;

    const std::string &getSearchMeta() const;

    RecordTypeInfo(const std::string &identifier,
                   const std::string &name,
                   const std::string &description,
                   const Record::RecordConstructor &constructor,
                   const std::string &searchMeta);
};


#endif //SECKIT_RECORD_H

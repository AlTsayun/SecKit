//
// Created by RedmiBook on 12.12.2020.
//

#ifndef SECKIT_MAINSERVICE_H
#define SECKIT_MAINSERVICE_H


#include <deque>
#include <string>
#include <map>
#include "../record/Record.h"

class MainService {
private:
    std::map<std::string, RecordTypeInfo*>* idToRecordTypeInfo;
    std::multimap<std::string, RecordTypeInfo*>* searchMetaToRecordTypeInfo;
    std::map<std::string, Record*>* idToRecord;
    std::multimap<std::string, Record*>* searchMetaToRecord;
    std::multimap<std::string, Record*>* folderToRecord;

    template<typename K, typename V>
    static void removeSinglePairFromMultimap(std::multimap<K,V>* mmap, std::pair<K, V> mapPair);

    template<typename K, typename V>
    static std::deque<V>* getFromMultimap(std::multimap<K,V>* mmap, K key);

    template<typename V>
    static std::deque<V>* searchInMultimap(std::multimap<std::string,V>* mmap, std::string searchQuery);

    template<typename V>
    static std::deque<V>* searchValuesInMap(std::map<std::string,V>* map, std::string searchQuery);

    template<typename V>
    static std::deque<std::string>* searchKeysInMultiMap(std::multimap<std::string, V> *mmap, std::string searchQuery);

    template<typename K, typename V>
    static std::deque<K>* getKeysFromMultiMap(std::multimap<K, V> *mmap);

    template<typename K, typename V>
    static std::deque<V>* getValuesFromMultiMap(std::multimap<K, V> *mmap);

    template<typename K, typename V>
    static std::deque<K>* getKeysFromMap(std::map<K, V> *map);

    template<typename K, typename V>
    static std::deque<V>* getValuesFromMap(std::map<K, V> *map);


    static bool searchSubstring(const std::string & strHaystack, const std::string & strNeedle);

    void addRecord(Record *record);
    void addTypeInfo(RecordTypeInfo* typeInfo);

    void updateSearchMetaToRecord();
    void updateFolderToRecord();


    static MainService *instance;
    MainService();
public:
    MainService(MainService &other) = delete;
    void operator=(const MainService &) = delete;
    static MainService* getInstance();

    Record* getRecordById(std::string id);
    std::deque<Record *> * getAllRecords();
    void removeRecordById(std::string id);
    std::deque<Record*>* findRecordsBySearchQuery(std::string searchQuery);


    std::deque<std::string> *getAllFolders();
    std::deque<std::string>* findFoldersBySearchQuery(std::string searchQuery);
    std::deque<Record*>* getRecordsByFolder(std::string folder);

    std::deque<RecordTypeInfo *> *getAllRecordTypeInfos();
    RecordTypeInfo * getTypeInfoById(std::string typeIdentifier);
    std::deque<RecordTypeInfo*>* findTypesBySearchQuery(std::string searchQuery);
    void saveRecord(Record* record);

    void loadFile(std::string pathToFile, std::string password);
    void saveFile(std::string pathToFile, std::string password);

};


#endif //SECKIT_MAINSERVICE_H

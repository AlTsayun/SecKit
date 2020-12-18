//
// Created by RedmiBook on 12.12.2020.
//

#include <algorithm>
#include "MainService.h"
#include "../record/PasswordRecord.h"

MainService* MainService::getInstance() {
    if(instance== nullptr){
        instance = new MainService();
    }
    return instance;
}
MainService* MainService::instance= nullptr;

Record *MainService::getRecordById(std::string id) {
    return idToRecord->at(id);
}

std::deque<Record *> *MainService::findRecordsBySearchQuery(std::string searchQuery) {
    return searchInMultimap(searchMetaToRecord,searchQuery);
}

std::deque<std::string> *MainService::findFoldersBySearchQuery(std::string searchQuery) {
    return searchKeysInMultiMap(folderToRecord, searchQuery);
}

std::deque<Record *> *MainService::getRecordsByFolder(std::string folder) {
    return getFromMultimap(folderToRecord, folder);
}


std::deque<RecordTypeInfo *> *MainService::findTypesBySearchQuery(std::string searchQuery) {
    return searchInMultimap(searchMetaToRecordTypeInfo, searchQuery);
}

RecordTypeInfo * MainService::getTypeInfoById(std::string typeIdentifier) {
    return idToRecordTypeInfo->at(typeIdentifier);
}


std::deque<Record *> * MainService::getAllRecords() {
    return getValuesFromMap(idToRecord);
}

std::deque<std::string> * MainService::getAllFolders() {
    return getKeysFromMultiMap(folderToRecord);
}

std::deque<RecordTypeInfo *> * MainService::getAllRecordTypeInfos() {
    return getValuesFromMap(idToRecordTypeInfo);
}

void MainService::saveRecord(Record *record) {
    std::map<std::string, Record*>::iterator nameToRecordIterator;

    nameToRecordIterator = idToRecord->find(record->getSearchMeta());

    if(nameToRecordIterator != idToRecord->end()){
        //if exists
        auto tmp = nameToRecordIterator->second;
        if(tmp != record){
            //new item with existing id is being saved
            removeRecordById(tmp->getId());
            addRecord(record);
        } else {
            //important properties may be committed to save
            updateFolderToRecord();
            updateSearchMetaToRecord();
        }

        delete(tmp);
    } else {
        addRecord(record);
    };


}

template<typename K, typename V>
void MainService::removeSinglePairFromMultimap(std::multimap<K, V>* mmap, const std::pair<K, V> mapPair) {
    std::pair<typename std::multimap<K, V>::iterator, typename std::multimap<K, V>::iterator> iteratorBounds = mmap->equal_range(mapPair.first);

    typename std::multimap<K, V>::iterator it = iteratorBounds.first;
    for (; it != iteratorBounds.second; ++it) {
        if (it->second == mapPair.second) {
            mmap->erase(it);
            break;
        }
    }
}

template<typename K, typename V>
std::deque<V>* MainService::getFromMultimap(std::multimap<K, V> *mmap, K key) {
    auto* values = new std::deque<V>();
    auto iteratorBounds = mmap->equal_range(key);
    for (auto it = iteratorBounds.first; it != iteratorBounds.second; ++it){
        values->push_back(it->second);
    }
    return values;
}

template<typename V>
std::deque<V> *MainService::searchInMultimap(std::multimap<std::string, V> *mmap, std::string searchQuery) {
    auto* values = new std::deque<V>();
    for (auto pair: *mmap){
        if(searchSubstring(pair.first, searchQuery)){
            values->push_back(pair.second);
        }
    }
    return values;
}

template<typename V>
std::deque<V> *MainService::searchValuesInMap(std::map<std::string, V> *map, std::string searchQuery) {
    auto* values = new std::deque<V>();
    for (auto pair: *mmap){
        if(searchSubstring(pair.first, searchQuery)){
            values->push_back(pair.second);
        }
    }
    return values;
}

template<typename V>
std::deque<std::string> *MainService::searchKeysInMultiMap(std::multimap<std::string, V> *mmap, std::string searchQuery) {
    auto* keys = new std::deque<std::string>();

    for(auto it = mmap->begin(), end = mmap->end();
        it != end;
        it = mmap->upper_bound(it->first)){
        if (searchSubstring(it->first, searchQuery)){
            keys->push_back(it->first);
        }
    }
    return keys;
}

bool MainService::searchSubstring(const std::string & strHaystack, const std::string & strNeedle)
{
    auto it = std::search(
            strHaystack.begin(), strHaystack.end(),
            strNeedle.begin(),   strNeedle.end(),
            [](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); }
    );
    return (it != strHaystack.end() );
}

void MainService::removeRecordById(std::string id) {
    auto* record = idToRecord->at(id);
    removeSinglePairFromMultimap(searchMetaToRecord, std::make_pair(record->getSearchMeta(), record));
    removeSinglePairFromMultimap(folderToRecord, std::make_pair(record->getFolder(), record));
    idToRecord->erase(id);
    delete(record);
}

void MainService::saveFile(std::string pathToFile, std::string password) {

}

void MainService::loadFile(std::string pathToFile, std::string password) {
}

MainService::MainService() {
    idToRecordTypeInfo = new std::map<std::string, RecordTypeInfo*>;
    searchMetaToRecordTypeInfo = new std::multimap<std::string, RecordTypeInfo*>;

    idToRecord = new std::map<std::string, Record*>;
    searchMetaToRecord = new std::multimap<std::string, Record*>;

    folderToRecord= new std::multimap<std::string, Record*>;

    //todo: remove testing code
    /////////////////////////////////////////////////////////////////////////////
    auto *records = new std::deque<Record*>;

    Record* record = (Record*) new PasswordRecord();


    record->setId("1");
    record->manipulate("name:name1");
    record->manipulate("folder:name1");
    record->manipulate("password:password1");
    records->push_front(record);


    record = (Record*) new PasswordRecord();
    record->setId("2");
    record->manipulate("name:name2");
    record->manipulate("folder:name2");
    record->manipulate("password:2");
    records->push_front(record);

    /////////////////////////////////////////////////////////////////////////////
    //todo: remove testing code

    //todo: insert loading records from backup file
    for (auto * record : *records){
        addRecord(record);
    }

}

void MainService::addRecord(Record *record) {
    idToRecord->insert(std::make_pair(record->getId(), record));
    searchMetaToRecord->insert(std::make_pair(record->getSearchMeta(), record));

    folderToRecord->insert(std::make_pair(record->getFolder(), record));
}

void MainService::updateSearchMetaToRecord() {
    //todo: find replacement for std::make_pair for iterator
    std::multimap<std::string, Record*> toUpdate;
    for (auto it : *searchMetaToRecord) {
        if (it.first != it.second->getSearchMeta()){
            toUpdate.insert(std::make_pair(it.first, it.second));
        }
    }
    for (auto it: toUpdate){
        removeSinglePairFromMultimap(searchMetaToRecord, std::make_pair(it.first, it.second));
        searchMetaToRecord->insert(std::make_pair(it.second->getSearchMeta(), it.second));
    }
}


void MainService::updateFolderToRecord() {
    //todo: find replacement for std::make_pair for iterator
    std::multimap<std::string, Record*> toUpdate;
    for (auto it : *folderToRecord) {
        if (it.first != it.second->getFolder()){
            toUpdate.insert(std::make_pair(it.first, it.second));
        }
    }
    for (auto it: toUpdate){
        removeSinglePairFromMultimap(folderToRecord, std::make_pair(it.first, it.second));
        folderToRecord->insert(std::make_pair(it.second->getFolder(), it.second));
    }
}

void MainService::addTypeInfo(RecordTypeInfo * typeInfo) {
    if (idToRecordTypeInfo->find(typeInfo->getIdentifier()) != idToRecordTypeInfo->end()){
        idToRecordTypeInfo->insert(std::make_pair(typeInfo->getIdentifier(), typeInfo));
        searchMetaToRecordTypeInfo->insert(std::make_pair(typeInfo->getSearchMeta(), typeInfo));
    }
}

template<typename K, typename V>
std::deque<K> *MainService::getKeysFromMultiMap(std::multimap<K, V> *mmap) {
    auto* keys = new std::deque<K>();

    for(auto it = mmap->begin(), end = mmap->end();
        it != end;
        it = mmap->upper_bound(it->first)){
        keys->push_back(it->first);
    }
    return keys;
}

template<typename K, typename V>
std::deque<V> *MainService::getValuesFromMultiMap(std::multimap<K, V> *mmap) {
    auto* values = new std::deque<V>();

    for(auto it = mmap->begin(), end = mmap->end();
        it != end;
        ++it){
        values->push_back(it->second);
    }
    return values;
}

template<typename K, typename V>
std::deque<K> *MainService::getKeysFromMap(std::map<K, V> *map) {
    auto* keys = new std::deque<K>();

    for(auto it = map->begin(), end = map->end();
        it != end;
        ++it){
        keys->push_back(it->first);
    }
    return keys;
}

template<typename K, typename V>
std::deque<V> *MainService::getValuesFromMap(std::map<K, V> *map) {
    auto* values = new std::deque<V>();

    for(auto it = map->begin(), end = map->end();
        it != end;
        ++it){
        values->push_back(it->second);
    }
    return values;
}

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

std::deque<RecordTypeInfo *> *MainService::findTypesBySearchQuery(std::string searchQuery) {
    return searchInMultimap(searchMetaToRecordTypeInfo, searchQuery);
}

RecordTypeInfo * MainService::getTypeInfoById(std::string typeIdentifier) {
    return idToRecordTypeInfo->at(typeIdentifier);
}

void MainService::save(Record *record) {
//    bool isPresent = false;
//    std::map<std::string, Record*>::iterator nameToRecordIterator;
//
//    nameToRecordIterator = idToRecord->find(record->getSearchMeta());
//    isPresent = nameToRecordIterator != idToRecord->end();
//
//    if(!isPresent){
//        auto tmp = nameToRecordIterator->second;
//        nameToRecordIterator->second = record;
//
//
////        std::pair<std::multimap<std::string, Record*>::iterator, std::multimap<std::string, Record*>::iterator> folderToRecordIteratorPair = folderToRecord->equal_range(tmp->getFolder());
////
////        std::multimap<std::string, Record*>::iterator folderToRecordIterator = folderToRecordIteratorPair.first;
////        for (; folderToRecordIterator != folderToRecordIteratorPair.second; ++folderToRecordIterator) {
////            if (folderToRecordIterator->second == tmp) {
////                folderToRecord->erase(folderToRecordIterator);
////                break;
////            }
////        }
//
//        removeSinglePairFromMultimap(folderToRecord, std::make_pair(tmp->getFolder(), tmp));
//        folderToRecord->insert(std::make_pair(record->getFolder(), record));
//
//        delete(tmp);
//    }


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

std::deque<Record *> *MainService::getRecordsByFolder(std::string folder) {
    return getFromMultimap(folderToRecord, folder);
}

template<typename K, typename V>
std::deque<V>* MainService::getFromMultimap(std::multimap<K, V> *mmap, K key) {
    auto* values = new std::deque<V>();
    auto iteratorBounds = mmap->equal_range(key);
    for (auto it = iteratorBounds.first; it != iteratorBounds.second; ++it){
        values->push_front(it->second);
    }
    return values;
}

template<typename V>
std::deque<V> *MainService::searchInMultimap(std::multimap<std::string, V> *mmap, std::string searchQuery) {
    auto* values = new std::deque<V>();
    for (auto pair: *mmap){
        if(searchSubstring(pair.first, searchQuery)){
            values->push_front(pair.second);
        }
    }
    return values;
}

template<typename V>
std::deque<V> *MainService::searchValuesInMap(std::map<std::string, V> *map, std::string searchQuery) {
    auto* values = new std::deque<V>();
    for (auto pair: *mmap){
        if(searchSubstring(pair.first, searchQuery)){
            values->push_front(pair.second);
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
        keys->push_front(it->first);
    }
    keys->erase(std::remove_if(keys->begin(), keys->end(),
                          [searchQuery](std::string str){
        return searchSubstring(str, searchQuery);
    }));
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

void MainService::removeRecordById(std::string name) {

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



    auto *records = new std::deque<Record*>;

    Record* record = (Record*) new PasswordRecord();

    record->setId("1");
    records->push_front(record);

    record = (Record*) new PasswordRecord();
    record->setId("2");
    records->push_front(record);

    for (auto * record : *records){
        auto *recordTypeInfo = record->getTypeInfo();
        idToRecordTypeInfo->insert(std::make_pair(recordTypeInfo->getIdentifier(), recordTypeInfo));
        searchMetaToRecordTypeInfo->insert(std::make_pair(recordTypeInfo->getSearchMeta(), recordTypeInfo));

        idToRecord->insert(std::make_pair(record->getId(), record));
        searchMetaToRecord->insert(std::make_pair(record->getSearchMeta(), record));

        folderToRecord->insert(std::make_pair(record->getFolder(), record));
    }

}

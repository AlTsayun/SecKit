cmake_minimum_required(VERSION 3.17)
project(SecKit)

set(CMAKE_CXX_STANDARD 14)


set(INCLUDE_DIRS)
set(LIBRARIES)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(cryptlib REQUIRED)
add_executable(SecKit #[[main.cpp]] core/Encryption/EncryptorTest.cpp core/Encryption/Encryptor.cpp core/Encryption/Encryptor.h core/Entry/Entry.cpp core/Entry/Entry.h)


message("include dirs: ${INCLUDE_DIRS}")
message("libraries: ${LIBRARIES}")

include_directories(${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})


#include_directories(${CRYPTLIB_INCLUDE_DIR})
#target_link_libraries(${PROJECT_NAME} ${CRYPTLIB_LIBRARY})
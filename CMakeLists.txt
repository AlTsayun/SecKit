cmake_minimum_required(VERSION 3.17)
project(SecKit)

set(CMAKE_CXX_STANDARD 14)

set(INCLUDE_DIRS)
set(LIBRARIES)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")


set(CMAKE_WIN32_EXECUTABLE true)

find_package(cryptlib REQUIRED)
find_package(libprotobuf REQUIRED)
add_executable(SecKit
        core/encryption/Encryptor.cpp
        core/encryption/Encryptor.h

        core/record/PasswordRecord.cpp
        core/record/PasswordRecord.h

        core/record/Record.cpp
        core/record/Record.h

        core/serialization/Serializer.cpp
        core/serialization/Serializer.h
#        core/serialization/SerializerTest.cpp

        core/serialization/generated/password.pb.cc
        core/serialization/generated/password.pb.h

        core/mainService/MainService.cpp
        core/mainService/MainService.h
#        core/mainService/MainServiceTest.cpp

        winapi/MainWindowController.cpp
        winapi/MainWindowController.h

        framework.h
        main.cpp
        winapi/styles.h)

message("include dirs: ${INCLUDE_DIRS}")
message("libraries: ${LIBRARIES}")

include_directories(${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
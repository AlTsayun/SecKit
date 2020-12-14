set(LIB_NAME "libprotobufd")
set(LIB_DIR "D:/workspace/osasp/protobuf-3.14.0")

set(LIB_INCLUDE_DIR ${LIB_DIR}/src)
set(LIB_PATH_SUFFIXES "/cmake/cmake-build-debug")


message("loading ${LIB_NAME}")
unset(LIB_VAR CACHE)

message("LIB_VAR: ${LIB_VAR}")

find_library(LIB_VAR
        NAMES
        ${LIB_NAME}
        PATHS
        ${LIB_DIR}
        PATH_SUFFIXES
        ${LIB_PATH_SUFFIXES}
        )

message("LIB_VAR: ${LIB_VAR}")
if(NOT LIB_VAR)
    message(SEND_ERROR "error loading ${LIB_NAME}")
else()
    message("${LIB_NAME} is found")

    list(APPEND INCLUDE_DIRS ${LIB_INCLUDE_DIR})
    list(APPEND LIBRARIES ${LIB_VAR})
endif()

unset(LIB_DIR CACHE)
unset(LIB_INCLUDE_DIR CACHE)
unset(LIB_PATH_SUFFIXES CACHE)
unset(LIB_VAR CACHE)
unset(LIB_NAME CACHE)
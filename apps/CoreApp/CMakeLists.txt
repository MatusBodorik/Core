cmake_minimum_required(VERSION 3.0)
project(CoreApp VERSION "0.1")
set(PROJECT_DESCRIPTION "CoreApp for project FleXd")

message(STATUS "***" )
message(STATUS "* " ${PROJECT_NAME})
message(STATUS "***")

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "setting default value 'Debug' for CMAKE_BUILD_TYPE")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

include(FindPkgConfig)
find_package(PkgConfig REQUIRED)
pkg_search_module(JSON_PARSER REQUIRED jsonParser)
if (JSON_PARSER_FOUND)
    message(STATUS "JSON_PARSER libs was found: " ${JSON_PARSER_LIBRARIES})
    message(STATUS "JSON_PARSER inc was found: " ${JSON_PARSER_INCLUDE_DIRS})
endif (JSON_PARSER_FOUND)

pkg_search_module(libsqlite3-dev REQUIRED sqlite3)
if (libsqlite3-dev_FOUND)
    message(STATUS "SQLITE3 libs was found: " ${libsqlite3-dev_LIBRARIES})
    message(STATUS "SQLITE3 inc was found: " ${libsqlite3-dev_INCLUDE_DIRS})
endif (libsqlite3-dev_FOUND)

pkg_search_module(FLEXD_LOGGER REQUIRED fleXdLoggerClient)
if (FLEXD_LOGGER_FOUND)
    message(STATUS "FLEXD_LOGGER libs was found: " ${FLEXD_LOGGER_LIBRARIES})
    message(STATUS "FLEXD_LOGGER inc was found: " ${FLEXD_LOGGER_INCLUDE_DIRS})
endif (FLEXD_LOGGER_FOUND)

pkg_search_module(FLEXD_EPOLL REQUIRED fleXdEpoll)
if (FLEXD_EPOLL_FOUND)
    message(STATUS "FLEXD_EPOLL libs was found: " ${FLEXD_EPOLL_LIBRARIES})
    message(STATUS "FLEXD_EPOLL inc was found: " ${FLEXD_EPOLL_INCLUDE_DIRS})
endif (FLEXD_EPOLL_FOUND)

pkg_search_module(FLEXD_CONECTOR REQUIRED fleXdIPCConnector)
if (FLEXD_CONECTOR_FOUND)
    message(STATUS "FLEXD_CONECTOR libs was found: " ${FLEXD_CONECTOR_LIBRARIES})
    message(STATUS "FLEXD_CONECTOR inc was found: " ${FLEXD_CONECTOR_INCLUDE_DIRS})
endif (FLEXD_CONECTOR_FOUND)

pkg_search_module(FLEXD_IPCCOMMON REQUIRED fleXdIPCCommon)
if (FLEXD_IPCCOMMON_FOUND)
    message(STATUS "FLEXD_IPCCOMMON libs was found: " ${FLEXD_IPCCOMMON_LIBRARIES})
    message(STATUS "FLEXD_IPCCOMMON inc was found: " ${FLEXD_IPCCOMMON_INCLUDE_DIRS})
endif (FLEXD_IPCCOMMON_FOUND)

SET(privateHeaders
    inc/CoreAppDatabase.h
    inc/CoreAppExecutor.h
    inc/CoreAppManager.h
    inc/CoreAppRequestFactory.h
    inc/CoreAppRequestValidator.h
    inc/CoreAppTypes.h
    inc/FreezRequest.h
    inc/iApp.h
    inc/iCoreAppAck.h
    inc/iCoreAppRequest.h
    inc/InstallRequest.h
    inc/InvalidRequest.h
    inc/IPCClient.h
    inc/StartRequest.h
    inc/StateMachine.h
    inc/StopRequest.h
    inc/UnfreezRequest.h
    inc/UninstallRequest.h
    inc/UpdateRequest.h
    inc/Visitor.h
    inc/sqlite3pp.h
    inc/sqlite3pp.ipp
    inc/sqlite3ppext.h
    inc/sqlite3ppext.ipp
    inc/IPCInterface.h
)

SET(privateSources
    src/CoreAppDatabase.cpp
    src/CoreAppExecutor.cpp
    src/CoreAppManager.cpp
    src/CoreAppRequestFactory.cpp
    src/CoreAppRequestValidator.cpp
    src/FreezRequest.cpp
    src/iApp.cpp
    src/iCoreAppAck.cpp
    src/iCoreAppRequest.cpp
    src/InstallRequest.cpp
    src/InvalidRequest.cpp
    src/IPCClient.cpp
    src/StartRequest.cpp
    src/StateMachine.cpp
    src/StopRequest.cpp
    src/UnfreezRequest.cpp
    src/UninstallRequest.cpp
    src/UpdateRequest.cpp
    src/Visitor.cpp
    src/IPCInterface.cpp
    src/main.cpp

)

SET(${PROJECT_NAME}PublicInc "${CoreApp_SOURCE_DIR}/inc")

add_executable(${PROJECT_NAME} ${privateSources} ${privateHeaders})
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++14 -Wall -Wfloat-conversion ${JSON_PARSER_CFLAGS_OTHER})
target_include_directories(${PROJECT_NAME} PUBLIC inc ${JSON_PARSER_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE inc ${FLEXD_EPOLL_INCLUDE_DIRS} ${FLEXD_CONECTOR_INCLUDE_DIRS} ${FLEXD_IPCCOMMON_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
    ${MQQT_CLIENT_LIBRARIES}
    ${JSON_PARSER_LIBRARIES}
    ${FLEXD_LOGGER_LIBRARIES}
    ${FLEXD_EPOLL_LIBRARIES}
    ${FLEXD_CONECTOR_LIBRARIES}
    ${FLEXD_IPCCOMMON_LIBRARIES}
    pthread
    sqlite3
)

option(
    ENABLE_TESTS
    "Run Test?"
    ON
    )

if(ENABLE_TESTS)
  add_subdirectory(gtest)
endif (ENABLE_TESTS)

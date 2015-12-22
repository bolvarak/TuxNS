## CMake Policy
cmake_policy(SET CMP0005 NEW)

## Include Directories
include_directories(/opt/Qt/5.5/gcc_64/include)
include_directories(/usr/include)

## Definitions
add_definitions(-DHGI_CONFIG_FILE="${CMAKE_CURRENT_LIST_DIR}/source/api/application.ini")

## CMake Minimum Version
cmake_minimum_required(VERSION 3.2)

## Project Definition
project(TuxNS)

## CMake Settings & Configuration
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++11")
set(SOURCE_FILES source/api/main.cpp source/api/externals/HeimdallGI/PgModel.cpp source/api/externals/HeimdallGI/PgModel.h source/api/externals/HeimdallGI/CGI.cpp source/api/externals/HeimdallGI/Configuration.cpp source/api/externals/HeimdallGI/DBI.cpp source/api/externals/HeimdallGI/ErrorController.cpp source/api/externals/HeimdallGI/HTML.cpp source/api/externals/HeimdallGI/Log.cpp source/api/externals/HeimdallGI/MaxMind.cpp source/api/externals/HeimdallGI/Router.cpp source/api/externals/HeimdallGI/Template.cpp source/api/externals/HeimdallGI/View.cpp source/api/controllers/GeoIP.cpp source/api/externals/HeimdallGI/CGI.h source/api/externals/HeimdallGI/Configuration.h source/api/externals/HeimdallGI/DBI.h source/api/externals/HeimdallGI/ErrorController.h source/api/externals/HeimdallGI/HTML.h source/api/externals/HeimdallGI/Log.h source/api/externals/HeimdallGI/MaxMind.h source/api/externals/HeimdallGI/Router.h source/api/externals/HeimdallGI/Template.h source/api/externals/HeimdallGI/View.h source/api/controllers/GeoIP.h)
set(CMAKE_AUTOMOC ON)

## GeoIP Packages
find_package(GeoIP)

## Qt5 Packages
find_package(Qt5Core)
find_package(Qt5Network)
find_package(Qt5Sql)
find_package(Qt5Xml)

## Executable
add_executable(TuxNS ${SOURCE_FILES})

## Links
target_link_libraries(TuxNS Qt5::Core Qt5::Network Qt5::Sql)

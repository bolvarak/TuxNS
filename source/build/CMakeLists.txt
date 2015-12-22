## CMake Policy
cmake_policy(SET CMP0005 NEW)

## Include Directories
include_directories(/opt/Qt/5.5/gcc_64/include)

## Definitions
add_definitions(-DHGI_CONFIG_FILE="${CMAKE_CURRENT_LIST_DIR}/../api/application.ini" -DGEOIPDATADIR="/usr/share/GeoIP" -DPACKAGE_VERSION="1.6.3")

## CMake Minimum Version
cmake_minimum_required(VERSION 3.2)

## Project Definition
project(TuxNS)

## CMake Settings & Configuration
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++11")
set(SOURCE_FILES
		../api/externals/HeimdallGI/CGI.h
		../api/externals/HeimdallGI/Configuration.h
		../api/externals/HeimdallGI/DBI.h
		../api/externals/HeimdallGI/ErrorController.h
		../api/externals/HeimdallGI/HTML.h
		../api/externals/HeimdallGI/Log.h
		# ../api/externals/GeoIP/libGeoIP/pread.h
		../api/externals/GeoIP/libGeoIP/GeoIP_internal.h
		../api/externals/GeoIP/libGeoIP/GeoIP.h
		../api/externals/GeoIP/libGeoIP/GeoIPCity.h
		../api/externals/HeimdallGI/MaxMind.h
		../api/externals/HeimdallGI/Router.h
		../api/externals/HeimdallGI/Template.h
		../api/externals/HeimdallGI/View.h
		../api/controllers/GeoIP.h
		../api/main.cpp
		../api/externals/HeimdallGI/PgModel.cpp
		../api/externals/HeimdallGI/PgModel.h
		../api/externals/HeimdallGI/CGI.cpp
		../api/externals/HeimdallGI/Configuration.cpp
		../api/externals/HeimdallGI/DBI.cpp
		../api/externals/HeimdallGI/ErrorController.cpp
		../api/externals/HeimdallGI/HTML.cpp
		../api/externals/HeimdallGI/Log.cpp
		# ../api/externals/GeoIP/libGeoIP/pread.c
		../api/externals/GeoIP/libGeoIP/timeZone.c
		../api/externals/GeoIP/libGeoIP/regionName.c
		../api/externals/GeoIP/libGeoIP/GeoIP_deprecated.c
		../api/externals/GeoIP/libGeoIP/GeoIP.c
		../api/externals/GeoIP/libGeoIP/GeoIPCity.c
		../api/externals/HeimdallGI/MaxMind.cpp
		../api/externals/HeimdallGI/Router.cpp
		../api/externals/HeimdallGI/Template.cpp
		../api/externals/HeimdallGI/View.cpp
		../api/controllers/GeoIP.cpp
		)
set(CMAKE_AUTOMOC ON)

## Qt5 Packages
find_package(Qt5Core)
find_package(Qt5Network)
find_package(Qt5Sql)
find_package(Qt5Xml)

## Executable
add_executable(TuxNS ${SOURCE_FILES})

## Links
target_link_libraries(TuxNS Qt5::Core Qt5::Network Qt5::Sql)
